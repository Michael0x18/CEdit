////////////////////////////////////////
// CEDIT Version 0.0A ALPHA
// Author: Michael Ferolito
// License: GNU Lesser General Public License
// Description: A text editor for the CE,
//              with support for multi-key
//              shortcuts, and a rich functionality
//              set
//
//              Currently, it is compatible with the following shells:
//              CESIUM -- arguments as a space separated list in the ANS variable
//		BOSshell - no, but planned
//		Xenon - no, but planned
////////////////////////////////////////
/*SYSTEM HEADER FILES*/
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <tice.h>
#include <fileioc.h>
#include <inttypes.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <graphx.h>
#include <keypadc.h>
/*USER HEADER FILES*/
#include "main.h"
#include "tigcclib.h"


short get_len(){
	int24_t i = 0;
	while(c1>0 && text[c1-1] != '\n'){
		i++;cursor_left();
	}
	for(int j = 0; j < i; j++){
		cursor_right();
	}
	return i;
}

//Returns true if the short passed as an argument
//is a control character, false otherwise.
bool is_control(short k)
{
	return (k<=0)||(k>=256);
}

//Redraws the main editor screen, scrolling if the cursor
//is not visible
void redraw_editor(void)
{
	//Clear screen
	gfx_ZeroScreen();
	//Draw upper and lower status bars
	gfx_SetColor(STATUSBAR_COLOR);
	gfx_FillRectangle_NoClip(0,0,320,10);
	gfx_FillRectangle_NoClip(0,230,320,10);
	//Prepare for main drawing
	gfx_SetColor(FG_COLOR);
	int24_t i = scr_offset;
	int8_t row = 0;
	int8_t col = 0;
	int24_t cp = 0;
	bool drawn = 0;
	//Main drawing
	while(i < MAX_BUFFER_SIZE && (cp<MAX_BUFFER_SIZE-c2+c1) && row<22) {

		if(i==c1) {
			gfx_VertLine_NoClip(10*col,10*row+10,10);
			i=c2+1;
			//cr=row;
			drawn=1;
			if(i>=MAX_BUFFER_SIZE)break;
		}

		if(text[i]=='\n') {
			row++;
			col=0;
			i++; cp++;
			continue;
		}

		gfx_SetTextXY(10*col,10*row+10);
		gfx_PrintChar(text[i]);

		i++; cp++;
		col++;
		if(col>=32) {
			col=0;
			row++;
		}

	}
	gfx_SetTextXY(0,0);
	gfx_PrintString(hasfilename?filename:"*Untitled*");
	gfx_SetTextXY(0,232);
	gfx_PrintInt(lines[lc1],4);
	gfx_SetTextXY(60,232);
	gfx_PrintInt(lc_offset,4);
	gfx_SwapDraw();
	//Scroll if cursor is not on screen
	if(!drawn) {
		if(c1<scr_offset) {
			scroll_up();
		}else{
			scroll_down();
		}
		redraw_editor();
	}

}

void insert_newline(){
	lc1++;
	lines[lc1]=0;
	lc_offset=0;
}

//Inserts the specified character into the buffer, updating
//the pointers accordingly.
void insert_char(char c)
{
	text[c1]=c;
	c1++;
	if(text[c1-1]=='\n'){
		//stuff to update
		insert_newline();
	}else{
		lines[lc1]++;
		lc_offset++;
	}
}

//Draws a file save screen
void draw_file_save_dialog(void)
{
	gfx_ZeroScreen();
	gfx_SetTextXY(0,0);
	gfx_PrintString("Enter a file name to (over)write");
	gfx_SetTextXY(0,10);
	gfx_PrintString(filename);
}

//Tests if the static filename variable is a valid file name
bool is_valid(void)
{
	return 1;//TODO add a proper check
}

//Writes the contents of the buffer to a file.
//Prompts the user for a filename if not already specified.
void save_file(void)
{
	ti_var_t var;
	ti_CloseAll();

	if(!hasfilename){
		short k=0;
		//prompt
		draw_file_save_dialog();
		gfx_SwapDraw();
		int sp=0;
		while(k!='\n'){
			k=ngetchx();
			if(!is_control(k)){
				if(k=='\n')break;
				if(sp<8){
					filename[sp]=k;
					sp++;
				}
			}else if(k==KEY_BS){
				if(sp>0){
					filename[sp-1]=0;
					sp--;
				}
			}
			draw_file_save_dialog();
			gfx_SwapDraw();
		}
		if(!is_valid()){
			return;//TODO print error message and error out
		}
		hasfilename=1;
	}
	var=ti_Open(filename,"w");

	int i = 0;
	while(i<MAX_BUFFER_SIZE){
		if(i==c1)i=c2+1;
		if(i>=MAX_BUFFER_SIZE)break;
		ti_PutC(text[i],var);
		i++;
	}

	ti_CloseAll();
}

//Attempts to fetch a string from the ANS variable.
//If such a string exists, e.g. if this is called
//as an editor program from Cesium, it sets filename.
void attempt_load_cesium(void)
{
	ti_RclVar(TI_STRING_TYPE, ti_Ans, (void*)(&Ans_Data));
	if ((Ans_Data->data)==NULL || Ans_Data == NULL){
		return;
	}else{
		memset(filename,0,10);

		int size = Ans_Data->len;
		if(size>8)size=8;

		for(int i = 0; i < size; i++){
			if(Ans_Data->data[i]==0 || Ans_Data->data[i]==' ')break;
			filename[i]=Ans_Data->data[i];
		}
		hasfilename=1;
#ifndef NDEBUG
		printf("Got filename %s\n",filename);
		printf("Length is %d",strlen(filename));
		ngetchx();
#endif
	}
}

//Attempts to load file names in the following order:
//1) Cesium
//2) BOSshell
//3) Xenon
//4) VYSion
void load_file_name(void)
{
	attempt_load_cesium();
}

//Reads into the buffer the contents of the file
//denoted by filename, if it exists.
void open_file(void)
{
	ti_var_t var;
	ti_CloseAll();
	var=ti_Open(filename,"r");
	if(var==0){
		return;//no error out
	}
	char c;
	while((c=ti_GetC(var))!=EOF){
		insert_char(c);
	}
}

void line_up(void)
{
	if(lc1>0){
		lines[lc2]=lines[lc1];
		lc1--;
		lc2--;
		lc_offset=lines[lc1];
	}
}

void line_down(void)
{
	if(lc2<MAX_BUFFER_SIZE){
		lc2++;
		lc1++;
		lines[lc1]=lines[lc2];
		lc_offset=0;
	}
}


//moves the text cursor one character left
void cursor_left(void)
{
	if(c1>0) {
		if(/*text[c1-1]=='\n' || */lc_offset==0){
			//we're moving left across a line feed
			//Move to previous line
			line_up();
			//lc_offset=lines[lc1];
		}else{
			//Moving on same line
			lc_offset--;
		}
		c1--;
		text[c2]=text[c1];
		c2--;
	}
}

//moves the text cursor one character right
void cursor_right(void)
{
	if(c2<MAX_BUFFER_SIZE-1) {
		if(/*text[c2+1]=='\n' || */lc_offset==lines[lc1]){
			line_down();
			//lc_offset=0;
		}else{
			lc_offset++;
		}
		c2++;
		text[c1]=text[c2];
		c1++;
	}
}

//moves the text cursor one character up
void cursor_up(void)
{
	//if the current line is long enough
	if(lc_offset>NUM_COLS){
		for(int i = 0; i < NUM_COLS; i++){
			cursor_left();
		}
	}else{
		//cache the current offset -- use this later
		int old = lc_offset;
		while(lc_offset>0){
			cursor_left();
		}
		if(!c1)return;
		cursor_left();
		//on last char of next line
		//now need to move until old

		//return if the end is what you want
		if(lc_offset%NUM_COLS<=old)
			return;
		int c = lc_offset-lc_offset%NUM_COLS;
		c+=old;//Offset to move to from start of line
		int to_move = lc_offset-c;
		for(int i = 0; i < to_move; i++){
			cursor_left();
		}
	}
}

//Moves the text cursor one row down
//borked 
void cursor_down(void)
{
	//if current line is long enough
	if(lines[lc1]-lc_offset>NUM_COLS){
		for(int i = 0; i < NUM_COLS; i++){
			cursor_right();
		}
	}else{
		int old=lc_offset;
		while(lc_offset>0){
			cursor_right();
			if(c2==MAX_BUFFER_SIZE-1){
				return;
			}
		}
		if(lines[lc1]<=old%NUM_COLS){
			for(int i = 0; i < lines[lc1]; i++){
				cursor_right();
			}
		}
		//Now on first char of next line
		//lock_dist is buffer line offset
		//////wtf//////
		//int lock_dist = lines[lc1]-lines[lc1]%32;
		//The true offset distance
		int true_offset = /*lock_dist+*/old%NUM_COLS;
		for(int i = 0; i < true_offset; i++){
			cursor_right();
		}
		
	}
}

//backspace
void bs(void)
{
	if(c1){
		if(/*text[c1-1]=='\n' || */lc_offset==0){
			/*
			gfx_SetDrawScreen();
			gfx_SetTextXY(10,10);
			gfx_PrintString("YES!!!");
			gfx_SetDrawBuffer();
			ngetchx();*/
			lc1--;//Delete line
			lc_offset=lines[lc1];
			lines[lc1]+=lines[lc1+1];
		}else{
			lc_offset--;//else go back
			lines[lc1]--;
		}
		c1--;
	}
}

//delete TODO untested
void del(void)
{
	if(c2<MAX_BUFFER_SIZE-1){
		if(lc_offset==lines[lc1]){
			lc2++;
			lines[lc1]+=lines[lc2+1];
		}else{
			lines[lc1]--;
		}
		c2++;
	}
}

//scrolls up a single row
//void scroll_up(void)
//{
	/*
	int i = scr_offset-1;
	int cm=0;
	//seek for new line
	while(i>=0 && text[i-1]!='\n'){
		i--;
		if(i==c2)i=c1-1;
		cm++;
	}
	//Found either SOF or newline, doesn't matter
	//We go ahead any way
	if(cm>32){
		int t = scr_offset;
		for(int i1=0;i1<32; i1++){
			t--;
			if(t==c2)
				t=c1-1;	
			if(t==0){
				scr_offset=0;return;
			}
		}
		scr_offset=t;
		return;
	}
	//int offset = cm;
	i--;
	if(i==c2)i=c1-1;
	i--;
	if(i==c2)i=c1-1;
	int cm2=0;
	//seek for next new line
	while(i>=0 && text[i-1]!='\n'){
		i--;
		if(i==c2)i=c1-1;
		cm2++;
	}
	int offset=cm2%32;
	int t = i;
	for(int i2 = 0; i2 < cm2-offset; i2++){
		t++;
		if(t==c1)t=c2+1;
	}


	*/


	//wtf was I thinking?
	/*int cm2 = cm%32;
	if(!cm2){
		cm2=32;
	}
	int t = scr_offset;
	for(int i1=0;i1<32; i1++){
		t--;
		if(t==c2)
			t=c1-1;	
		if(t==0){
			scr_offset=0;return;
		}
	}
	scr_offset=t;
	*/
	
//}
//
void scroll_up(void)
{
	//WTH I don't know if this is gonna work, but I'm hella tired rn.
	//scr_offset=c1-(lines[lc1]%32==0?32:lines[lc1]%32);
	scr_offset=c1-lc_offset%32;
	
}
void scroll_down_line();
void scroll_down(void){
	//This is gonna suck. There are 22 columns, so that means 22 segments above the mouse cursor.
	scroll_down_line();
	
}

//scrolls down a single row
void scroll_down_line(void)//ASSUMES THE CURSOR IS OFF THE BOTTOM OF THE SCREEN
{
	int i = scr_offset;
	for(;i-scr_offset<32;++i){
		if(text[i+1]=='\n'){
			i++;
			break;
		}
	}
	scr_offset=i;
}

//scrolls down a single row
////borked
void scroll_down_old(void)
{
	int i = scr_offset;
	int cp=0;

	while(1){
		i++;
		if(i==c1)i=c2+1;
		cp++;
		if(i==MAX_BUFFER_SIZE-1){
			scr_offset=MAX_BUFFER_SIZE-1;
			return;
		}
		//if(cp==32){
		//	scr_offset=i;
		//}
		if(text[i]=='\n'){
			scr_offset=i+1;
			return;
		}
	}
}

//main function
void main(int argc, char** argv)
{
	//load_file_name();
	if(argc>=2){
		strncpy(filename,argv[1],8);
		if(is_valid()){
			hasfilename=1;
		}
	}
	gfx_Begin();
	gfx_SetTransparentColor(TRANSPARENT_COLOR);
	gfx_SetTextTransparentColor(TRANSPARENT_COLOR);
	gfx_SetTextFGColor(FG_COLOR);
	gfx_SetTextBGColor(TRANSPARENT_COLOR);
	gfx_SetColor(FG_COLOR);
	gfx_SetDrawBuffer();
	c1=0;
	lc2=16383;
	//cr=0;
	scr_offset=0;
	c2=16383;
	memset(text,0,16384);
	if(hasfilename){
		open_file();
	}
	//scr_end=0;
	redraw_editor();
	//gfx_SwapDraw();
	//redraw_editor();
    //gfx_SwapDraw();
	short k = 0;
	//if(hasfilename){
	//	open_file();
	//}
	while(k!=KEY_CLEAR) {
		k=ngetchx();
		//if(k==KEY_CUT)k='1';
		//if(k==KEY_COPY)k='2';
		//if(k==KEY_PASTE)k='3';
		//gfx_SetTextXY(10*(i%32),10*(i/32));i++;
		if(!is_control(k)) {
			insert_char(k);
			redraw_editor();
		} else {
			//TODO make it a switch statement
			switch(k){
			case KEY_LEFT:
				cursor_left();
				break;
			case KEY_RIGHT:
				cursor_right();
				break;
			case KEY_DOWN:
				cursor_down();
				break;
			case KEY_UP:
				cursor_up();
				break;
			case KEY_BS:
				bs();
				break;
			case KEY_DEL:
				del();
				break;
			case KEY_SAVE:
				save_file();
				break;
			}
			redraw_editor();
			/*
			if(k==KEY_LEFT) {
				cursor_left();
				redraw_editor();
			}
			if(k==KEY_RIGHT) {
				cursor_right();
				redraw_editor();
			}
			if(k==KEY_DOWN) {
				cursor_down();
				redraw_editor();
			}
			if(k==KEY_UP) {
				cursor_up();
				redraw_editor();
			}
			if(k==KEY_BS) {
				bs();
				redraw_editor();
			}
			if(k==KEY_DEL) {
				del();
				redraw_editor();
			}
			if(k==KEY_SAVE) {
				save_file();
				redraw_editor();
			}*/
		}
	}

	gfx_End();
}

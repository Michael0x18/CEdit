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
#include "tigcclib.h"
#include "main.h"

int animatecursor(void)
{
	if(!editor_on){
		return 1;
	}
	if(c_on){
		c_on=0;
		gfx_VertLine_NoClip(cursor_x,cursor_y,10);
	}else{
		c_on=1;
		gfx_SetColor(0);
		gfx_VertLine_NoClip(cursor_x,cursor_y,10);
		gfx_SetColor(FG_COLOR);
	}
	return 0;
}

//Draw scroll bar
void draw_scroll(void)
{
	//scrollbar data
	int24_t size_of_bar =22*220/( lc1+MAX_BUFFER_SIZE-lc2);
	//size_of_bar*=220;
	//size_of_bar/=22;
	if(size_of_bar>=220){
		size_of_bar=220;
	}
	int24_t ypos=10+220*scr_line/(lc1+MAX_BUFFER_SIZE-lc2);
	if(ypos+size_of_bar>230){
		ypos=230-size_of_bar;
	}
	//int24_t length = 220/size_of_bar;
	gfx_SetColor(220);//TODO symbolic name
	gfx_Rectangle_NoClip(310,ypos,10,size_of_bar);
	gfx_SetColor(42);
	gfx_FillRectangle_NoClip(311,ypos+1,8,size_of_bar-2);
	gfx_SetColor(FG_COLOR);
}

//Deprecated
short get_len()
{
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
	editor_on=1;
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
		if(i==0){
			gfx_SetTextXY(0,10);
			gfx_PrintChar(':');
		}
		if(i==c1) {
			if(col>=NUM_COLS){
				gfx_VertLine_NoClip(319,10*row+10,10);
				cursor_x=319;
				cursor_y=10*row+10;
				c_on=1;
			}else{
				gfx_VertLine_NoClip((10+10*col),10*row+10,10);
				c_on=1;
				cursor_x=(10+10*col);
				cursor_y=10+10*row;
			}

			i=c2+1;
			//cr=row;
			drawn=1;
			if(i>=MAX_BUFFER_SIZE)break;
		}

		if(text[i]=='\n') {
			row++;
			col=0;
			i++; cp++;
			gfx_SetTextXY(0,10*row+10);
			gfx_PrintChar(':');
			continue;
		}

		gfx_SetTextXY(10*col+10,10*row+10);
		gfx_PrintChar(text[i]);

		i++; cp++;
		col++;
		if(col>=NUM_COLS) {
#ifdef SMART_WRAPPING
			//if((i==MAX_BUFFER_SIZE-1&&col==NUM_COLS)||(col==NUM_COLS&&text[(i+1==c1)?c2+1:i+1]=='\n')){
			//No wrap?
			//if at edge of screen
			if(col==NUM_COLS){
				//if next char is a newline
				//if(text[(i+1==c1)?c2+1:i+1]=='\n'){
				if(text[i==c1?c2+1:i]=='\n'){
					//skip it
					continue;
				}
			}
#endif
			//Otherwise just move down
			//if(text[i]!='\n'){
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
	gfx_SetTextXY(200,0);
	gfx_PrintString(VERSION_STRING);
	draw_scroll();
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

//Inserts a newline into the line buffer
void insert_newline(){
	//Perform line splitting
	int tmp=lines[lc1]-lc_offset;
	lines[lc1]=lc_offset;
	//Create new entry in line buffer.
	lc1++;
	lines[lc1]=tmp;
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
		editor_on=0;//TODO move the cursor and animate instead of this
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
		editor_on=1;
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

//Move to the previous line
void line_up(void)
{
	if(lc1>0){
		lines[lc2]=lines[lc1];
		lc1--;
		lc2--;
		lc_offset=lines[lc1];
	}
}

//Move to the next line
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
		if(lc_offset%NUM_COLS<old)
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
	if(lines[lc1]-lc_offset>NUM_COLS){
		for(int i = 0; i < NUM_COLS; i++){
			cursor_right();
		}
	}else{
		int old=lc_offset;int oldb = lines[lc1];
		for(int i = 0; i < oldb-old; i++){
			cursor_right();
		}cursor_right();
		if(lines[lc1]<old%NUM_COLS){
			for(int i = 0; i < lines[lc1]; i++){
				cursor_right();
			}
		}else{
			for(int i = 0; i < old%NUM_COLS; i++){
				cursor_right();
			}
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

void scroll_up(void)
{
	//WTH I don't know if this is gonna work, but I'm hella tired rn.
	//scr_offset=c1-(lines[lc1]%32==0?32:lines[lc1]%32);
	scr_offset=c1-lc_offset%NUM_COLS;
	scr_line=lc1;
	
}

int divide_round_up(int a, int b){
	return a%b==0?a/b:a/b+1;
}

void scroll_down(void){
	scroll_down_line();
	scr_line++;
	/*int line_offset=0;
	int offset = lc_offset-lc_offset%NUM_COLS;
	int segments_left = 21;//Move 21 segments up*/
	
}

void scroll_down_borked(void){
	gfx_SetDrawScreen();
	gfx_SetTextXY(30,30);
	gfx_PrintString("Scroll Down called");
	//This is gonna suck. There are 22 rows, and there are 22 segments above the mouse cursor.
	//janky crutch
	//scroll_down_line();
	//int offset = c1;
	int line_offset = 0;
	int offset=lc_offset-lc_offset%NUM_COLS;
	int segment=5;
	for(int i = 0;segment>0&& i < lc_offset/NUM_COLS; i++){
		segment--;
		offset-=NUM_COLS;
		//offset--;
	}
	gfx_SetTextXY(30,40);
	gfx_PrintInt(segment,3);
	ngetchx();
	//line_offset++;
	while(segment>0){
		line_offset++;
		if(lines[lc1-line_offset]%NUM_COLS!=0 || lines[lc1-line_offset]==0){
			segment--;
			offset-=lines[lc1-line_offset]%NUM_COLS;
			offset--;
		}
		for(int i = 0; segment>0&&i<lines[lc1-line_offset]/NUM_COLS; i++){
			segment--;
			offset-=NUM_COLS;
			//offset--;
		}
		//line_offset++;
	}
	gfx_ZeroScreen();
	gfx_SetTextXY(30,30);
	gfx_PrintInt(segment,3);
	ngetchx();
	gfx_SetDrawBuffer();
	scr_offset=offset;
	
}

//scrolls down a single row
void scroll_down_line(void)//ASSUMES THE CURSOR IS OFF THE BOTTOM OF THE SCREEN
{
	int i = scr_offset;
	for(;i-scr_offset<NUM_COLS;++i){
		if(text[i+1]=='\n'){
			i++;
			break;
		}
	}
	scr_offset=i;
}

void cursor_to_start(void)
{
	while(c1){
		cursor_left();
	}
}

void cursor_to_end(void)
{
	while(c2<MAX_BUFFER_SIZE-1){
		cursor_right();
	}
}

void cursor_to_left_word(void)
{

}

void cursor_to_right_word(void)
{

}

void cursor_multi_up(void)
{
	for(int i = 0; i < MULTI_LINES; i++){
		cursor_up();
	}
}

void cursor_multi_down(void)
{
	for(int i = 0; i < MULTI_LINES; i++){
		cursor_down();
	}
}

void cursor_to_l_start(void)
{
	while(lc_offset){
		cursor_left();
	}
}

void cursor_to_l_end(void)
{
	while(lc_offset<lines[lc1]){
		cursor_right();
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
	lc2=MAX_BUFFER_SIZE-1;
	//cr=0;
	scr_offset=0;
	c2=MAX_BUFFER_SIZE-1;
	memset(text,0,MAX_BUFFER_SIZE);
	text[MAX_BUFFER_SIZE]='\n';
	lines[MAX_BUFFER_SIZE]=-1;
	if(hasfilename){
		open_file();
	}
	//scr_end=0;
	editor_on=1;
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
			switch(k){
			case KEY_LEFT://left
				cursor_left();
				break;
			case KEY_RIGHT://right
				cursor_right();
				break;
			case KEY_DOWN://down
				cursor_down();
				break;
			case KEY_UP://up
				cursor_up();
				break;
			case KEY_BS://backspace
				bs();
				break;
			case KEY_DEL://delete
				del();
				break;
			case KEY_SAVE://save
				save_file();
				break;
			case KEY_WLEFT://2nd-left
				cursor_to_left_word();
				break;
			case KEY_WRIGHT://2nd-right
				cursor_to_right_word();
				break;
			case KEY_WUP://2nd-up
				cursor_multi_up();
				break;
			case KEY_WDOWN://2nd-down
				cursor_multi_down();
				break;
			case KEY_LLEFT://meta-left
				cursor_to_l_start();
				break;
			case KEY_LRIGHT://meta-right
				cursor_to_l_end();
				break;
			case KEY_LUP://meta-up
				cursor_to_start();
				break;
			case KEY_LDOWN://meta-down
				cursor_to_end();
				break;
			}
			redraw_editor();
		}
	}

	gfx_End();
}

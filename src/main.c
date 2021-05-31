////////////////////////////////////////
// { PROGRAM NAME } { VERSION }
// Author:
// License:
// Description:
////////////////////////////////////////

#include "tigcclib.h"

#define MAX_BUFFER_SIZE 16384

#define TRANSPARENT_COLOR 1
#define BG_COLOR 0
#define FG_COLOR 255
#define STATUSBAR_COLOR

static char text[MAX_BUFFER_SIZE];
static int24_t c1;
static int24_t c2;
static int24_t scr_offset;
static int24_t scr_end;

static int24_t cr;

void redraw();

//static int8_t cr;
//static int8_t cc;

void cursor_left() {
	if(c1>0) {
		c1--;
		text[c2]=text[c1];
		c2--;
	}
}

void cursor_right() {
	if(c2<MAX_BUFFER_SIZE-1) {
		c2++;
		text[c1]=text[c2];
		c1++;
	}
}

void insertChar(char c) {
	text[c1]=c;
	c1++;
}

void bs() {
	if(c1)
		c1--;
}

void del() {
	if(c2<MAX_BUFFER_SIZE-1)
		c2++;
}

//Saves a text file
void savefile() {

}

//opens a file for editing
void openfile() {

}

void scroll_up(){
	//scroll up 1 row
	int i = scr_offset-1;int cp = 0;
	while(1){
		i--;
		if(i==c2)i=c1-1;
		cp++;
		if(i==0){
			scr_offset=0;
			return;
		}
		//if(cp==31){
		//	scr_offset=i;
		//	return;
		//}
		if(text[i]=='\n'){
			scr_offset=i+1;
			return;
		}
	}
}

void scroll_down(){
	//no work
	//scr_offset+=32;
	//return;
	int i = scr_offset;int cp=0;
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

void redraw() {
	//gfx_FillScreen(BG_COLOR);
	gfx_ZeroScreen();
	gfx_SetColor(120);
	gfx_FillRectangle_NoClip(0,0,320,10);
	gfx_FillRectangle_NoClip(0,230,320,10);
	gfx_SetColor(FG_COLOR);
	int24_t i = scr_offset;
	int8_t row = 0;
	int8_t col = 0;
	int24_t cp = 0;
	bool drawn = 0;
	while(i < MAX_BUFFER_SIZE && (cp<MAX_BUFFER_SIZE-c2+c1) && row<22) {

		if(i==c1) {
			gfx_VertLine_NoClip(10*col,10*row+10,10);
			i=c2+1;
			cr=row;
			drawn=1;
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
	gfx_SwapDraw();
	if(!drawn) {
		//scroll

		if(c1<scr_offset) {
			//scroll up
			/*
			   int j = c1;
			   while(j >= 0 && text[j]!='\n') {
			   --j;
			   }
			   scr_offset=j+1;
			   */
			scroll_up();
		}else{
			/*
			   int j = c1;
			   while(j >= 0 && text[j]!='\n') {
			   ++j;
			   }
			   scr_offset=j-cp-1;
			   */
			scroll_down();
		}
		redraw();
	}
}

bool isControl(short k) {
	return (k<=0)||(k>=256);
}

void main() {
	//printf("Hello, World!");
	//ngetchx();
	gfx_Begin();
	gfx_SetTransparentColor(TRANSPARENT_COLOR);
	gfx_SetTextTransparentColor(TRANSPARENT_COLOR);
	gfx_SetTextFGColor(FG_COLOR);
	gfx_SetTextBGColor(TRANSPARENT_COLOR);
	//gfx_FillScreen(BG_COLOR);
	gfx_SetColor(FG_COLOR);
	gfx_SetDrawBuffer();
	c2=0;
	cr=0;
	scr_offset=0;
	c2=16383;
	memset(text,0,16384);
	scr_end=0;
	redraw();
	gfx_SwapDraw();
	//short i = 0;
	short k = 0;
	while(k!=KEY_CLEAR) {
		k=ngetchx();
		//if(k==KEY_CUT)k='1';
		//if(k==KEY_COPY)k='2';
		//if(k==KEY_PASTE)k='3';
		//gfx_SetTextXY(10*(i%32),10*(i/32));i++;
		if(!isControl(k)) {
			insertChar(k);
			redraw();
		} else {
			if(k==KEY_LEFT) {
				cursor_left();
				redraw();
			}
			if(k==KEY_RIGHT) {
				cursor_right();
				redraw();
			}
			if(k==KEY_BS) {
				bs();
				redraw();
			}
			if(k==KEY_DEL) {
				del();
				redraw();
			}
		}
	}

	gfx_End();
}

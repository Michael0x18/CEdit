#ifndef _tigcclib
#define _tigcclib

#ifndef _ngetchx_h
#define _ngetchx_h
/* Keep these headers */
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <tice.h>
#include <fileioc.h>

#include <inttypes.h>

/* Standard headers */
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <graphx.h>
#include <keypadc.h>

enum ControlKeys{
	KEY_NO_EXIST	=	0,
	KEY_RESERVED	=	-1,
	KEY_UNBOUND	=	-2,
	KEY_F1		=	259,
	KEY_F2		=	260,
	KEY_F3		=	261,
	KEY_F4		=	262,
	KEY_F5		=	263,
	KEY_F6		=	264,
	KEY_F7		=	265,
	KEY_F8		=	266,
	KEY_F9		=	267,
	KEY_F10		=	268,
	KEY_CUT		=	269,
	KEY_COPY	=	270,
	KEY_PASTE	=	271,
	KEY_LEFT	=	272,
	KEY_RIGHT	=	273,
	KEY_UP		=	274,
	KEY_DOWN	=	275,
	KEY_WLEFT	=	276,
	KEY_WRIGHT	=	277,
	KEY_WUP		=	278,
	KEY_WDOWN	=	279,
	KEY_SLEFT	=	280,
	KEY_SRIGHT	=	281,
	KEY_SUP		=	282,
	KEY_SDOWN	=	283,
	KEY_WSLEFT	=	284,
	KEY_WSRIGHT	=	285,
	KEY_WSUP	=	286,
	KEY_WSDOWN	=	287,
	KEY_LLEFT	=	288,
	KEY_LRIGHT	=	289,
	KEY_LUP		=	290,
	KEY_LDOWN	=	291,
	KEY_LSLEFT	=	292,
	KEY_LSRIGHT	=	293,
	KEY_LSUP	=	294,
	KEY_LSDOWN	=	295,
	KEY_CLEAR	=	296,
	KEY_TAB		=	297,
	KEY_DEL		=	298,
	KEY_BS		=	299,
	KEY_BRIGHT_U	=	300,
	KEY_BRIGHT_D	=	301,
	KEY_ESC		=	302,
	KEY_KILL	=	303,
	KEY_SAVE	=	304,
	KEY_SUSPEND	=	305,
	KEY_OFF		=	306,
	KEY_BREAK	=	307,
	KEY_FQUIT	=	308,
	KEY_UNDO	=	309,
	KEY_REDO	=	310,
	KEY_QUIT    	=	311,
	KEY_OPEN	=	312
};

//backend for scanning keys, ignores modifiers
uint8_t ngetchx_backend(void) {
	static uint8_t last_key;
	uint8_t only_key = 0;
	kb_Scan();
	for (uint8_t key = 1, group = 7; group; --group) {
		for (uint8_t mask = 1; mask; mask <<= 1, ++key) {
			if (kb_Data[group] & mask) {
				if(key==40||key==48||key==54||key==55)continue;
				if (only_key) {
					last_key = 0;
					return 0;
				} else {
					only_key = key;
				}
			}
		}
	}
	if (only_key == last_key) {
		return 0;
	}
	last_key = only_key;
	return only_key;
}

short kmain[]={KEY_NO_EXIST,	KEY_DOWN,	KEY_LEFT,	KEY_RIGHT,	KEY_UP,		KEY_NO_EXIST,	KEY_NO_EXIST,	KEY_NO_EXIST,	KEY_NO_EXIST,	'\n', '+', '-', '*', '/', '^', KEY_TAB, KEY_NO_EXIST, '-', '3', '6', '9', ')', KEY_UNBOUND, KEY_UNBOUND, KEY_NO_EXIST, '.', '2', '5', '8', '(', KEY_UNBOUND, KEY_UNBOUND, KEY_SAVE, '0', '1', '4', '7', ',', KEY_UNBOUND, KEY_UNBOUND, KEY_NO_EXIST, KEY_RESERVED, KEY_SAVE, '\\', '|', '=', KEY_UNBOUND, KEY_UNBOUND, KEY_NO_EXIST, KEY_F5, KEY_F4, KEY_F3, KEY_F2, KEY_F1, KEY_NO_EXIST, KEY_NO_EXIST, KEY_BS};

short ksec[]={KEY_NO_EXIST,	KEY_WDOWN, KEY_WLEFT, KEY_WRIGHT, KEY_WUP, KEY_NO_EXIST, KEY_NO_EXIST, KEY_NO_EXIST, KEY_NO_EXIST, KEY_UNBOUND, '\'', ']', '[', KEY_UNBOUND, KEY_UNBOUND, KEY_CLEAR, KEY_NO_EXIST, KEY_UNBOUND, KEY_UNBOUND, KEY_UNBOUND, KEY_UNBOUND, '}', KEY_UNBOUND, KEY_UNBOUND, KEY_NO_EXIST, KEY_UNBOUND, KEY_UNBOUND, KEY_UNBOUND, KEY_UNBOUND, '{', KEY_UNBOUND, KEY_UNBOUND, KEY_SAVE, KEY_UNBOUND, KEY_UNBOUND, KEY_UNBOUND, KEY_UNBOUND, KEY_UNBOUND, KEY_UNBOUND, KEY_UNBOUND, KEY_NO_EXIST, KEY_RESERVED, KEY_SAVE, KEY_UNBOUND, KEY_UNBOUND, KEY_UNBOUND, KEY_UNBOUND, KEY_UNBOUND, KEY_NO_EXIST, KEY_F10, KEY_F9, KEY_F8, KEY_F7, KEY_F6, KEY_NO_EXIST, KEY_NO_EXIST, KEY_DEL};

short kalpha[]={KEY_NO_EXIST, KEY_DOWN, KEY_LEFT, KEY_RIGHT, KEY_UP, KEY_NO_EXIST, KEY_NO_EXIST, KEY_NO_EXIST, KEY_NO_EXIST, '\n', '"', 'w', 'r', 'm', 'h', KEY_TAB, KEY_NO_EXIST, '?', '_', 'v', 'q', 'l', 'g',KEY_UNBOUND,KEY_NO_EXIST, ':', 'z', 'u', 'p', 'k', 'f', 'c',KEY_NO_EXIST, ' ', 'y', 't', 'o', 'j', 'e', 'b', KEY_NO_EXIST, KEY_RESERVED, 'x', 's', 'n', 'i', 'd', 'a', KEY_NO_EXIST, KEY_F5, KEY_F4, KEY_F3, KEY_F2, KEY_F1, KEY_NO_EXIST,KEY_NO_EXIST, KEY_BS};
short kshift[]={KEY_NO_EXIST, KEY_SDOWN, KEY_SLEFT, KEY_SRIGHT, KEY_SUP, KEY_NO_EXIST, KEY_NO_EXIST, KEY_NO_EXIST, KEY_NO_EXIST, KEY_UNBOUND, '\'', 'W', 'R', 'M', 'H', KEY_UNBOUND, KEY_NO_EXIST, '<', '>', 'V', 'Q', 'L', 'G', KEY_UNBOUND, KEY_NO_EXIST, ';', 'Z', 'U', 'P', 'K', 'F', 'C', KEY_SAVE, ' ', 'Y', 'T', 'O', 'J', 'E', 'B', KEY_NO_EXIST, KEY_RESERVED, 'X', 'S', 'N', 'I', 'D', 'A', KEY_NO_EXIST, KEY_F5, KEY_F4, KEY_F3, KEY_F2, KEY_F1, KEY_NO_EXIST, KEY_NO_EXIST, KEY_UNBOUND};
short kmeta[]={KEY_NO_EXIST, KEY_LDOWN, KEY_LLEFT, KEY_LRIGHT, KEY_LUP, KEY_NO_EXIST, KEY_NO_EXIST, KEY_NO_EXIST, KEY_NO_EXIST, KEY_UNBOUND,'!','@','#','$','%','&', KEY_NO_EXIST, KEY_UNBOUND,KEY_UNBOUND,KEY_UNBOUND,KEY_UNBOUND,KEY_UNBOUND,KEY_UNBOUND, KEY_UNBOUND,KEY_NO_EXIST, KEY_UNBOUND, KEY_UNBOUND, KEY_UNBOUND, KEY_UNBOUND, KEY_UNBOUND, KEY_UNBOUND, KEY_UNBOUND, KEY_OPEN, KEY_UNBOUND, KEY_UNBOUND, KEY_UNBOUND, KEY_UNBOUND, KEY_UNBOUND, KEY_UNBOUND, KEY_UNBOUND, KEY_UNBOUND, KEY_RESERVED, KEY_OPEN, KEY_UNBOUND, KEY_UNBOUND, KEY_UNBOUND, KEY_UNBOUND, KEY_UNBOUND, KEY_UNBOUND, KEY_REDO, KEY_UNDO, KEY_PASTE, KEY_COPY, KEY_CUT, KEY_UNBOUND, KEY_UNBOUND, KEY_QUIT};
short ksecshift[]={KEY_NO_EXIST, KEY_WSDOWN, KEY_WSLEFT, KEY_WSRIGHT, KEY_WSUP, KEY_NO_EXIST, KEY_NO_EXIST, KEY_NO_EXIST, KEY_NO_EXIST, KEY_UNBOUND,KEY_UNBOUND,KEY_UNBOUND,KEY_UNBOUND,KEY_UNBOUND,KEY_UNBOUND,KEY_UNBOUND, KEY_NO_EXIST, KEY_UNBOUND,KEY_UNBOUND,KEY_UNBOUND,KEY_UNBOUND,KEY_UNBOUND,KEY_UNBOUND, KEY_UNBOUND,KEY_NO_EXIST, KEY_UNBOUND, KEY_UNBOUND, KEY_UNBOUND, KEY_UNBOUND, KEY_UNBOUND, KEY_UNBOUND, KEY_UNBOUND, KEY_SAVE, KEY_UNBOUND, KEY_UNBOUND, KEY_UNBOUND, KEY_UNBOUND, KEY_UNBOUND, KEY_UNBOUND, KEY_UNBOUND, KEY_UNBOUND, KEY_RESERVED, KEY_SAVE, KEY_UNBOUND, KEY_UNBOUND, KEY_UNBOUND, KEY_UNBOUND, KEY_UNBOUND, KEY_UNBOUND, KEY_UNBOUND, KEY_UNBOUND, KEY_UNBOUND, KEY_UNBOUND, KEY_UNBOUND, KEY_UNBOUND, KEY_UNBOUND, KEY_QUIT};
short kmetashift[]={KEY_NO_EXIST, KEY_LSDOWN, KEY_LSLEFT, KEY_LSRIGHT, KEY_LSUP, KEY_NO_EXIST, KEY_NO_EXIST, KEY_NO_EXIST, KEY_NO_EXIST, KEY_UNBOUND,KEY_UNBOUND,KEY_UNBOUND,KEY_UNBOUND,KEY_UNBOUND,KEY_UNBOUND,KEY_UNBOUND, KEY_NO_EXIST, KEY_UNBOUND,KEY_UNBOUND,KEY_UNBOUND,KEY_UNBOUND,KEY_UNBOUND,KEY_UNBOUND, KEY_UNBOUND,KEY_NO_EXIST, KEY_UNBOUND, KEY_UNBOUND, KEY_UNBOUND, KEY_UNBOUND, KEY_UNBOUND, KEY_UNBOUND, KEY_UNBOUND, KEY_SAVE, KEY_UNBOUND, KEY_UNBOUND, KEY_UNBOUND, KEY_UNBOUND, KEY_UNBOUND, KEY_UNBOUND, KEY_UNBOUND, KEY_UNBOUND, KEY_RESERVED, KEY_SAVE, KEY_UNBOUND, KEY_UNBOUND, KEY_UNBOUND, KEY_UNBOUND, KEY_UNBOUND, KEY_UNBOUND, KEY_UNBOUND, KEY_UNBOUND, KEY_UNBOUND, KEY_UNBOUND, KEY_UNBOUND, KEY_UNBOUND, KEY_UNBOUND, KEY_QUIT};


short ngetchx(void){
	//static bool latches[4];
	uint8_t k=0;
	while(!(k=ngetchx_backend())){
        //Sorry, user has to hold keys
        /*
		if(!latches[0]&&kb_IsDown(kb_Key2nd))
			modlatch=modlatch==1?0:1;
		if(!latches[1]&&kb_IsDown(kb_KeyAlpha))
			modlatch=modlatch==2?0:2;
		if(!latches[2]&&kb_IsDown(kb_KeyMode))
			modlatch=modlatch==3?0:3;
		if(!latches[3]&&kb_IsDown(kb_KeyGraphVar))
			modlatch=modlatch==4?0:4;
		latches[0]=kb_IsDown(kb_Key2nd);
		latches[1]=kb_IsDown(kb_KeyAlpha);
		latches[2]=kb_IsDown(kb_KeyMode);
		latches[3]=kb_IsDown(kb_KeyGraphVar);
        */
	}
    /*
	if(!modlatch){
		if(kb_IsDown(kb_Key2nd))
			modlatch=1;
		else if(kb_IsDown(kb_KeyAlpha))
			modlatch=2;
		else if(kb_IsDown(kb_KeyMode))
			modlatch=3;
		else if(kb_IsDown(kb_KeyGraphVar))
			modlatch=4;
	}
	short k2=chars[modlatch][k];
	modlatch=0;*/
    if(kb_IsDown(kb_Key2nd) && kb_IsDown(kb_KeyGraphVar)){
        return ksecshift[k];
    }else if(kb_IsDown(kb_KeyMode)&&kb_IsDown(kb_KeyAlpha)){
        return kmetashift[k];
    }else if(kb_IsDown(kb_KeyMode)){//mode=meta
        return kmeta[k];
    }else if(kb_IsDown(kb_Key2nd)){
        return ksec[k];
    }else if(kb_IsDown(kb_KeyGraphVar)){
        return kshift[k];
    }else if(kb_IsDown(kb_KeyAlpha)){
        return kalpha[k];
    }else{
        return kmain[k];
    }
}

//frontend function, handles modifier latching and returns character
char ngetchx2(void){
	static bool latches[4];
	static bool prevpolls[4];//2nd meta shift alpha
	char ret=0;
	while(1){
		kb_Scan();
		if(!prevpolls[0]&&kb_IsDown(kb_Key2nd)){
			//new keypress for 2nd key
			//Latch
			latches[0]=!latches[0];
		}
		if(!prevpolls[1]&&kb_IsDown(kb_KeyAlpha)){
			//Meta
			latches[1]=!latches[1];
		}
		if(!prevpolls[2]&&kb_IsDown(kb_KeyMode)){
			//Shift
			latches[2]=!latches[2];
		}
		if(!prevpolls[3]&&kb_IsDown(kb_KeyGraphVar)){
			//Alpha
			latches[3]=!latches[3];
		}
		prevpolls[0]=kb_IsDown(kb_Key2nd);
		prevpolls[1]=kb_IsDown(kb_KeyAlpha);
		prevpolls[2]=kb_IsDown(kb_KeyMode);
		prevpolls[3]=kb_IsDown(kb_KeyGraphVar);
		switch(ngetchx_backend()){
			case 53://f1
			case 52://f2
			case 51://f3
			case 50://f4
			case 49://f5
				//TODO TODO TODO TODO TODO TODO TODO TODO
				//TODO TODO TODO TODO TODO TODO TODO TODO
				//TODO TODO TODO TODO TODO TODO TODO TODO
				//do the function keys

			case 56://esc
				//TODO TODO TODO TODO TODO TODO TODO Do escape

			case 32://apps

			case 47://home
			case 39://mode
			case 31://catalog
			case 23://del
				//Send ascii delete?
			case 15://clear

			case 1://down
			case 2://left
			case 3://right
			case 4://up
				break;

			case 46:
				//x
				if(latches[0] || kb_IsDown(kb_Key2nd)){
					goto end;
				}
				if(latches[1] || kb_IsDown(kb_KeyAlpha)){
					goto end;
				}
				if(latches[2] || kb_IsDown(kb_KeyMode)){
					ret='X';goto end;
				}
				ret='x';
				goto end;
			case 38:
				if(latches[0] || kb_IsDown(kb_Key2nd)){
					goto end;
				}
				if(latches[1] || kb_IsDown(kb_KeyAlpha)){
					goto end;
				}
				if(latches[2] || kb_IsDown(kb_KeyMode)){
					ret='Y';goto end;
				}
				ret='y';goto end;
			case 30:
				if(latches[0] || kb_IsDown(kb_Key2nd)){
					goto end;
				}
				if(latches[1] || kb_IsDown(kb_KeyAlpha)){
					goto end;
				}
				if(latches[2] || kb_IsDown(kb_KeyMode)){
					ret='Z';goto end;
				}
				ret='z';goto end;
			case 22:
				if(latches[0] || kb_IsDown(kb_Key2nd)){
					goto end;
				}
				if(latches[1] || kb_IsDown(kb_KeyAlpha)){
					goto end;
				}
				if(latches[2] || kb_IsDown(kb_KeyMode)){
					ret='T';goto end;
				}
				ret='t';goto end;
			case 14:
				if(latches[0] || kb_IsDown(kb_Key2nd)){
					ret=1;goto end;//TODO pi
				}
				if(latches[1] || kb_IsDown(kb_KeyAlpha)){
					ret=1;goto end;//TODO theta
				}
				ret='^';
				goto end;
			case 45:
				if(latches[0] || kb_IsDown(kb_Key2nd)){
					goto end;
				}
				if(latches[1] || kb_IsDown(kb_KeyAlpha)){
					ret='e';goto end;//TODO not right
				}
				if(latches[2] || kb_IsDown(kb_KeyMode)){
					ret='A';goto end;
				}
				if(latches[3] || kb_IsDown(kb_KeyGraphVar)){
					ret='a';goto end;
				}
				ret='=';
				goto end;
			case 37:
				if(latches[0] || kb_IsDown(kb_Key2nd)){
					ret='{';goto end;
				}
				if(latches[1] || kb_IsDown(kb_KeyAlpha)){
					goto end;
				}
				if(latches[2] || kb_IsDown(kb_KeyMode)){
					ret='B';goto end;
				}
				if(latches[3] || kb_IsDown(kb_KeyGraphVar)){
					ret='b';goto end;
				}
				ret='(';
				goto end;
			case 29:
				if(latches[0] || kb_IsDown(kb_Key2nd)){
					ret='}';goto end;
				}
				if(latches[1] || kb_IsDown(kb_KeyAlpha)){
					goto end;
				}
				if(latches[2] || kb_IsDown(kb_KeyMode)){
					ret='C';goto end;
				}
				if(latches[3] || kb_IsDown(kb_KeyGraphVar)){
					ret='c';goto end;
				}
				ret=')';goto end;
			case 21:
				if(latches[0] || kb_IsDown(kb_Key2nd)){
					ret='[';goto end;
				}
				if(latches[1] || kb_IsDown(kb_KeyAlpha)){
					goto end;
				}
				if(latches[2] || kb_IsDown(kb_KeyMode)){
					ret='D';goto end;
				}
				if(latches[3] || kb_IsDown(kb_KeyGraphVar)){
					ret='d';goto end;
				}
				ret=',';goto end;
			case 13:
				if(latches[0] || kb_IsDown(kb_Key2nd)){
					ret=']';goto end;
				}
				if(latches[1] || kb_IsDown(kb_KeyAlpha)){
					goto end;
				}
				if(latches[2] || kb_IsDown(kb_KeyMode)){
					ret='E';goto end;
				}
				if(latches[3] || kb_IsDown(kb_KeyGraphVar)){
					ret='e';goto end;
				}
				ret='/';goto end;
			case 44:
				if(latches[0] || kb_IsDown(kb_Key2nd)){
					ret=1;goto end;//TODO degree
				}
				if(latches[1] || kb_IsDown(kb_KeyAlpha)){
					goto end;
				}
				if(latches[2] || kb_IsDown(kb_KeyMode)){
					ret='F';goto end;
				}
				if(latches[3] || kb_IsDown(kb_KeyGraphVar)){
					ret='f';goto end;
				}
				ret='|';goto end;
			case 36:
				if(latches[0] || kb_IsDown(kb_Key2nd)){
					goto end;
				}
				if(latches[1] || kb_IsDown(kb_KeyAlpha)){
					goto end;
				}
				if(latches[2] || kb_IsDown(kb_KeyMode)){
					ret='G';goto end;
				}
				if(latches[3] || kb_IsDown(kb_KeyGraphVar)){
					ret='g';goto end;
				}
				ret='7';goto end;
			case 28:
				if(latches[0] || kb_IsDown(kb_Key2nd)){
					goto end;
				}
				if(latches[1] || kb_IsDown(kb_KeyAlpha)){
					goto end;
				}
				if(latches[2] || kb_IsDown(kb_KeyMode)){
					ret='H';goto end;
				}
				if(latches[3] || kb_IsDown(kb_KeyGraphVar)){
					ret='h';goto end;
				}
				ret='8';goto end;
			case 20:
				if(latches[0] || kb_IsDown(kb_Key2nd)){
					ret=';';goto end;
				}
				if(latches[1] || kb_IsDown(kb_KeyAlpha)){
					goto end;
				}
				if(latches[2] || kb_IsDown(kb_KeyMode)){
					ret='I';goto end;
				}
				if(latches[3] || kb_IsDown(kb_KeyGraphVar)){
					ret='i';goto end;
				}
				ret='9';goto end;
			case 12:
				if(latches[0] || kb_IsDown(kb_Key2nd)){
					goto end;
				}
				if(latches[1] || kb_IsDown(kb_KeyAlpha)){
					goto end;
				}
				if(latches[2] || kb_IsDown(kb_KeyMode)){
					ret='J';goto end;
				}
				if(latches[3] || kb_IsDown(kb_KeyGraphVar)){
					ret='j';goto end;
				}
				ret='*';goto end;
			case 43:
				if(latches[0] || kb_IsDown(kb_Key2nd)){
					goto end;
				}
				if(latches[1] || kb_IsDown(kb_KeyAlpha)){
					goto end;
				}
				if(latches[2] || kb_IsDown(kb_KeyMode)){
					ret='K';goto end;
				}
				if(latches[3] || kb_IsDown(kb_KeyGraphVar)){
					ret='k';goto end;
				}
				ret='E';goto end;//TODO no, it's sci E.
			case 35:
				if(latches[0] || kb_IsDown(kb_Key2nd)){
					ret=':';goto end;
				}
				if(latches[1] || kb_IsDown(kb_KeyAlpha)){
					goto end;
				}
				if(latches[2] || kb_IsDown(kb_KeyMode)){
					ret='L';goto end;
				}
				if(latches[3] || kb_IsDown(kb_KeyGraphVar)){
					ret='l';goto end;
				}
				ret='4';goto end;
			case 27:
				if(latches[0] || kb_IsDown(kb_Key2nd)){
					goto end;
				}
				if(latches[1] || kb_IsDown(kb_KeyAlpha)){
					goto end;
				}
				if(latches[2] || kb_IsDown(kb_KeyMode)){
					ret='M';goto end;
				}
				if(latches[3] || kb_IsDown(kb_KeyGraphVar)){
					ret='m';goto end;
				}
				ret='5';goto end;
			case 19:
				if(latches[0] || kb_IsDown(kb_Key2nd)){
					goto end;
				}
				if(latches[1] || kb_IsDown(kb_KeyAlpha)){
					goto end;
				}
				if(latches[2] || kb_IsDown(kb_KeyMode)){
					ret='N';goto end;
				}
				if(latches[3] || kb_IsDown(kb_KeyGraphVar)){
					ret='n';goto end;
				}
				ret='6';goto end;
			case 11:
				if(latches[0] || kb_IsDown(kb_Key2nd)){
					goto end;
				}
				if(latches[1] || kb_IsDown(kb_KeyAlpha)){
					goto end;
				}
				if(latches[2] || kb_IsDown(kb_KeyMode)){
					ret='O';goto end;
				}
				if(latches[3] || kb_IsDown(kb_KeyGraphVar)){
					ret='o';goto end;
				}
				ret='-';goto end;
			case 42://store
				if(latches[0] || kb_IsDown(kb_Key2nd)){
					goto end;
				}
				if(latches[1] || kb_IsDown(kb_KeyAlpha)){
					goto end;
				}
				if(latches[2] || kb_IsDown(kb_KeyMode)){
					ret='P';goto end;
				}
				if(latches[3] || kb_IsDown(kb_KeyGraphVar)){
					ret='p';goto end;
				}
				goto end;//TODO find out about other chars
			case 34:
				if(latches[0] || kb_IsDown(kb_Key2nd)){
					ret='"';goto end;
				}
				if(latches[1] || kb_IsDown(kb_KeyAlpha)){
					goto end;
				}
				if(latches[2] || kb_IsDown(kb_KeyMode)){
					ret='Q';goto end;
				}
				if(latches[3] || kb_IsDown(kb_KeyGraphVar)){
					ret='q';goto end;
				}
				ret='1';goto end;
			case 26:
				if(latches[0] || kb_IsDown(kb_Key2nd)){
					ret='\\';goto end;
				}
				if(latches[1] || kb_IsDown(kb_KeyAlpha)){
					goto end;
				}
				if(latches[2] || kb_IsDown(kb_KeyMode)){
					ret='R';goto end;
				}
				if(latches[3] || kb_IsDown(kb_KeyGraphVar)){
					ret='r';goto end;
				}
				ret='2';goto end;
			case 18:
				if(latches[0] || kb_IsDown(kb_Key2nd)){
					goto end;
				}
				if(latches[1] || kb_IsDown(kb_KeyAlpha)){
					goto end;
				}
				if(latches[2] || kb_IsDown(kb_KeyMode)){
					ret='S';goto end;
				}
				if(latches[3] || kb_IsDown(kb_KeyGraphVar)){
					ret='s';goto end;
				}
				ret='3';goto end;
			case 10:
				if(latches[0] || kb_IsDown(kb_Key2nd)){
					goto end;//TODO show chars menu...
				}
				if(latches[1] || kb_IsDown(kb_KeyAlpha)){
					goto end;
				}
				if(latches[2] || kb_IsDown(kb_KeyMode)){
					ret='U';goto end;
				}
				if(latches[3] || kb_IsDown(kb_KeyGraphVar)){
					ret='u';goto end;
				}
				goto end;
				//case 41: os_checkbreak
			case 33:
				if(latches[0] || kb_IsDown(kb_Key2nd)){
					ret='<';goto end;
				}
				if(latches[1] || kb_IsDown(kb_KeyAlpha)){
					ret=1;goto end;//TODO <=
				}
				if(latches[2] || kb_IsDown(kb_KeyMode)){
					ret='V';goto end;
				}
				if(latches[3] || kb_IsDown(kb_KeyGraphVar)){
					ret='v';goto end;
				}
				ret='0';goto end;
			case 25:
				if(latches[0] || kb_IsDown(kb_Key2nd)){
					ret='>';goto end;
				}
				if(latches[1] || kb_IsDown(kb_KeyAlpha)){
					ret=1;goto end;//TODO >=
				}
				if(latches[2] || kb_IsDown(kb_KeyMode)){
					ret='W';goto end;
				}
				if(latches[3] || kb_IsDown(kb_KeyGraphVar)){
					ret='w';goto end;
				}
				ret='.';goto end;
			case 17:
				if(latches[0] || kb_IsDown(kb_Key2nd)){
					goto end;
				}
				if(latches[1] || kb_IsDown(kb_KeyAlpha)){
					goto end;
				}
				if(latches[2] || kb_IsDown(kb_KeyMode)){
					ret=' ';goto end;
				}
				if(latches[3] || kb_IsDown(kb_KeyGraphVar)){
					ret=' ';goto end;
				}
				ret=1;goto end;//TODO TODO other (-) sign
			case 9://TODO TODO TODO TODO TODO wtf is enter?
				if(latches[0] || kb_IsDown(kb_Key2nd)){
					goto end;
				}
				if(latches[1] || kb_IsDown(kb_KeyAlpha)){
					goto end;
				}
				if(latches[2] || kb_IsDown(kb_KeyMode)){
					goto end;
				}
				if(latches[3] || kb_IsDown(kb_KeyGraphVar)){
					goto end;
				}
				goto end;


			default:
				break;
		}
	}
end:
	latches[0]=0;
	latches[1]=0;
	latches[2]=0;
	latches[3]=0;
	return ret;
}

/*
   if(latches[0] || kb_IsDown(kb_Key2nd)){
   goto end;
   }
   if(latches[1] || kb_IsDown(kb_KeyAlpha)){
   goto end;
   }
   if(latches[2] || kb_IsDown(kb_KeyMode)){
   goto end;
   }
   if(latches[3] || kb_IsDown(kb_KeyGraphVar)){
   goto end;
   }
   goto end;
   */
//template


#endif



#endif

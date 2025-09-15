// Emacs style mode select   -*- C++ -*- 
//-----------------------------------------------------------------------------
//
// $Id:$
//
// Copyright (C) 1993-1996 by id Software, Inc.
//
// This source is available for distribution and/or modification
// only under the terms of the DOOM Source Code License as
// published by id Software. All rights reserved.
//
// The source is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// FITNESS FOR A PARTICULAR PURPOSE. See the DOOM Source Code License
// for more details.
//
// $Log:$
//
// DESCRIPTION:
//	DOOM graphics stuff for X11, UNIX.
//
//-----------------------------------------------------------------------------

#include "common.h"
#include "doomstat.h"
#include "i_system.h"
#include "v_video.h"
#include "m_argv.h"
#include "d_main.h"

#include "doomdef.h"

draw_ctx *ctx;
// byte *screen;

void I_InitGraphics (void){
	ctx = (draw_ctx*)malloc(sizeof(draw_ctx));
	request_draw_ctx(ctx);
	// screen = (byte*)malloc(SCREENWIDTH*SCREENHEIGHT*NUM_SCREENS);
}

void I_StartTic (void){
	NOT_IMPLEMENTED
}

#include "input_keycodes.h"

int xlatekey(char key)
{

    switch(key)
    {
		case KEY_LEFT:	return KEY_LEFTARROW;
		case KEY_RIGHT:	return KEY_RIGHTARROW;
		case KEY_DOWN:	return KEY_DOWNARROW;
		case KEY_UP:		return KEY_UPARROW;
		case KEY_ESC:		return KEY_ESCAPE;
		case KEY_ENTER:	return KEY_DOOM_ENTER;
		case KEY_TAB:		return KEY_DOOM_TAB;
		case KEY_F1:		return KEY_MOD_F1;
		case KEY_F2:		return KEY_MOD_F2;
		case KEY_F3:		return KEY_MOD_F3;
		case KEY_F4:		return KEY_MOD_F4;
		case KEY_F5:		return KEY_MOD_F5;
		case KEY_F6:		return KEY_MOD_F6;
		case KEY_F7:		return KEY_MOD_F7;
		case KEY_F8:		return KEY_MOD_F8;
		case KEY_F9:		return KEY_MOD_F9;
		case KEY_F10:		return KEY_MOD_F10;
		case KEY_F11:		return KEY_MOD_F11;
		case KEY_F12:		return KEY_MOD_F12;

		case KEY_BACKSPACE:
		case KEY_DELETE:	return KEY_BACKSPACE;

		case KEY_PAUSE:	return KEY_DOOM_PAUSE;

		case KEY_KPEQUAL:
		case KEY_EQUAL:	return KEY_EQUALS;

		case KEY_KPMINUS:
		case KEY_MINUS:	return KEY_DOOM_MINUS;

		case KEY_LEFTSHIFT:
		case KEY_RIGHTSHIFT: return KEY_RSHIFT;

		case KEY_RIGHTCTRL:
		case KEY_LEFTCTRL: return KEY_RCTRL;

		case KEY_LEFTALT:
		case KEY_LEFTMETA:
		case KEY_RIGHTALT:
		case KEY_RIGHTMETA: return KEY_RALT;

		default:{
			char readable = hid_keycode_to_char[key];
			if (readable){
				if (readable >= 'A' && readable <= 'Z')
					return readable - 'A' + 'a';
				else return readable;
			}
		}
		break;
	}

    return key;

}

void I_GetEvent(void)
{

    event_t event;

    // put event-grabbing stuff in here
    
	keypress kp = {};
	if (read_key(&kp)){	
		if (kp.keys[0]){
			event.type = ev_keydown;
			event.data1 = xlatekey(kp.keys[0]);
		} else event.type = ev_keyup;
		D_PostEvent(&event);
	}

    // switch (X_event.type)
    // {
    //   case KeyPress:
	// event.type = ev_keydown;
	// event.data1 = xlatekey();
	// D_PostEvent(&event);
	// // fprintf(stderr, "k");
	// break;
    //   case KeyRelease:
	// event.type = ev_keyup;
	// event.data1 = xlatekey();
	// D_PostEvent(&event);
	// // fprintf(stderr, "ku");
	// break;
    //   case ButtonPress:
	// event.type = ev_mouse;
	// event.data1 =
	//     (X_event.xbutton.state & Button1Mask)
	//     | (X_event.xbutton.state & Button2Mask ? 2 : 0)
	//     | (X_event.xbutton.state & Button3Mask ? 4 : 0)
	//     | (X_event.xbutton.button == Button1)
	//     | (X_event.xbutton.button == Button2 ? 2 : 0)
	//     | (X_event.xbutton.button == Button3 ? 4 : 0);
	// event.data2 = event.data3 = 0;
	// D_PostEvent(&event);
	// // fprintf(stderr, "b");
	// break;
    //   case ButtonRelease:
	// event.type = ev_mouse;
	// event.data1 =
	//     (X_event.xbutton.state & Button1Mask)
	//     | (X_event.xbutton.state & Button2Mask ? 2 : 0)
	//     | (X_event.xbutton.state & Button3Mask ? 4 : 0);
	// // suggest parentheses around arithmetic in operand of |
	// event.data1 =
	//     event.data1
	//     ^ (X_event.xbutton.button == Button1 ? 1 : 0)
	//     ^ (X_event.xbutton.button == Button2 ? 2 : 0)
	//     ^ (X_event.xbutton.button == Button3 ? 4 : 0);
	// event.data2 = event.data3 = 0;
	// D_PostEvent(&event);
	// // fprintf(stderr, "bu");
	// break;
    //   case MotionNotify:
	// event.type = ev_mouse;
	// event.data1 =
	//     (X_event.xmotion.state & Button1Mask)
	//     | (X_event.xmotion.state & Button2Mask ? 2 : 0)
	//     | (X_event.xmotion.state & Button3Mask ? 4 : 0);
	// event.data2 = (X_event.xmotion.x - lastmousex) << 2;
	// event.data3 = (lastmousey - X_event.xmotion.y) << 2;

	// if (event.data2 || event.data3)
	// {
	//     lastmousex = X_event.xmotion.x;
	//     lastmousey = X_event.xmotion.y;
	//     if (X_event.xmotion.x != X_width/2 &&
	// 	X_event.xmotion.y != X_height/2)
	//     {
	// 	D_PostEvent(&event);
	// 	// fprintf(stderr, "m");
	// 	mousemoved = false;
	//     } else
	//     {
	// 	mousemoved = true;
	//     }
	// }
	// break;
	
    //   case Expose:
    //   case ConfigureNotify:
	// break;
	
    //   default:
	// if (doShm && X_event.type == X_shmeventtype) shmFinished = true;
	// break;
    // }

}

void I_StartFrame(void){
	I_GetEvent();
}

void I_ShutdownGraphics(void){
	NOT_IMPLEMENTED
}

argbcolor colors[256];

// Takes full 8 bit values.
void I_SetPalette (byte* palette){
	for (int i = 0; i < 256; i++){
		colors[i].alpha = 0xFF;
		colors[i].red = gammatable[usegamma][*palette++];
		colors[i].green = gammatable[usegamma][*palette++];
		colors[i].blue = gammatable[usegamma][*palette++];
	}
}

void I_UpdateNoBlit (void){
	
}

void I_FinishUpdate (void){
	for (int i = 0; i < SCREENWIDTH*SCREENHEIGHT; i++){
		ctx->fb[i] = colors[screens[0][i]].color;
	}
	ctx->full_redraw = true;
	commit_draw_ctx(ctx);
}

void I_ReadScreen (byte* scr){
	NOT_IMPLEMENTED
}
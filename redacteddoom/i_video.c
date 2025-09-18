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

uint32_t scaleFactor = 1;
uint32_t pad_x, pad_y;


void I_InitGraphics (void){
	ctx = (draw_ctx*)malloc(sizeof(draw_ctx));
	request_draw_ctx(ctx);
	if (ctx->width < SCREENWIDTH || ctx->height < SCREENHEIGHT){
		I_Error("Game must run at at least 320x200 resolution");
	}
	scaleFactor = min(ctx->width/SCREENWIDTH,ctx->height/SCREENHEIGHT);
	pad_x = (ctx->width - (SCREENWIDTH * scaleFactor))/2;
	pad_y = (ctx->height - (SCREENHEIGHT * scaleFactor))/2;
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

keypress oldkp = {};

void I_GetEvent(void)
{

    // put event-grabbing stuff in here
    
    keypress kp = {};
    for (int j = 0; j < 10 && read_key(&kp); j++){
        for (int i = 0; i < 6; i++) {
            if (kp.keys[i] != oldkp.keys[i] && oldkp.keys[i]){
                event_t event;
                event.type = ev_keyup;
                event.data1 = xlatekey(oldkp.keys[i]);
                D_PostEvent(&event);

                if (!kp.keys[i]) continue;
            }

            event_t event;
            event.type = ev_keydown;
            event.data1 = xlatekey(kp.keys[i]);
            D_PostEvent(&event);
        }
        oldkp = kp;
    }
}

void I_StartFrame(void){
	I_GetEvent();
}

void I_ShutdownGraphics(void){
	
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
    for (int x = 0; x < SCREENWIDTH; x++) {
        for (int y = 0; y < SCREENHEIGHT; y++) {
            uint32_t color = colors[screens[0][(y * SCREENWIDTH) + x]].color;

            for (int dx = 0; dx < scaleFactor; dx++) {
                for (int dy = 0; dy < scaleFactor; dy++) {
                    ctx->fb[((y * scaleFactor + dy + pad_y) * ctx->width) + (x * scaleFactor + dx + pad_x)] = color;
                }
            }
        }
    }
    
	ctx->full_redraw = true;
	commit_draw_ctx(ctx);
}

void I_ReadScreen (byte* scr){
	NOT_IMPLEMENTED
}
#ifndef DEFINES_H
#define DEFINES_H

// Prints to the console any SDL errors
#define SDL_ERROR_CHECK(value, text) if(value) { printf(text); printf(" SDL_Error: %s\n", SDL_GetError()); }

#define SAFE_SHUTDOWN(p) if(p) { p->Shutdown(); delete p; p = NULL; }
#define SAFE_DELETE(p) if(p) { delete p; p = NULL; }

// State Enum
enum eSTATE_TYPE {BASE_STATE = 0, INTRO_STATE, MENU_STATE, OPTIONS_STATE, GAME_STATE};
enum eLAYER {BACK_LAYER = 0, MID_LAYER, FRONT_LAYER};
enum eTEXT_POS_TYPE {TOP_LEFT_POS = 0, TOP_MIDDLE_POS, TOP_RIGHT_POS, MIDDLE_POS, BOTTOM_LEFT_POS, BOTTOM_MIDDLE_POS, BOTTOM_RIGHT_POS};

// Button Defines
#define INVALID_BUTTON -1
#define QUIT_MENU_BUTTON 0
#define OPTIONS_MENU_BUTTON 1

// Misc Defines
#define MAX_INTRO_FADE 2.0f

#endif

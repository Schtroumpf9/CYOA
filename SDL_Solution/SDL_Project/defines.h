#ifndef DEFINES_H
#define DEFINES_H

// Prints to the console any SDL errors
#define SDL_ERROR_CHECK(value, text) if(value) { printf(text); printf(" SDL_Error: %s\n", SDL_GetError()); }

#define SAFE_SHUTDOWN(p) if(p) { p->Shutdown(); delete p; p = NULL; }
#define SAFE_DELETE(p) if(p) { delete p; p = NULL; }

// State Enum
enum eSTATE_TYPE {BASE_STATE = 0, INTRO_STATE, MENU_STATE, OPTIONS_STATE, GAME_STATE};
enum eLAYER {BACK = 0, MID, FRONT};
enum eTEXT_POS_TYPE {TOP_LEFT = 0, TOP_MIDDLE, TOP_RIGHT, MIDDLE, BOTTOM_LEFT, BOTTOM_MIDDLE, BOTTOM_RIGHT};

// Misc Defines
#define MAX_INTRO_FADE 2.0f

#endif

#ifndef DEFINES_H
#define DEFINES_H

// Prints to the console any SDL errors
#define SDL_ERROR_CHECK(value, text) if(value) { printf(text); printf(" SDL_Error: %s\n", SDL_GetError()); }

#define SAFE_SHUTDOWN(p) if(p) { p->Shutdown(); delete p; p = NULL; }
#define SAFE_DELETE(p) if(p) { delete p; p = NULL; }

// State Enum
enum eSTATE_TYPE {BASE_STATE = 0, INTRO_STATE, MENU_STATE, OPTIONS_STATE, GAME_STATE, TOOL_STATE};
// Image Layer Enum
enum eLAYER {BACK_LAYER = 0, MID_LAYER, FRONT_LAYER};
// Text Positions Enum
enum eQUAD_POS_TYPE {INVALID_POS = -1, TOP_LEFT_POS = 0, TOP_MIDDLE_POS, TOP_RIGHT_POS, MIDDLE_POS, BOTTOM_LEFT_POS, BOTTOM_MIDDLE_POS, BOTTOM_RIGHT_POS};
// Key State Enum
enum eKEY_STATE {KEY_STD = 0, KEY_UP, KEY_DOWN};
// Simple Quad Type Enum
enum eQUAD_TYPE {CUSTOM_QUAD = 0, SQUAREW_QUAD, SQUAREH_QUAD};

// Misc Defines
#define COMP_NAME "Blank"
#define APP_NAME "CYOA"
#define MAX_INTRO_FADE 2.0f

#define LIST_TOP 0.2f
#define LIST_LEFT 0.1f
#define LIST_WIDTH 0.7f
#define LIST_TEXT_HEIGHT 0.05f
#define LIST_DEAD_HEIGHT 0.025f
#define LIST_MAX 8

#endif

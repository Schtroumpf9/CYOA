#ifndef STRUCT_H
#define STRUCT_H

// A Rect of floats, to be used in terms of surface space
typedef struct FloatRect
{
    float x, y;
    float w, h;
} FloatRect;

typedef struct TextData
{
	float x, y;
	float pt;
	eQUAD_POS_TYPE type;
} TextData;

#endif
#ifndef STRUCT_H
#define STRUCT_H

// A Rect of floats, to be used in terms of surface space
typedef struct FloatRect
{
    float x, y;
    float w, h;

	FloatRect() { x = y = 0.0f; w = h = 1.0f; }
	FloatRect(float _x, float _y, float _w, float _h) { x = _x; y = _y; w = _w; h = _h; }
} FloatRect;

typedef struct TextData
{
	float x, y;
	float pt;
	eTEXT_POS_TYPE type;

	TextData() { x = y = 0.0f; pt = 0.1f; type = TOP_LEFT; }
	TextData(float _x, float _y, float _pt, eTEXT_POS_TYPE _type) { x = _x; y = _y; pt = _pt; type = _type; }
} TextData;

#endif
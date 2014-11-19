#include "std.h"
#include "Quad.h"

// Constructor
CQuad::CQuad(SDL_Texture* pTexture, eLAYER ucLayer, SDL_Color tColor, FloatRect tDstRect)
{
	m_pTexture = pTexture;
	m_tColor = tColor;
	m_tDstRect = tDstRect;
	m_tSrcRect.x = m_tSrcRect.y = 0.0f;
	m_tSrcRect.w = m_tSrcRect.h = 1.0f;
	m_ucLayer = ucLayer;
}

// Destructor
CQuad::~CQuad(void)
{
}

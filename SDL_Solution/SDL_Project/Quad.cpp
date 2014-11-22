#include "std.h"
#include "Quad.h"

// Constructor
CQuad::CQuad(SDL_Texture* pTexture, FloatRect tDstRect, eLAYER eLayer, eQUAD_TYPE eType, SDL_Color tColor)
{
	m_pTexture = pTexture;
	m_tColor = tColor;
	m_tDstRect = tDstRect;
	m_tSrcRect.x = m_tSrcRect.y = 0.0f;
	m_tSrcRect.w = m_tSrcRect.h = 1.0f;
	m_eLayer = eLayer;
	m_eType = eType;
}

// Destructor
CQuad::~CQuad(void)
{
}

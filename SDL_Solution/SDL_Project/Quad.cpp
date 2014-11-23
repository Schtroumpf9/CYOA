#include "std.h"
#include "Quad.h"

// Constructor
CQuad::CQuad(SDL_Texture* pTexture, FloatRect tDstRect, eQUAD_POS_TYPE ePosType, eQUAD_TYPE eType, eLAYER eLayer) :
m_tColor(SDL_Color{ 255, 255, 255, 255 })
{
	m_pTexture = pTexture;
	m_tSrcRect.x = m_tSrcRect.y = 0.0f;
	m_tSrcRect.w = m_tSrcRect.h = 1.0f;
	m_eLayer = eLayer;
	m_eType = eType;
	MoveDstQuad(tDstRect, ePosType);
}

CQuad::CQuad(SDL_Color tColor, FloatRect tDstRect, eQUAD_POS_TYPE ePosType, eQUAD_TYPE eType, eLAYER eLayer) :
m_pTexture(NULL)
{
	m_tColor = tColor;
	m_tSrcRect.x = m_tSrcRect.y = 0.0f;
	m_tSrcRect.w = m_tSrcRect.h = 1.0f;
	m_eLayer = eLayer;
	m_eType = eType;
	MoveDstQuad(tDstRect, ePosType);
}

// Destructor
CQuad::~CQuad(void)
{
}

// Public Helpers
void CQuad::MoveDstQuad(const FloatRect& tNewDstRect, eQUAD_POS_TYPE ePosType)
{
	if (ePosType != INVALID_POS)
		m_ePosType = ePosType;

	m_tDstRect = tNewDstRect;

	float x, y;
	switch (m_ePosType)
	{
	case TOP_LEFT_POS:
		m_tTrueDstRect = tNewDstRect;
		break;
	case TOP_MIDDLE_POS:
		x = tNewDstRect.x - (tNewDstRect.w / 2);
		m_tTrueDstRect = FloatRect{ x, tNewDstRect.y, tNewDstRect.w, tNewDstRect.h };
		break;
	case TOP_RIGHT_POS:
		x = tNewDstRect.x - tNewDstRect.w;
		m_tTrueDstRect = FloatRect{ x, tNewDstRect.y, tNewDstRect.w, tNewDstRect.h };
		break;
	case MIDDLE_POS:
		x = tNewDstRect.x - (tNewDstRect.w / 2);
		y = tNewDstRect.y - (tNewDstRect.h / 2);
		m_tTrueDstRect = FloatRect{ x, y, tNewDstRect.w, tNewDstRect.h };
		break;
	case BOTTOM_LEFT_POS:
		y = tNewDstRect.y - tNewDstRect.h;
		m_tTrueDstRect = FloatRect{ tNewDstRect.x, y, tNewDstRect.w, tNewDstRect.h };
		break;
	case BOTTOM_MIDDLE_POS:
		y = tNewDstRect.y - tNewDstRect.h;
		x = tNewDstRect.x - (tNewDstRect.w / 2);
		m_tTrueDstRect = FloatRect{ x, y, tNewDstRect.w, tNewDstRect.h };
		break;
	case BOTTOM_RIGHT_POS:
		y = tNewDstRect.y - tNewDstRect.h;
		x = tNewDstRect.x - tNewDstRect.w;
		m_tTrueDstRect = FloatRect{ x, y, tNewDstRect.w, tNewDstRect.h };
		break;
	default:
		break;
	}
}
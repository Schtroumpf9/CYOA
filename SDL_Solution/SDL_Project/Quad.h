#ifndef QUAD_H
#define QUAD_H

#include "structs.h"

class CQuad
{
public:
	// Constructors
	CQuad(SDL_Texture* pTexture, FloatRect tDstRect = { 0.0f, 0.0f, 1.0f, 1.0f }, eQUAD_POS_TYPE ePosType = TOP_LEFT_POS, eQUAD_TYPE eType = CUSTOM_QUAD, eLAYER eLayer = MID_LAYER);
	CQuad(SDL_Color tColor, FloatRect tDstRect = { 0.0f, 0.0f, 1.0f, 1.0f }, eQUAD_POS_TYPE ePosType = TOP_LEFT_POS, eQUAD_TYPE eType = CUSTOM_QUAD, eLAYER eLayer = MID_LAYER);
	// Destructors
	~CQuad(void);

	// Mutators
	inline void SetColor(SDL_Color tColor) { m_tColor = tColor; }
	inline void SetSrcRect(FloatRect tSrcRect) { m_tSrcRect = tSrcRect; }
	inline void SetTexture(SDL_Texture* pTexture) { m_pTexture = pTexture; }
	
	// Accessors
	inline SDL_Color GetColor(void) const { return m_tColor; }
	inline FloatRect GetSrcRect(void) const { return m_tSrcRect; }
	inline FloatRect GetDstRect(void) const { return m_tDstRect; }
	inline SDL_Texture* GetTexture(void) const { return m_pTexture; }
	inline SDL_Rect GetPixelDstRect(void) const { return m_tPixelDstRect; }
	inline SDL_Rect GetPixelSrcRect(void) const { return m_tPixelSrcRect; }
	inline eLAYER GetLayer(void) const { return m_eLayer; }
	inline eQUAD_TYPE GetQuadType(void) const { return m_eType; }

	// Public Helpers
	void MoveDstQuad(const FloatRect& tNewDstRect, eQUAD_POS_TYPE ePosType = INVALID_POS);

	friend class CRenderManager;
protected:
	inline void SetPixelDstRect(SDL_Rect tPixelDstRect) { m_tPixelDstRect = tPixelDstRect; }
	inline void SetPixelSrcRect(SDL_Rect tPixelSrcRect) { m_tPixelSrcRect = tPixelSrcRect; }
	inline FloatRect GetTrueDstRect(void) const { return m_tTrueDstRect; }

private:
	// Quad data
	SDL_Texture* m_pTexture;
	SDL_Color m_tColor;
	FloatRect m_tDstRect;
	FloatRect m_tTrueDstRect;
	FloatRect m_tSrcRect;
	eLAYER m_eLayer;
	eQUAD_TYPE m_eType;
	eQUAD_POS_TYPE m_ePosType;

	// Pixel Rects
	SDL_Rect m_tPixelDstRect;
	SDL_Rect m_tPixelSrcRect;
};
#endif

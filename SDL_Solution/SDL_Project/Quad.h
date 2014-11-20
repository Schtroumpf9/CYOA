#ifndef QUAD_H
#define QUAD_H

#include "structs.h"

class CQuad
{
public:
	// Constructors
	CQuad(SDL_Texture* pTexture = NULL, eLAYER ucLayer = MID_LAYER, SDL_Color tColor = { 255, 255, 255, 255 }, FloatRect tDstRect = { 0.0f, 0.0f, 1.0f, 1.0f });
	// Destructors
	~CQuad(void);

	// Mutators
	inline void SetColor(SDL_Color tColor) { m_tColor = tColor; }
	inline void SetSrcRect(FloatRect tSrcRect) { m_tSrcRect = tSrcRect; }
	inline void SetDstRect(FloatRect tDstRect) { m_tDstRect = tDstRect; }
	inline void SetTexture(SDL_Texture* pTexture) { m_pTexture = pTexture; }
	inline void SetPixelDstRect(SDL_Rect tPixelDstRect) { m_tPixelDstRect = tPixelDstRect; }
	inline void SetPixelSrcRect(SDL_Rect tPixelSrcRect) { m_tPixelSrcRect = tPixelSrcRect; }
	inline void SetLayer(eLAYER ucLayer) { m_ucLayer = ucLayer; }
	// Accessors
	inline SDL_Color GetColor(void) const { return m_tColor; }
	inline FloatRect GetSrcRect(void) const { return m_tSrcRect; }
	inline FloatRect GetDstRect(void) const { return m_tDstRect; }
	inline SDL_Texture* GetTexture(void) const { return m_pTexture; }
	inline SDL_Rect GetPixelDstRect(void) const { return m_tPixelDstRect; }
	inline SDL_Rect GetPixelSrcRect(void) const { return m_tPixelSrcRect; }
	inline eLAYER GetLayer(void) const { return m_ucLayer; }

private:
	// Quad data
	SDL_Texture* m_pTexture;
	SDL_Color m_tColor;
	FloatRect m_tDstRect;
	FloatRect m_tSrcRect;
	eLAYER m_ucLayer;

	// Pixel Rects
	SDL_Rect m_tPixelDstRect;
	SDL_Rect m_tPixelSrcRect;
};
#endif

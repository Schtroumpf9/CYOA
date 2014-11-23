#ifndef FONT_MANAGER_H
#define FONT_MANAGER_H

#include <SDL_ttf.h>
#include "structs.h"

class CRenderManager;
class CQuad;

class CFontManager
{
public:
	CFontManager(void);
	~CFontManager(void);

	void Initialize(CRenderManager* pRenderManager);
	void Shutdown(void);
	
	CQuad* TTFCreateText(const char* szText, const SDL_Color& tColor = { 255, 255, 255, 255 }, const TextData& tData = { 0.0f, 0.0f, 0.1f, TOP_LEFT_POS });

	void TTFChangeText(CQuad* out_pQuad, const char* szText, const SDL_Color& tColor = { 255, 255, 255, 255 });

	void TTFChangeTextData(CQuad* out_pQuad, const TextData& tData);

private:
	SDL_Texture* TTFLoadText(float& out_fWidth, const char* szText, const SDL_Color& tColor, const float fHeight);

	TTF_Font* m_pTTFont;
	CRenderManager* m_pRenderManager;
};
#endif

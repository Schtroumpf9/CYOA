#include "std.h"
#include "FontManager.h"
#include "Quad.h"
#include "RenderManager.h"

CFontManager::CFontManager(void) : m_pTTFont(NULL), m_pRenderManager(NULL)
{
}


CFontManager::~CFontManager(void)
{
}

void CFontManager::Initialize(CRenderManager* pRenderManager)
{
	m_pRenderManager = pRenderManager;

	SDL_ERROR_CHECK(TTF_Init() == -1, "SDL_ttf could not initialize!");

	m_pTTFont = TTF_OpenFont("../Fonts/unispace.ttf", 72);
	TTF_SetFontHinting(m_pTTFont, TTF_HINTING_LIGHT);
}

void CFontManager::Shutdown(void)
{
	TTF_CloseFont(m_pTTFont);
	TTF_Quit();
}

CQuad* CFontManager::TTFCreateText(const char* szText, const SDL_Color& tColor, const TextData& tData, const eLAYER eLayer)
{
	float fWidth;
	SDL_Texture* pTexture = TTFLoadText(fWidth, szText, tColor, tData.pt);
	FloatRect tDstRect = { tData.x, tData.y, fWidth, tData.pt };
	CQuad* pQuad = new CQuad(pTexture, tDstRect, tData.type, CUSTOM_QUAD, eLayer);
	pQuad->SetColor(tColor);
	m_pRenderManager->AddQuad(pQuad);
	return pQuad;
}

void CFontManager::TTFChangeText(CQuad* out_pQuad, const char* szText, const SDL_Color& tColor)
{
	SDL_DestroyTexture(out_pQuad->GetTexture());
	FloatRect tDstRect = out_pQuad->GetDstRect();
	out_pQuad->SetTexture(TTFLoadText(tDstRect.w, szText, tColor, tDstRect.h));
	out_pQuad->MoveDstQuad(tDstRect);
	m_pRenderManager->UpdateQuad(out_pQuad);
}

void CFontManager::TTFChangeTextData(CQuad* out_pQuad, const TextData& tData)
{
	FloatRect tDstRect = out_pQuad->GetDstRect();
	float newWidth = (tDstRect.w / tDstRect.h) * tData.pt;
	tDstRect.w = newWidth;
	out_pQuad->MoveDstQuad(tDstRect);
	m_pRenderManager->UpdateQuad(out_pQuad);
}

// Helpers
SDL_Texture* CFontManager::TTFLoadText(float& out_fWidth, const char* szText, const SDL_Color& tColor, const float fHeight)
{
	SDL_Surface* pTextSurface = TTF_RenderText_Blended(m_pTTFont, szText, tColor);
	SDL_ERROR_CHECK(pTextSurface == NULL, "Unable to load text surface!");

	SDL_Texture* pTextTexture = SDL_CreateTextureFromSurface(m_pRenderManager->GetRenderer(), pTextSurface);
	SDL_ERROR_CHECK(pTextTexture == NULL, "Unable to create texture from text surface!");

	out_fWidth = (static_cast<float>(pTextSurface->w) / pTextSurface->h) * fHeight;

	SDL_FreeSurface(pTextSurface);

	return pTextTexture;
}

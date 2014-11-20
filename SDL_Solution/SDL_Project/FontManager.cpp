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

	m_pTTFont = TTF_OpenFont("../Fonts/vgaoem.fon", 72);
}

void CFontManager::Shutdown(void)
{
	TTF_CloseFont(m_pTTFont);
	TTF_Quit();
}

CQuad* CFontManager::TTFCreateText(const char* szText, const SDL_Color& tColor, const TextData& tData)
{
	CQuad* pQuad;
	float fWidth;
	FloatRect tDstRect;
	SDL_Texture* pTexture = TTFLoadText(fWidth, szText, tColor, tData.pt);
	SetTextDstRect(tDstRect, tData, fWidth);
	pQuad = new CQuad(pTexture, FRONT_LAYER, tColor, tDstRect);
	m_pRenderManager->AddQuad(pQuad);
	return pQuad;
}

void CFontManager::TTFChangeText(CQuad* out_pQuad, const char* szText, const SDL_Color& tColor)
{
	SDL_DestroyTexture(out_pQuad->GetTexture());
	FloatRect tDstRect = out_pQuad->GetDstRect();
	out_pQuad->SetTexture(TTFLoadText(tDstRect.w, szText, tColor, tDstRect.h));
	out_pQuad->SetDstRect(tDstRect);
}

void CFontManager::TTFChangeTextData(CQuad* out_pQuad, const TextData& tData)
{
	FloatRect tDstRect = out_pQuad->GetDstRect();
	float newWidth = (tDstRect.w / tDstRect.h) * tData.pt;
	SetTextDstRect(tDstRect, tData, newWidth);
	out_pQuad->SetDstRect(tDstRect);
	m_pRenderManager->UpdateQuad(out_pQuad);
}

// Helpers
SDL_Texture* CFontManager::TTFLoadText(float& out_fWidth, const char* szText, const SDL_Color& tColor, const float fHeight)
{
	SDL_Surface* pTextSurface = TTF_RenderText_Solid(m_pTTFont, szText, tColor);
	SDL_ERROR_CHECK(pTextSurface == NULL, "Unable to load text surface!");

	SDL_Texture* pTextTexture = SDL_CreateTextureFromSurface(m_pRenderManager->GetRenderer(), pTextSurface);
	SDL_ERROR_CHECK(pTextTexture == NULL, "Unable to create texture from text surface!");

	out_fWidth = (pTextSurface->w / pTextSurface->h) * fHeight;

	SDL_FreeSurface(pTextSurface);

	return pTextTexture;
}

void CFontManager::SetTextDstRect(FloatRect& out_tDstRect, const TextData& tData, const float width)
{
	float x, y;
	switch (tData.type)
	{
	case TOP_LEFT_POS:
		out_tDstRect = FloatRect{ tData.x, tData.y, width, tData.pt };
		break;
	case TOP_MIDDLE_POS:
		x = tData.x - (width / 2);
		out_tDstRect = FloatRect{ x, tData.y, width, tData.pt };
		break;
	case TOP_RIGHT_POS:
		x = tData.x - width;
		out_tDstRect = FloatRect{ x, tData.y, width, tData.pt };
		break;
	case MIDDLE_POS:
		x = tData.x - (width / 2);
		y = tData.y - (tData.pt / 2);
		out_tDstRect = FloatRect{ x, y, width, tData.pt };
		break;
	case BOTTOM_LEFT_POS:
		y = tData.y - tData.pt;
		out_tDstRect = FloatRect{ tData.x, y, width, tData.pt };
		break;
	case BOTTOM_MIDDLE_POS:
		y = tData.y - tData.pt;
		x = tData.x - (width / 2);
		out_tDstRect = FloatRect{ x, y, width, tData.pt };
		break;
	case BOTTOM_RIGHT_POS:
		y = tData.y - tData.pt;
		x = tData.x - width;
		out_tDstRect = FloatRect{ x, y, width, tData.pt };
		break;
	default:
		break;
	}
}

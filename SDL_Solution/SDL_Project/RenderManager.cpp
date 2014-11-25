#include "std.h"
#include "RenderManager.h"
#include <SDL_image.h>
#include "Quad.h"

// Class Functions
CRenderManager::CRenderManager(void) : m_tWindowSize(SDL_Point{ 960, 640 }), m_bFullscreen(false), m_pWindow(NULL), m_pRenderer(NULL)
{
}

CRenderManager::~CRenderManager(void)
{
}

void CRenderManager::Initialize(void)
{
	m_pWindow = SDL_CreateWindow(APP_NAME, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, m_tWindowSize.x, m_tWindowSize.y, SDL_WINDOW_SHOWN | SDL_WINDOW_MOUSE_FOCUS | SDL_WINDOW_RESIZABLE);
	SDL_ERROR_CHECK(m_pWindow == NULL, "Window failed to create.");

	m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	SDL_ERROR_CHECK(m_pRenderer == NULL, "Renderer failed to create.");

	SDL_ERROR_CHECK(SDL_SetRenderDrawBlendMode(m_pRenderer, SDL_BLENDMODE_BLEND) < 0, "Renderer failed to set Blend Mode");

	SDL_ERROR_CHECK(SDL_SetRenderDrawColor(m_pRenderer, 0, 255, 255, 255) < 0, "Draw color failed to be set.");

	SDL_ERROR_CHECK((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) == 0, "IMG extension failed to initialize.");

	m_unDisplayIndex = SDL_GetWindowDisplayIndex(m_pWindow);
	SDL_GetCurrentDisplayMode(m_unDisplayIndex, &m_tDisplayMode);
	//m_fAspectRatio = static_cast<float>(m_tDisplayMode.w) / m_tDisplayMode.h;
	m_fAspectRatio = 3 / 2;
	m_tFittedSize = m_tWindowSize;
	m_tFittedOffset = SDL_Point{ 0, 0 };
}

void CRenderManager::Render(void)
{
	//Clear screen
	SDL_RenderClear(m_pRenderer);

	// Render Textures
	RenderQuads();

	//Update screen
	SDL_RenderPresent(m_pRenderer);
}

void CRenderManager::Resize(const SDL_Point& tWindowSize)
{
	m_tWindowSize.x = tWindowSize.x;
	m_tWindowSize.y = tWindowSize.y;

	SDL_Point tSizeDiff{ tWindowSize.x - m_tFittedSize.x, tWindowSize.y - m_tFittedSize.y };
	tSizeDiff.y = static_cast<int>(tSizeDiff.y * m_fAspectRatio);
	if ((tSizeDiff.x < tSizeDiff.y && tSizeDiff.x < 0) || 
		(tSizeDiff.x < tSizeDiff.y && tSizeDiff.x > 0)) // sizing horizontally
	{
		m_tFittedSize.x = m_tWindowSize.x;
		m_tFittedSize.y = static_cast<int>(m_tFittedSize.x / m_fAspectRatio);
	}
	else if ((tSizeDiff.y < tSizeDiff.x && tSizeDiff.y < 0) ||
		(tSizeDiff.y < tSizeDiff.x && tSizeDiff.y > 0)) // sizing vertically
	{
		m_tFittedSize.y = m_tWindowSize.y;
		m_tFittedSize.x = static_cast<int>(m_tFittedSize.y * m_fAspectRatio);
	}

	m_tFittedOffset.x = m_tWindowSize.x / 2 - m_tFittedSize.x / 2;
	m_tFittedOffset.y = m_tWindowSize.y / 2 - m_tFittedSize.y / 2;

	// Resize all quads to be appropriate dimensions
	std::forward_list<CQuad*>::iterator quadIter = m_Quads.begin();
	for (; quadIter != m_Quads.cend(); ++quadIter)
	{
		UpdateQuad(*quadIter);
	}
}

void CRenderManager::Shutdown(void)
{
	DeleteAllQuads();

	SDL_DestroyRenderer(m_pRenderer);
	m_pRenderer = NULL;

	SDL_DestroyWindow(m_pWindow);
	m_pWindow = NULL;

	IMG_Quit();
}

void CRenderManager::AddQuad(CQuad* pQuad)
{
	UpdateQuad(pQuad);

	std::forward_list<CQuad*>::const_iterator quadIter = m_Quads.cbegin();
	if (!m_Quads.empty() && (*quadIter)->GetLayer() <= pQuad->GetLayer())
	{
		std::forward_list<CQuad*>::const_iterator prevQuadIter = quadIter++;
		if (quadIter != m_Quads.cend())
		{
			for (; quadIter != m_Quads.cend(); prevQuadIter = quadIter++)
			{
				if ((*quadIter)->GetLayer() > pQuad->GetLayer())
				{
					m_Quads.insert_after(prevQuadIter, pQuad);
					return;
				}
			}
		}
		m_Quads.insert_after(prevQuadIter, pQuad);
		return;
	}
	m_Quads.push_front(pQuad);
}

void CRenderManager::RemoveQuad(CQuad* pQuad)
{
	std::forward_list<CQuad*>::const_iterator quadIter;
	for (quadIter = m_Quads.cbegin(); quadIter != m_Quads.cend(); ++quadIter)
	{
		if (pQuad == (*quadIter))
		{
			m_Quads.remove(pQuad);
		}
	}
}

void CRenderManager::DeleteAllQuads(void)
{
	std::forward_list<CQuad*>::iterator quadIter = m_Quads.begin();
	for (; quadIter != m_Quads.cend(); ++quadIter)
	{
		SAFE_DELETE((*quadIter));
	}
	m_Quads.clear();
}

void CRenderManager::UpdateQuad(CQuad* pQuad)
{
	// Set Quad Data in terms of the Window size
	SDL_Rect tPixelDstRect;
	tPixelDstRect.x = static_cast<int>(pQuad->GetTrueDstRect().x * m_tFittedSize.x);
	tPixelDstRect.y = static_cast<int>(pQuad->GetTrueDstRect().y * m_tFittedSize.y);
	switch (pQuad->GetQuadType())
	{
	case CUSTOM_QUAD:
	{
		tPixelDstRect.w = static_cast<int>(pQuad->GetTrueDstRect().w * m_tFittedSize.x);
		tPixelDstRect.h = static_cast<int>(pQuad->GetTrueDstRect().h * m_tFittedSize.y);
		break;
	}
	case SQUAREW_QUAD:
	{
		tPixelDstRect.w = static_cast<int>(pQuad->GetTrueDstRect().w * m_tFittedSize.x);
		tPixelDstRect.h = tPixelDstRect.w;
		break;
	}
	case SQUAREH_QUAD:
	{
		tPixelDstRect.h = static_cast<int>(pQuad->GetTrueDstRect().h * m_tFittedSize.y);
		tPixelDstRect.w = tPixelDstRect.h;
		break;
	}
	default:
		break;
	}

	tPixelDstRect.x += m_tFittedOffset.x/* + m_tFittedSize.x / 20*/;
	tPixelDstRect.y += m_tFittedOffset.y/* + m_tFittedSize.y / 20*/;
	pQuad->SetPixelDstRect(tPixelDstRect);
}

// Private Helpers
void CRenderManager::RenderQuads(void)
{
	CQuad* curQuad;
	SDL_Texture* curTexture;
	SDL_Color curColor;
	SDL_Rect tDstRect;
	//SDL_Rect tSrcRect;

	std::forward_list<CQuad*>::iterator quadIter = m_Quads.begin();
	for (; quadIter != m_Quads.cend(); ++quadIter)
	{
		curQuad = (*quadIter);
		curTexture = curQuad->GetTexture();
		curColor = curQuad->GetColor();
		tDstRect = curQuad->GetPixelDstRect();

		// Draw colored rect or texture
		if (curTexture)
		{
			SDL_SetTextureColorMod(curTexture, curColor.r, curColor.g, curColor.b);
			SDL_SetTextureAlphaMod(curTexture, curColor.a);
			SDL_RenderCopy(m_pRenderer, curTexture, NULL, &tDstRect);
		}
		else
		{
			SDL_SetRenderDrawColor(m_pRenderer, curColor.r, curColor.g, curColor.b, curColor.a);
			SDL_RenderFillRect(m_pRenderer, &tDstRect);
			SDL_SetRenderDrawColor(m_pRenderer, 0, 255, 255, 255);
		}
	}
}

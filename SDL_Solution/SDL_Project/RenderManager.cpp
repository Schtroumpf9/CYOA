#include "std.h"
#include "RenderManager.h"
#include <SDL_image.h>
#include "Quad.h"

// Class Functions
CRenderManager::CRenderManager(void) : m_unWindowWidth(1600), m_unWindowHeight(900), m_bFullscreen(false), m_pWindow(NULL), m_pRenderer(NULL)
{
}

CRenderManager::~CRenderManager(void)
{
}

void CRenderManager::Initialize(void)
{
	m_pWindow = SDL_CreateWindow("SDL Project", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, m_unWindowWidth, m_unWindowHeight, SDL_WINDOW_SHOWN | SDL_WINDOW_MOUSE_FOCUS | SDL_WINDOW_RESIZABLE);
	SDL_ERROR_CHECK(m_pWindow == NULL, "Window failed to create.");

	m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	SDL_ERROR_CHECK(m_pRenderer == NULL, "Renderer failed to create.");

	SDL_ERROR_CHECK(SDL_SetRenderDrawColor(m_pRenderer, 0, 255, 255, 255) < 0, "Draw color failed to be set.");

	SDL_ERROR_CHECK((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) == 0, "IMG extension failed to initialize.");
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
	m_unWindowWidth = (Uint32)tWindowSize.x;
	m_unWindowHeight = (Uint32)tWindowSize.y;

	// Resize all quads to be appropriate dimensions
	std::forward_list<CQuad*>::iterator quadIter = m_Quads.begin();
	for (; quadIter != m_Quads.cend(); ++quadIter)
	{
		UpdateQuad((*quadIter));
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
			// TODO: Determine whether or not to delete Quad as well
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
	tPixelDstRect.x = static_cast<int>(pQuad->GetDstRect().x * m_unWindowWidth);
	tPixelDstRect.y = static_cast<int>(pQuad->GetDstRect().y * m_unWindowHeight);
	tPixelDstRect.w = static_cast<int>(pQuad->GetDstRect().w * m_unWindowWidth);
	tPixelDstRect.h = static_cast<int>(pQuad->GetDstRect().h * m_unWindowHeight);

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

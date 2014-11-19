#include "std.h"
#include "GameState.h"


CGameState::CGameState(void)
{
	m_eType = GAME_STATE;
}


CGameState::~CGameState(void)
{
}

void CGameState::Initialize(CRenderManager* pRenderManager, CTextureManager* pTextureManager,
	CInputManager* pInputManager, CFontManager* pFontManager)
{
	CBaseState::Initialize(pRenderManager, pTextureManager, pInputManager, pFontManager);

	// Add Initial Images
	SDL_Color color {255, 0, 255, 255};
	FloatRect dstRect = {0.0f, 0.0f, 0.25f, 0.25f};
	CQuad* pQuad;
	CreateQuad(NULL, dstRect, MID, color);

	color.a = 127;
	dstRect.y = 0.75f;
	dstRect.w = 1.0f;
	CreateQuad("Vacation.png", dstRect, MID, color);

	color.a = 255;
	color.b = 0;
	dstRect.x = 0.25f;
	dstRect.y = 0.25f;
	dstRect.w = 0.5f;
	dstRect.h = 0.5f;
	pQuad = CreateQuad(NULL, dstRect, MID, color);
	m_Buttons.push_front(pQuad);

	color.g = 255;
	color.b = 255;
	dstRect.x = 0.75f;
	dstRect.y = 0.0f;
	dstRect.w = 0.25f;
	dstRect.h = 1.0f;
	CreateQuad("Vacation.png", dstRect, MID, color);
}

eSTATE_TYPE CGameState::Update(float fDeltaTime)
{
	if(m_pInputManager->SelectEvent())
	{
		SDL_Rect buttonRect;
		SDL_Point selectPos = m_pInputManager->GetSelectPoint();
		std::forward_list<CQuad*>::iterator buttonIter = m_Buttons.begin();
		for(; buttonIter != m_Buttons.cend(); ++buttonIter)
		{
			buttonRect = (*buttonIter)->GetPixelDstRect();

			// SDL_PointInRect in 2.0.4
			if(PointInRect(&selectPos, &buttonRect) == SDL_TRUE)
			{
				// Do Stuff for this button
				return MENU_STATE;
			}
		}
	}

	return CBaseState::Update(fDeltaTime);
}

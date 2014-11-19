#include "std.h"
#include "MenuState.h"


CMenuState::CMenuState(void)
{
	m_eType = MENU_STATE;
}


CMenuState::~CMenuState(void)
{
}

void CMenuState::Initialize(CRenderManager* pRenderManager, CTextureManager* pTextureManager,
	CInputManager* pInputManager, CFontManager* pFontManager)
{
	CBaseState::Initialize(pRenderManager, pTextureManager, pInputManager, pFontManager);

	// Add Initial Images
	CQuad* pQuad;
	CQuad* pText;
	float fWidth;

	// Background
	CreateQuad(NULL, FloatRect{ 0.f, 0.f, 1.f, 1.f }, BACK, SDL_Color{ 0, 0, 0, 255 });

	// Options Text
	pText = m_pFontManager->TTFCreateText("Options", SDL_Color{ 0, 255, 0, 255 }, TextData{ .05f, .05f, .025f, TOP_LEFT });

	// Options Button
	fWidth = pText->GetDstRect().w + 0.075f;
	pQuad = CreateQuad(NULL, FloatRect{ 0.f, 0.f, fWidth, .1f }, MID, SDL_Color{ 0, 95, 0, 255 });
	m_Buttons.push_front(pQuad);

	// Options Back
	fWidth -= 0.0125f;
	CreateQuad(NULL, FloatRect{ 0.f, 0.f, fWidth, .0875f }, MID, SDL_Color{ 63, 63, 63, 255 });

	// Quit Text
	pText = m_pFontManager->TTFCreateText("Quit", SDL_Color{ 255, 0, 0, 255 }, TextData{ .95f, .05f, .025f, TOP_RIGHT });

	// Quit Button
	fWidth = pText->GetDstRect().w + 0.075f;
	pQuad = CreateQuad(NULL, FloatRect{ 1.f - fWidth, 0.f, fWidth, .1f }, MID, SDL_Color{ 95, 0, 0, 255 });
	m_Buttons.push_front(pQuad);

	fWidth -= 0.0125f;
	CreateQuad(NULL, FloatRect{ 1.f - fWidth, 0.f, fWidth, .0875f }, MID, SDL_Color{ 63, 63, 63, 255 });

	// Menu Text
	pText = m_pFontManager->TTFCreateText("Play", SDL_Color{ 0, 127, 127, 255 }, TextData{ .5f, .5f, .1f, MIDDLE });
}

eSTATE_TYPE CMenuState::Update(float fDeltaTime)
{
	if (m_pInputManager->SelectEvent())
	{
		SDL_Rect buttonRect;
		SDL_Point selectPos = m_pInputManager->GetSelectPoint();
		std::forward_list<CQuad*>::iterator buttonIter = m_Buttons.begin();
		for (; buttonIter != m_Buttons.cend(); ++buttonIter)
		{
			buttonRect = (*buttonIter)->GetPixelDstRect();

			if (PointInRect(&selectPos, &buttonRect) == SDL_TRUE)
			{
				return OPTIONS_STATE;
			}
		}
	}

	return CBaseState::Update(fDeltaTime);
}


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

	// Background
	CreateQuad(NULL, FloatRect{ 0.f, 0.f, 1.f, 1.f }, BACK_LAYER/*, SDL_Color{ 0, 0, 0, 255 }*/);

	// Options Button
	m_Buttons[OPTIONS_MENU_BUTTON] = CreateQuad("OptionsButton.png", FloatRect{ .028125f, .05f, .05625f, .1f }, MID_LAYER, SDL_Color{ 127, 127, 127, 255 });

	// Quit Button
	m_Buttons[QUIT_MENU_BUTTON] = CreateQuad("QuitButton.png", FloatRect{ 1.f - .028125f - .05625f, .05f, .05625f, .1f }, MID_LAYER, SDL_Color{ 127, 0, 0, 255 });

	// Menu Buttons
	SDL_Color tColor = { 0, 0, 0, 255 };
	m_Buttons[CHOOSE_MENU_BUTTON] = m_pFontManager->TTFCreateText("Choose", tColor, TextData{ .45f, .45f, .05f, BOTTOM_RIGHT_POS });

	m_Buttons[CREATE_MENU_BUTTON] = m_pFontManager->TTFCreateText("Create", tColor, TextData{ .45f, .55f, .05f, TOP_RIGHT_POS });

	m_pFontManager->TTFCreateText("Your Own Adventure", tColor, TextData{ .55f, .475f, .05f, TOP_LEFT_POS });
}

eSTATE_TYPE CMenuState::Update(float fDeltaTime)
{
	SDL_Event tEvent;

	// Escape to Quit
	if (m_pInputManager->KeyEvent(SDLK_ESCAPE, KEY_UP))
	{
		tEvent.type = SDL_QUIT;
		SDL_PushEvent(&tEvent);
	}

	ProcessButtons();

	if (m_sOverKey != INVALID_BUTTON)
	{
		if (m_pInputManager->SelectorUpEvent())
		{
			m_pInputManager->SetArrowCursor();
			switch (m_sOverKey)
			{
			case QUIT_MENU_BUTTON:
				tEvent.type = SDL_QUIT;
				SDL_PushEvent(&tEvent);
				break;
			case OPTIONS_MENU_BUTTON:
				return OPTIONS_STATE;
			}
		}
	}

	return CBaseState::Update(fDeltaTime);
}


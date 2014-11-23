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

	// Background
	CreateQuad(SDL_Color{ 0, 0, 0, 255 }, FloatRect{ 0.f, 0.f, 1.f, 1.f }, TOP_LEFT_POS, CUSTOM_QUAD, BACK_LAYER);

	// Options Button
	pQuad = CreateQuad("OptionsButton.png", FloatRect{ 0.05f, 0.05f, .1f, .1f }, TOP_LEFT_POS, SQUAREH_QUAD);
	pQuad->SetColor(SDL_Color{ 127, 127, 127, 255 });
	m_Buttons[OPTIONS_MENU_BUTTON] = pQuad;

	// Quit Button
	pQuad = CreateQuad("QuitButton.png", FloatRect{ .95f, .05f, .1f, .1f }, TOP_RIGHT_POS, SQUAREH_QUAD);
	pQuad->SetColor(SDL_Color{ 127, 0, 0, 255 });
	m_Buttons[QUIT_MENU_BUTTON] = pQuad;

	// Menu Buttons
	SDL_Color tColor = { 0, 255, 0, 255 };
	m_Buttons[CHOOSE_MENU_BUTTON] = m_pFontManager->TTFCreateText("Choose", tColor, TextData{ .33f, .45f, .05f, BOTTOM_RIGHT_POS });

	m_Buttons[CREATE_MENU_BUTTON] = m_pFontManager->TTFCreateText("Create", tColor, TextData{ .33f, .55f, .05f, TOP_RIGHT_POS });

	m_pFontManager->TTFCreateText("Your Own Adventure", tColor, TextData{ .43f, .475f, .05f, TOP_LEFT_POS });

	// Menu Fluff
	pQuad = CreateQuad("MenuBracket.png", FloatRect{ .33f, .425f, .1f, .15f });
	pQuad->SetColor(SDL_Color{ 0, 127, 0, 255 });
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
			case CHOOSE_MENU_BUTTON:
				return GAME_STATE;
			case CREATE_MENU_BUTTON:
				return TOOL_STATE;
			default:
				break;
			}
		}
	}

	return CBaseState::Update(fDeltaTime);
}


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

	// Menu Fluff
	pQuad = CreateQuad("MenuBracket.png", FloatRect{ .33f, .425f, .1f, .15f });
	pQuad->SetColor(SDL_Color{ 0, 127, 0, 255 });

	// Buttons
	m_ucNumButtons = NUM_BTNS;
	m_ppButtons = new CQuad*[m_ucNumButtons];

	// Options Button
	pQuad = CreateQuad("OptionsButton.png", FloatRect{ 0.05f, 0.05f, .1f, .1f }, TOP_LEFT_POS, SQUAREH_QUAD);
	pQuad->SetColor(SDL_Color{ 127, 127, 127, 255 });
	m_ppButtons[OPTIONS_BTN] = pQuad;

	// Quit Button
	pQuad = CreateQuad("QuitButton.png", FloatRect{ .95f, .05f, .1f, .1f }, TOP_RIGHT_POS, SQUAREH_QUAD);
	pQuad->SetColor(SDL_Color{ 127, 0, 0, 255 });
	m_ppButtons[QUIT_BTN] = pQuad;

	// Menu Buttons
	SDL_Color tColor = { 0, 255, 0, 255 };
	m_ppButtons[CHOOSE_BTN] = m_pFontManager->TTFCreateText("Choose", tColor, TextData{ .33f, .45f, .05f, BOTTOM_RIGHT_POS });

	m_ppButtons[CREATE_BTN] = m_pFontManager->TTFCreateText("Create", tColor, TextData{ .33f, .55f, .05f, TOP_RIGHT_POS });

	m_pFontManager->TTFCreateText("Your Own Adventure", tColor, TextData{ .43f, .475f, .05f, TOP_LEFT_POS });
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

	if (m_cOverKey != INVALID_BUTTON)
	{
		if (m_pInputManager->SelectorUpEvent())
		{
			m_pInputManager->SetCursor(SDL_SYSTEM_CURSOR_ARROW);
			switch (m_cOverKey)
			{
			case QUIT_BTN:
				tEvent.type = SDL_QUIT;
				SDL_PushEvent(&tEvent);
				break;
			case OPTIONS_BTN:
				return OPTIONS_STATE;
			case CHOOSE_BTN:
				return GAME_STATE;
			case CREATE_BTN:
				return TOOL_STATE;
			default:
				break;
			}
		}
	}

	return CBaseState::Update(fDeltaTime);
}


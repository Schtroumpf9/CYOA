#include "std.h"
#include "OptionsState.h"


COptionsState::COptionsState()
{
	m_eType = OPTIONS_STATE;
}


COptionsState::~COptionsState()
{
}

void COptionsState::Initialize(CRenderManager* pRenderManager, CTextureManager* pTextureManager,
	CInputManager* pInputManager, CFontManager* pFontManager)
{
	CBaseState::Initialize(pRenderManager, pTextureManager, pInputManager, pFontManager);

	// Add Initial Images
	CQuad* pQuad;

	// Background
	CreateQuad(SDL_Color{ 0, 0, 0, 255 }, FloatRect{ 0.f, 0.f, 1.f, 1.f }, TOP_LEFT_POS, CUSTOM_QUAD, BACK_LAYER);

	// Buttons
	m_ucNumButtons = NUM_BTNS;
	m_ppButtons = new CQuad*[m_ucNumButtons];

	// Back Button
	pQuad = CreateQuad("BackButton.png", FloatRect{ 0.05f, 0.05f, .1f, .1f }, TOP_LEFT_POS, SQUAREH_QUAD);
	pQuad->SetColor(SDL_Color{ 127, 127, 127, 255 });
	m_ppButtons[BACK_BTN] = pQuad;

}

eSTATE_TYPE COptionsState::Update(float fDeltaTime)
{
	// Go back to main menu
	if (m_pInputManager->KeyEvent(SDLK_ESCAPE, KEY_UP))
		return MENU_STATE;

	ProcessButtons();

	if (m_cOverKey != INVALID_BUTTON)
	{
		if (m_pInputManager->SelectorUpEvent())
		{
			m_pInputManager->SetCursor(SDL_SYSTEM_CURSOR_ARROW);
			switch (m_cOverKey)
			{
			case BACK_BTN:
				return MENU_STATE;
			default:
				break;
			}
		}
	}

	return CBaseState::Update(fDeltaTime);
}

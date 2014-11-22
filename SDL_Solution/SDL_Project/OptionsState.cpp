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

	// Background
	CreateQuad(NULL, FloatRect{ 0.f, 0.f, 1.f, 1.f }, BACK_LAYER, CUSTOM_QUAD, SDL_Color{ 0, 0, 0, 255 });

	// Back Button
	m_Buttons[BACK_OPTIONS_BUTTON] = CreateQuad("BackButton.png", FloatRect{ .028125f, .05f, .05625f, .1f }, MID_LAYER, CUSTOM_QUAD, SDL_Color{ 127, 127, 127, 255 });
}

eSTATE_TYPE COptionsState::Update(float fDeltaTime)
{
	// Go back to main menu
	if (m_pInputManager->KeyEvent(SDLK_ESCAPE, KEY_UP))
		return MENU_STATE;

	ProcessButtons();

	if (m_sOverKey != INVALID_BUTTON)
	{
		if (m_pInputManager->SelectorUpEvent())
		{
			m_pInputManager->SetArrowCursor();
			switch (m_sOverKey)
			{
			case BACK_OPTIONS_BUTTON:
				return MENU_STATE;
			}
		}
	}

	return CBaseState::Update(fDeltaTime);
}

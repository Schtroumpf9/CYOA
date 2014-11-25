#include "std.h"
#include "IntroState.h"


CIntroState::CIntroState()
{
	m_eType = INTRO_STATE;
}


CIntroState::~CIntroState()
{
}

void CIntroState::Initialize(CRenderManager* pRenderManager, CTextureManager* pTextureManager,
	CInputManager* pInputManager, CFontManager* pFontManager)
{
	CBaseState::Initialize(pRenderManager, pTextureManager, pInputManager, pFontManager);

	// Add Initial Images
	CQuad* pText;
	SDL_Color tLightGray{ 0xd3, 0xd3, 0xd3, 0 };
	TextData tPosition{ 0.5f, 0.5f, 0.1f, MIDDLE_POS };

	// Background
	CreateQuad(SDL_Color{ 0, 0, 0, 255 }, FloatRect{ 0.f, 0.f, 1.f, 1.f }, TOP_LEFT_POS, CUSTOM_QUAD, BACK_LAYER);

	// Author
	pText = m_pFontManager->TTFCreateText("Alex Kahl", tLightGray, tPosition);
	m_pIntroText[0] = pText;

	// Filler
	pText = m_pFontManager->TTFCreateText("Presents", tLightGray, tPosition);
	m_pIntroText[1] = pText;

	// Title
	pText = m_pFontManager->TTFCreateText("CYOA", tLightGray, tPosition);
	m_pIntroText[2] = pText;

	m_fFadeTimer = 0.0f;
	m_ucCurText = 0;
	m_bFadeIn = true;
}

eSTATE_TYPE CIntroState::Update(float fDeltaTime)
{
	if (m_pInputManager->AnyEvent() && m_fInputDelayTimer <= 0.0f)
		return MENU_STATE;

	(m_bFadeIn) ? m_fFadeTimer += fDeltaTime : m_fFadeTimer -= fDeltaTime;
	if (m_bFadeIn && m_fFadeTimer > MAX_INTRO_FADE)
		m_fFadeTimer = MAX_INTRO_FADE;
	else if (!m_bFadeIn && m_fFadeTimer < 0.0f)
		m_fFadeTimer = 0.0f;

	SDL_Color tColor = m_pIntroText[m_ucCurText]->GetColor();
	tColor.a = static_cast<Uint8>((m_fFadeTimer / MAX_INTRO_FADE) * 255);
	m_pIntroText[m_ucCurText]->SetColor(tColor);

	if (tColor.a == 255 && m_bFadeIn)
	{
		m_bFadeIn = !m_bFadeIn;
	}
	else if (tColor.a == 0 && !m_bFadeIn)
	{
		m_bFadeIn = !m_bFadeIn;
		m_ucCurText++;
		if (m_ucCurText == 3)
			return MENU_STATE;
	}

	return CBaseState::Update(fDeltaTime);
}

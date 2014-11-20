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

	// BACK_LAYERground
	CreateQuad(NULL, FloatRect{ 0.f, 0.f, 1.f, 1.f }, BACK_LAYER, SDL_Color{ 0, 0, 0, 255 });

	// Options Text
	pText = m_pFontManager->TTFCreateText("Options", SDL_Color{ 0, 255, 0, 255 }, TextData{ .075f, .075f, .025f, TOP_LEFT_POS });

	// Options Button
	fWidth = pText->GetDstRect().w + 0.05f;
	pQuad = CreateQuad("ButtonStd.png", FloatRect{ .05f, .05f, fWidth, .075f }, MID_LAYER, SDL_Color{ 127, 127, 127, 255 });
	m_Buttons[OPTIONS_MENU_BUTTON] = pQuad;

	// Quit Text
	pText = m_pFontManager->TTFCreateText("Quit", SDL_Color{ 255, 0, 0, 255 }, TextData{ .95f, .05f, .025f, TOP_RIGHT_POS });

	// Quit Button
	//fWidth = pText->GetDstRect().w + 0.075f;
	//pQuad = CreateQuad(NULL, FloatRect{ 1.f - fWidth, 0.f, fWidth, .1f }, MID_LAYER, SDL_Color{ 95, 0, 0, 255 });

	// Menu Text
	pText = m_pFontManager->TTFCreateText("Play", SDL_Color{ 0, 127, 127, 255 }, TextData{ .5f, .5f, .1f, MIDDLE_POS });
}

eSTATE_TYPE CMenuState::Update(float fDeltaTime)
{
	SDL_Rect buttonRect;
	SDL_Point selectorPos = m_pInputManager->GetSelectorPos();
	std::map<Sint16, CQuad*>::iterator buttonIter = m_Buttons.begin();
	for (; buttonIter != m_Buttons.cend(); ++buttonIter)
	{
		buttonRect = buttonIter->second->GetPixelDstRect();

		if (PointInRect(&selectorPos, &buttonRect) == SDL_TRUE)
		{
			if (m_sOverKey != buttonIter->first)
			{
				if (m_sOverKey != INVALID_BUTTON)
					m_Buttons[m_sOverKey]->SetTexture(m_pTextureManager->GetTexture("ButtonStd.png"));
				buttonIter->second->SetTexture(m_pTextureManager->GetTexture("ButtonOver.png"));
				m_sOverKey = buttonIter->first;
				break;
			}
		}
	}

	if (m_sOverKey != INVALID_BUTTON)
	{
		if (buttonIter == m_Buttons.cend())
		{
			m_Buttons[m_sOverKey]->SetTexture(m_pTextureManager->GetTexture("ButtonStd.png"));
			m_sOverKey = INVALID_BUTTON;
		}
		else if (m_pInputManager->SelectorDownEvent())
		{
			m_Buttons[m_sOverKey]->SetTexture(m_pTextureManager->GetTexture("ButtonDown.png"));
		}
		else if (m_pInputManager->SelectorUpEvent())
		{
			return OPTIONS_STATE;
		}
	}

	return CBaseState::Update(fDeltaTime);
}


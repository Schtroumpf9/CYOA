#include "std.h"
#include "BaseState.h"


CBaseState::CBaseState(void) : m_pRenderManager(NULL), m_pTextureManager(NULL), m_pInputManager(NULL)
{
	m_eType = BASE_STATE;
}


CBaseState::~CBaseState(void)
{
}

void CBaseState::Initialize(CRenderManager* pRenderManager, CTextureManager* pTextureManager,
	CInputManager* pInputManager, CFontManager* pFontManager)
{
	m_pRenderManager = pRenderManager;
	m_pTextureManager = pTextureManager;
	m_pInputManager = pInputManager;
	m_pFontManager = pFontManager;

	m_cOverKey = INVALID_BUTTON;

	m_szPrefPath = SDL_GetPrefPath(COMP_NAME, APP_NAME);

	m_fInputDelayTimer = 0.25f;

	m_ucNumButtons = 0;
	m_ppButtons = NULL;

	// FPS Stuff
	m_unFrameCount = 0;
	m_fFPS = 0.0f;

	SDL_Color tColor = { 255, 0, 0, 255 };
	TextData tData = { 0.0f, 1.0f, 0.025f, BOTTOM_LEFT_POS };
	m_pFPSTextQuad = m_pFontManager->TTFCreateText("FPS: ", tColor, tData);

	tData.x += m_pFPSTextQuad->GetDstRect().w;
	m_pFPSQuad = m_pFontManager->TTFCreateText("0.0f", tColor, tData);

	// Last Thing!
	m_unStartTime = SDL_GetTicks();
}

eSTATE_TYPE CBaseState::Update(float fDeltaTime)
{
	// Calculate FPS
	Uint32 unTime = SDL_GetTicks();
	m_fFPS = m_unFrameCount / ((unTime - m_unStartTime) / 1000.0f);

	// Show FPS
	m_OSS.str("");
	m_OSS << m_fFPS;
	m_pFontManager->TTFChangeText(m_pFPSQuad, m_OSS.str().c_str(), m_pFPSQuad->GetColor());

	// Update Timer
	if (m_fInputDelayTimer > 0.0f)
		m_fInputDelayTimer -= fDeltaTime;

	m_unFrameCount++;

	return m_eType;
}

void CBaseState::Shutdown(void)
{
	m_pRenderManager->DeleteAllQuads();
	delete[]m_ppButtons;
	m_ppButtons = NULL;
	m_ucNumButtons = 0;
}

// Helpers
CQuad* CBaseState::CreateQuad(const char* szTextureName, const FloatRect& tDstRect, const eQUAD_POS_TYPE ePosType, const eQUAD_TYPE eType, const eLAYER eLayer)
{
	SDL_Texture* pTexture = m_pTextureManager->GetTexture(szTextureName);
	CQuad* pQuad = new CQuad(pTexture, tDstRect, ePosType, eType, eLayer);
	m_pRenderManager->AddQuad(pQuad);
	return pQuad;
}

CQuad* CBaseState::CreateQuad(const SDL_Color tColor, const FloatRect& tDstRect, const eQUAD_POS_TYPE ePosType, const eQUAD_TYPE eType, const eLAYER eLayer)
{
	CQuad* pQuad = new CQuad(tColor, tDstRect, ePosType, eType, eLayer);
	m_pRenderManager->AddQuad(pQuad);
	return pQuad;
}

void CBaseState::ProcessButtons(void)
{
	if (m_fInputDelayTimer > 0.0f)
		return;

	SDL_Rect buttonRect;
	SDL_Point selectorPos = m_pInputManager->GetSelectorPos();
	Uint8 btnIter = 0;
	for (; btnIter < m_ucNumButtons; ++btnIter)
	{
		buttonRect = m_ppButtons[btnIter]->GetPixelDstRect();

		if (PointInRect(&selectorPos, &buttonRect) == SDL_TRUE)
		{
			if (m_cOverKey != btnIter)
			{
				m_pInputManager->SetCursor(SDL_SYSTEM_CURSOR_HAND);
				m_cOverKey = btnIter;
			}
			break;
		}
	}

	if (m_cOverKey != INVALID_BUTTON)
	{
		if (btnIter == m_ucNumButtons)
		{
			m_pInputManager->SetCursor(SDL_SYSTEM_CURSOR_ARROW);
			m_cOverKey = INVALID_BUTTON;
		}
	}
}

// Static Helpers
char* CBaseState::ReadString(SDL_RWops* pFile)
{
	Uint8 ucLength;
	SDL_RWread(pFile, &ucLength, sizeof(ucLength), 1);
	char* szData = new char[ucLength + 1];
	SDL_RWread(pFile, szData, sizeof(char) * (ucLength), 1);
	szData[ucLength] = '\0';
	return szData;
}

SDL_Color CBaseState::InvertColor(const SDL_Color& tColor)
{
	SDL_Color tInvertedColor;
	tInvertedColor.r = 255 - tColor.r;
	tInvertedColor.g = 255 - tColor.g;
	tInvertedColor.b = 255 - tColor.b;
	tInvertedColor.a = tColor.a;
	return tInvertedColor;
}

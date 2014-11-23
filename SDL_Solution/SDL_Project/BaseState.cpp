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

	// FPS Stuff
	m_unFrameCount = 0;
	m_fFPS = 0.0f;

	SDL_Color tColor = { 255, 0, 0, 255 };
	TextData tData = { 0.0f, 1.0f, 0.025f, BOTTOM_LEFT_POS };
	m_pFPSTextQuad = m_pFontManager->TTFCreateText("FPS: ", tColor, tData);

	tData.x += m_pFPSTextQuad->GetDstRect().w;
	m_pFPSQuad = m_pFontManager->TTFCreateText("0.0f", tColor, tData);

	m_sOverKey = INVALID_BUTTON;

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

	m_unFrameCount++;

	return m_eType;
}

void CBaseState::Shutdown(void)
{
	m_pRenderManager->DeleteAllQuads();
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
				m_pInputManager->SetHandCursor();
				m_sOverKey = buttonIter->first;
			}
			break;
		}
	}

	if (m_sOverKey != INVALID_BUTTON)
	{
		if (buttonIter == m_Buttons.cend())
		{
			m_pInputManager->SetArrowCursor();
			m_sOverKey = INVALID_BUTTON;
		}
	}
}

char* CBaseState::ReadString(SDL_RWops* pFile)
{
	Uint8 ucLength;
	SDL_RWread(pFile, &ucLength, sizeof(ucLength), 1);
	char* szData = new char[ucLength + 1];
	SDL_RWread(pFile, szData, sizeof(char) * (ucLength), 1);
	szData[ucLength] = '\0';
	return szData;
}




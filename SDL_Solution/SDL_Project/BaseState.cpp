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
	TextData tData = { 0.0f, 1.0f, 0.025f, BOTTOM_LEFT };
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

	m_unFrameCount++;

	return m_eType;
}

void CBaseState::Shutdown(void)
{
	m_pRenderManager->DeleteAllQuads();
}

CQuad* CBaseState::CreateQuad(const char* szTextureName, const FloatRect& tDstRect, const eLAYER& ucLayer, const SDL_Color& tColor)
{
	CQuad* pQuad;
	if(szTextureName == NULL)
	{
		pQuad = new CQuad(NULL, ucLayer, tColor, tDstRect);
	}
	else
	{
		SDL_Texture* pTexture = m_pTextureManager->GetTexture(szTextureName);
		pQuad = new CQuad(pTexture, ucLayer, tColor, tDstRect);
	}

	m_pRenderManager->AddQuad(pQuad);
	return pQuad;
}


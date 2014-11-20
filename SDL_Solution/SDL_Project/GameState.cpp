#include "std.h"
#include "GameState.h"


CGameState::CGameState(void)
{
	m_eType = GAME_STATE;
}


CGameState::~CGameState(void)
{
}

void CGameState::Initialize(CRenderManager* pRenderManager, CTextureManager* pTextureManager,
	CInputManager* pInputManager, CFontManager* pFontManager)
{
	CBaseState::Initialize(pRenderManager, pTextureManager, pInputManager, pFontManager);

}

eSTATE_TYPE CGameState::Update(float fDeltaTime)
{
	return CBaseState::Update(fDeltaTime);
}

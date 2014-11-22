#include "std.h"
#include "ToolState.h"


CToolState::CToolState()
{
}


CToolState::~CToolState()
{
}

void CToolState::Initialize(CRenderManager* pRenderManager, CTextureManager* pTextureManager,
	CInputManager* pInputManager, CFontManager* pFontManager)
{
	CBaseState::Initialize(pRenderManager, pTextureManager, pInputManager, pFontManager);

}

eSTATE_TYPE CToolState::Update(float fDeltaTime)
{
	// Go back to main menu
	if (m_pInputManager->KeyEvent(SDLK_ESCAPE, KEY_UP))
		return MENU_STATE;

	return CBaseState::Update(fDeltaTime);
}

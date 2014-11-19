#ifndef GAME_STATE_H
#define GAME_STATE_H

#include "BaseState.h"

class CGameState : public CBaseState
{
public:
	CGameState(void);
	~CGameState(void);

	void Initialize(CRenderManager* pRenderManager, CTextureManager* pTextureManager,
		CInputManager* pInputManager, CFontManager* pFontManager);
	eSTATE_TYPE Update(float fDeltaTime);
};
#endif

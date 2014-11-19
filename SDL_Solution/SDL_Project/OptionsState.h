#ifndef OPTIONS_STATE_H
#define OPTIONS_STATE_H

#include "BaseState.h"

class COptionsState : public CBaseState
{
public:
	COptionsState();
	~COptionsState();

	void Initialize(CRenderManager* pRenderManager, CTextureManager* pTextureManager,
		CInputManager* pInputManager, CFontManager* pFontManager);
	eSTATE_TYPE Update(float fDeltaTime);
};
#endif



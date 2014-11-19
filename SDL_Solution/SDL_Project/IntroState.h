#ifndef INTRO_STATE_H
#define INTRO_STATE_H

#include "BaseState.h"

class CIntroState : public CBaseState
{
public:
	CIntroState();
	~CIntroState();

	void Initialize(CRenderManager* pRenderManager, CTextureManager* pTextureManager,
		CInputManager* pInputManager, CFontManager* pFontManager);
	eSTATE_TYPE Update(float fDeltaTime);

private:
	float m_fFadeTimer;
	CQuad* m_pIntroText[3];
	Uint8 m_ucCurText;
	bool m_bFadeIn;
};
#endif



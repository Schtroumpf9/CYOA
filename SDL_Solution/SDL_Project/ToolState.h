#ifndef TOOL_STATE_H
#define TOOL_STATE_H

#include "BaseState.h"

class CToolState : public CBaseState
{
public:
	CToolState();
	~CToolState();

	void Initialize(CRenderManager* pRenderManager, CTextureManager* pTextureManager,
		CInputManager* pInputManager, CFontManager* pFontManager);
	eSTATE_TYPE Update(float fDeltaTime);

private:
	// Button Type Enum
	enum TOOL_BTN_ID { INVALID_BUTTON = -1, BACK_BTN, NUM_BTNS };
};
#endif



#ifndef MENU_STATE_H
#define MENU_STATE_H

#include "BaseState.h"

class CMenuState : public CBaseState
{
public:
	CMenuState(void);
	~CMenuState(void);

	void Initialize(CRenderManager* pRenderManager, CTextureManager* pTextureManager,
		CInputManager* pInputManager, CFontManager* pFontManager);
	eSTATE_TYPE Update(float fDeltaTime);

private:
	// Button Type Enum
	enum MENU_BTN_ID { INVALID_BUTTON = -1, QUIT_BTN, OPTIONS_BTN, CHOOSE_BTN, CREATE_BTN, NUM_BTNS};
};
#endif

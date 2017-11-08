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
	void Shutdown(void);

private:
	typedef eSTATE_TYPE(CToolState::*UpdateFunction) (float);
	UpdateFunction UpdatePtr;
	typedef void(CToolState::*ShutdownFunction)(void);
	ShutdownFunction ShutdownPtr;
	void ChangeToSelect(void);
	void ChangeToTool(void);

	// Select Screen Related Methods and Members
	void SelectInit(void);
	eSTATE_TYPE SelectUpdate(float fDeltaTime);
	void SelectShutdown(void);

	char** m_szAdventures;
	Uint8 m_ucNumAdventures;

	CQuad* m_pSelected;
	CQuad* m_pHighlight;
	bool m_bSelected;

	bool m_bScrollable;
	CQuad* m_pScrollBar;

	// Button Type Enum
	enum SELECT_BTN_ID { INVALID_BUTTON = -1, BACK_BTN, NEW_BTN, EDIT_BTN, DELETE_BTN, LIST_START_BTN };

	// Shared Data
	const char* m_szCurAdventure;

	// Tool Related Methods and Members
	void ToolInit(void);
	eSTATE_TYPE ToolUpdate(float fDeltaTime);
	void ToolShutdown(void);
};
#endif



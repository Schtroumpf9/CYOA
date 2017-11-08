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
	void Shutdown(void);

private:
	typedef eSTATE_TYPE(CGameState::*UpdateFunction) (float);
	UpdateFunction UpdatePtr;
	typedef void(CGameState::*ShutdownFunction)(void);
	ShutdownFunction ShutdownPtr;
	void ChangeToSelect(void);
	void ChangeToGame(void);

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
	enum SELECT_BTN_ID { INVALID_BUTTON = -1, BACK_BTN, PLAY_BTN, LIST_START_BTN };

	// Shared Data
	const char* m_szCurAdventure;

	// Game Related Methods and Members
	void GameInit(void);
	eSTATE_TYPE GameUpdate(float fDeltaTime);
	void GameShutdown(void);


};
#endif

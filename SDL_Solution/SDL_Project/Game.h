#ifndef GAME_H
#define GAME_H

// CONST CORRECTNESS THROUGHOUT

// Move FPS timer to BaseState?

#include "structs.h"

class CRenderManager;
class CTextureManager;
class CInputManager;
class CFontManager;
class CBaseState;
class CQuad;

class CGame
{
public:
	CGame(void);
	~CGame(void);

	void Initialize(void);
	bool Run(void);
	void Shutdown();

private:
	// Managers
	CRenderManager* m_pRenderManager;
	CTextureManager* m_pTextureManager;
	CInputManager* m_pInputManager;
	CFontManager* m_pFontManager;

	CBaseState* m_pCurrentState;

	// Used for DeltaTime
	Uint32 m_unTime;

	// Helpers
	void ChangeStates(const eSTATE_TYPE& eState);
};
#endif

#ifndef GAME_H
#define GAME_H

// TODO: Use SDL_GetPlatform for platform specific tasks
// TODO: Add way to keep images from being scaled incorrectly (i.e. the options button is square and should stay square)
//			Determine which ratio the screen res is closest to, determine the resolution that fits inside the screen with that ratio
//			Adjust elements to that ratio and screen res
//			Textures only need to change between 4:3 and 16:9
// TODO: Make easier way to make square or scaled images.
//			(i.e. Create Quad by passing a single size value, and then either scales the other size to be the screen ratio, or makes them equal

// TODO: File I/O Manager
//			Reading strings sucks

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

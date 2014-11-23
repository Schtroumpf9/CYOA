#ifndef GAME_H
#define GAME_H

// TODO: Use SDL_GetPlatform for platform specific tasks
// TODO: Option to change/lock Aspect Ratio and set Screen Res
// TODO: Make easier way to make square or scaled images.
//			(i.e. Create Quad by passing a single size value, and then either scales the other size to be the screen ratio, or makes them equal
//			Might need to redo how a Quad's position and size are set

// 16:10
// 16:9
// 5:3
// 4:3
// 3:2

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

#include "std.h"
#include "Game.h"
#include "RenderManager.h"
#include "TextureManager.h"
#include "InputManager.h"
#include "FontManager.h"
#include "Quad.h"
#include "MenuState.h"
#include "GameState.h"

CGame::CGame(void) : m_pRenderManager(NULL), m_pTextureManager(NULL), m_pInputManager(NULL), m_pFontManager(NULL), m_pCurrentState(NULL)
{
}

CGame::~CGame(void)
{
}

void CGame::Initialize(void)
{
	SDL_ERROR_CHECK(SDL_Init(SDL_INIT_VIDEO) < 0, "SDL failed to initialize.");

	m_pRenderManager = new CRenderManager;
	m_pRenderManager->Initialize();

	m_pTextureManager = new CTextureManager;
	m_pTextureManager->Initialize(m_pRenderManager->GetRenderer());

	m_pInputManager = new CInputManager;
	m_pInputManager->Initialize();

	m_pFontManager = new CFontManager;
	m_pFontManager->Initialize(m_pRenderManager);

	m_pCurrentState = new CMenuState;
	m_pCurrentState->Initialize(m_pRenderManager, m_pTextureManager, m_pInputManager, m_pFontManager);

	m_unTime = SDL_GetTicks();
}

bool CGame::Run(void)
{
	m_pInputManager->Input();

	// Standard Game Input
	if(m_pInputManager->QuitEvent())
		return false;
	if(m_pInputManager->WindowResizeEvent())
		m_pRenderManager->Resize(m_pInputManager->GetWindowSize());

	// Find DeltaTime before updating
	Uint32 unCurTime = SDL_GetTicks();
	float fDeltaTime = (unCurTime - m_unTime) / 1000.0f;
	m_unTime = unCurTime;

	eSTATE_TYPE eResult = m_pCurrentState->Update(fDeltaTime);
	if(eResult != m_pCurrentState->GetType())
		ChangeStates(eResult);

	m_pRenderManager->Render();

	return true;
}

void CGame::Shutdown(void)
{
	SAFE_SHUTDOWN(m_pCurrentState);
	SAFE_SHUTDOWN(m_pFontManager);
	SAFE_SHUTDOWN(m_pInputManager);
	SAFE_SHUTDOWN(m_pTextureManager);
	SAFE_SHUTDOWN(m_pRenderManager);

	SDL_Quit();
}

void CGame::ChangeStates(const eSTATE_TYPE& eState)
{
	SAFE_SHUTDOWN(m_pCurrentState);

	switch (eState)
	{
	case MENU_STATE:
		m_pCurrentState = new CMenuState;
		m_pCurrentState->Initialize(m_pRenderManager, m_pTextureManager, m_pInputManager, m_pFontManager);
		break;
	case GAME_STATE:
		m_pCurrentState = new CGameState;
		m_pCurrentState->Initialize(m_pRenderManager, m_pTextureManager, m_pInputManager, m_pFontManager);
		break;
	}
}

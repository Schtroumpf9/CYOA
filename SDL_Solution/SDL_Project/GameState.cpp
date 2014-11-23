#include "std.h"
#include "GameState.h"


CGameState::CGameState(void)
{
	m_eType = GAME_STATE;
}


CGameState::~CGameState(void)
{
}

void CGameState::Initialize(CRenderManager* pRenderManager, CTextureManager* pTextureManager,
	CInputManager* pInputManager, CFontManager* pFontManager)
{
	CBaseState::Initialize(pRenderManager, pTextureManager, pInputManager, pFontManager);

	// Add Initial Images
	CQuad* pQuad;

	// Background
	CreateQuad(SDL_Color{ 0, 0, 0, 255 }, FloatRect{ 0.f, 0.f, 1.f, 1.f }, TOP_LEFT_POS, CUSTOM_QUAD, BACK_LAYER);

	// Back Button
	pQuad = CreateQuad("BackButton.png", FloatRect{ 0.05f, 0.05f, .1f, .1f }, TOP_LEFT_POS, SQUAREH_QUAD);
	pQuad->SetColor(SDL_Color{ 127, 127, 127, 255 });
	m_Buttons[BACK_OPTIONS_BUTTON] = pQuad;

	// Read Available Adventures
	//SDL_GetPrefPath for user files
	// Create It!
	/*SDL_RWops* file = SDL_RWFromFile("../Adventures/Available.bin", "wb");
	SDL_ERROR_CHECK(file == NULL, "SDL could not create file!");
	Uint8 data = 5;
	SDL_RWwrite(file, &data, sizeof(data), 1);

	const char* szAdventures[] = { "Red vs. Blue: Church", "Red vs. Blue: Grif", "Red vs. Blue: Tex", "Mass Effect", "Fallout 3" };
	for (int i = 0; i < 5; ++i)
	{
		data = strnlen_s(szAdventures[i], 256);
		SDL_RWwrite(file, &data, sizeof(data), 1);
		SDL_RWwrite(file, szAdventures[i], sizeof(char), data);
	}
	SDL_RWclose(file);*/

	SDL_RWops* file = SDL_RWFromFile("../Adventures/Available.bin", "rb");
	SDL_ERROR_CHECK(file == NULL, "SDL could not open file!");
	Uint8 ucCount;
	SDL_RWread(file, &ucCount, sizeof(ucCount), 1);
	char** szAdventures = new char*[ucCount];
	Uint8 i;
	for (i = 0; i < ucCount; ++i)
	{
		szAdventures[i] = ReadString(file);
	}
	SDL_RWclose(file);

	SDL_Color tColor = { 0, 255, 0, 255 };
	TextData tData = { .2f, .2f, .05f, TOP_LEFT_POS };
	for (i = 0; i < ucCount; ++i)
	{
		m_pFontManager->TTFCreateText(szAdventures[i], tColor, tData);
		tData.y += 0.075f;
		delete[]szAdventures[i];
	}
	delete[]szAdventures;
}

eSTATE_TYPE CGameState::Update(float fDeltaTime)
{
	// Go back to main menu
	if (m_pInputManager->KeyEvent(SDLK_ESCAPE, KEY_UP))
		return MENU_STATE;

	ProcessButtons();

	if (m_sOverKey != INVALID_BUTTON)
	{
		if (m_pInputManager->SelectorUpEvent())
		{
			m_pInputManager->SetArrowCursor();
			switch (m_sOverKey)
			{
			case BACK_OPTIONS_BUTTON:
				return MENU_STATE;
			}
		}
	}

	return CBaseState::Update(fDeltaTime);
}

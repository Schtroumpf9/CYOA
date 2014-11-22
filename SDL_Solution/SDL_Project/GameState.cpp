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

	// Background
	CreateQuad(NULL, FloatRect{ 0.f, 0.f, 1.f, 1.f }, BACK_LAYER, CUSTOM_QUAD, SDL_Color{ 0, 0, 0, 255 });

	// Back Button
	m_Buttons[BACK_OPTIONS_BUTTON] = CreateQuad("BackButton.png", FloatRect{ .028125f, .05f, .05625f, .1f }, MID_LAYER, CUSTOM_QUAD, SDL_Color{ 127, 127, 127, 255 });

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
	Uint8 ucCount, ucLength;
	SDL_RWread(file, &ucCount, sizeof(ucCount), 1);
	char** szAdventures = new char*[ucCount];
	Uint8 i;
	for (i = 0; i < ucCount; ++i)
	{
		SDL_RWread(file, &ucLength, sizeof(ucLength), 1);
		szAdventures[i] = new char[ucLength+1];
		SDL_RWread(file, szAdventures[i], sizeof(char) * (ucLength), 1);
		szAdventures[i][ucLength] = '\0';
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

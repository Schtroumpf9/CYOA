#include "std.h"
#include "ToolState.h"


CToolState::CToolState()
{
}


CToolState::~CToolState()
{
}

void CToolState::Initialize(CRenderManager* pRenderManager, CTextureManager* pTextureManager,
	CInputManager* pInputManager, CFontManager* pFontManager)
{
	CBaseState::Initialize(pRenderManager, pTextureManager, pInputManager, pFontManager);

	// Add Initial Images
	CQuad* pQuad;

	// Background
	CreateQuad(SDL_Color{ 0, 0, 0, 255 }, FloatRect{ 0.f, 0.f, 1.f, 1.f }, TOP_LEFT_POS, CUSTOM_QUAD, BACK_LAYER);

	// Buttons
	m_ucNumButtons = NUM_BTNS;
	m_ppButtons = new CQuad*[m_ucNumButtons];

	// Back Button
	pQuad = CreateQuad("BackButton.png", FloatRect{ 0.05f, 0.05f, .1f, .1f }, TOP_LEFT_POS, SQUAREH_QUAD);
	pQuad->SetColor(SDL_Color{ 127, 127, 127, 255 });
	m_ppButtons[BACK_BTN] = pQuad;

	// Create It!
	SDL_RWops* file = SDL_RWFromFile("../Adventures/AvailableLarge.bin", "wb");
	SDL_ERROR_CHECK(file == NULL, "SDL could not create file!");
	Uint8 data = 20;
	SDL_RWwrite(file, &data, sizeof(data), 1);

	const char* szAdventures[] = {
		"Red vs. Blue: Church", "Red vs. Blue: Grif", "Red vs. Blue: Tex", "Mass Effect", "Fallout 3",
		"Skyrim", "Oblivion", "Mass Effect 2", "Mass Effect 3", "Borderlands",
		"Game Of Thrones", "The Walking Dead", "Battlefield 4", "Saints Row 2", "Saints Row IV",
		"Splinter Cell", "Halo 3", "Custom", "New", "Blank"
	};

	size_t size = 0;
	for (int i = 0; i < data; ++i)
	{
		size = SDL_strlen(szAdventures[i]);
		SDL_RWwrite(file, &size, sizeof(size), 1);
		SDL_RWwrite(file, szAdventures[i], sizeof(char), size);
	}
	SDL_RWclose(file);
}

eSTATE_TYPE CToolState::Update(float fDeltaTime)
{
	// Go back to main menu
	if (m_pInputManager->KeyEvent(SDLK_ESCAPE, KEY_UP))
		return MENU_STATE;

	ProcessButtons();

	if (m_cOverKey != INVALID_BUTTON)
	{
		if (m_pInputManager->SelectorUpEvent())
		{
			m_pInputManager->SetCursor(SDL_SYSTEM_CURSOR_ARROW);
			switch (m_cOverKey)
			{
			case BACK_BTN:
				return MENU_STATE;
			default:
				break;
			}
		}
	}

	return CBaseState::Update(fDeltaTime);
}

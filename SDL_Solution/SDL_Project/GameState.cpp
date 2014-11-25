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

	// Init on Select Screen
	SelectInit();
	UpdatePtr = &CGameState::SelectUpdate;
	ShutdownPtr = &CGameState::SelectShutdown;
}

eSTATE_TYPE CGameState::Update(float fDeltaTime)
{
	ProcessButtons();

	return (this->*UpdatePtr)(fDeltaTime);
}

void CGameState::Shutdown(void)
{
	(this->*ShutdownPtr)();
}

void CGameState::ChangeToSelect(void)
{
	GameShutdown();
	CBaseState::Initialize(m_pRenderManager, m_pTextureManager, m_pInputManager, m_pFontManager);
	SelectInit();
	UpdatePtr = &CGameState::SelectUpdate;
	ShutdownPtr = &CGameState::SelectShutdown;
}

void CGameState::ChangeToGame(void)
{
	SelectShutdown();
	CBaseState::Initialize(m_pRenderManager, m_pTextureManager, m_pInputManager, m_pFontManager);
	GameInit();
	UpdatePtr = &CGameState::GameUpdate;
	ShutdownPtr = &CGameState::GameShutdown;
}

// Select Screen Related Methods
void CGameState::SelectInit(void)
{
	// Background
	CreateQuad(SDL_Color{ 0, 0, 0, 255 }, FloatRect{ 0.f, 0.f, 1.f, 1.f }, TOP_LEFT_POS, CUSTOM_QUAD, BACK_LAYER);

	// Reset Adventure
	m_szCurAdventure = "";

	// Read Available Adventures
	SDL_RWops* file = SDL_RWFromFile(m_szPrefPath, "rb");
	if (file == NULL)
		file = SDL_RWFromFile("../Adventures/Available.bin", "rb");
	SDL_RWread(file, &m_ucNumAdventures, sizeof(m_ucNumAdventures), 1);

	if (m_ucNumAdventures > 0)
		m_szAdventures = new char*[m_ucNumAdventures];

	Uint8 i;
	for (i = 0; i < m_ucNumAdventures; ++i)
	{
		m_szAdventures[i] = ReadString(file);
	}
	SDL_RWclose(file);


	// Buttons
	m_ucNumButtons = LIST_START_BTN + m_ucNumAdventures;
	m_ppButtons = new CQuad*[m_ucNumButtons];

	SDL_Color tColor = { 0, 255, 0, 255 };
	TextData tData = { LIST_LEFT, LIST_TOP, LIST_TEXT_HEIGHT, TOP_LEFT_POS };
	for (i = LIST_START_BTN; i < LIST_START_BTN + m_ucNumAdventures; ++i)
	{
		m_ppButtons[i] = m_pFontManager->TTFCreateText(m_szAdventures[i - LIST_START_BTN], tColor, tData, MID_LAYER);
		tData.y += LIST_TEXT_HEIGHT + LIST_DEAD_HEIGHT;
	}

	// Highlighting
	float fTop = LIST_TOP - (LIST_DEAD_HEIGHT / 2);
	float fLeft = LIST_LEFT - (LIST_DEAD_HEIGHT / 2);
	m_pHighlight = CreateQuad(SDL_Color{ 100, 100, 100, 0 }, FloatRect{ fLeft, fTop, 1.f - fLeft, LIST_TEXT_HEIGHT + LIST_DEAD_HEIGHT }, TOP_LEFT_POS, CUSTOM_QUAD, BACK_LAYER);
	m_pSelected = CreateQuad(SDL_Color{ 100, 100, 100, 0 }, FloatRect{ fLeft, fTop, 1.f - fLeft, LIST_TEXT_HEIGHT + LIST_DEAD_HEIGHT }, TOP_LEFT_POS, CUSTOM_QUAD, BACK_LAYER);

	// Num of Adventures Stuff
	if (m_ucNumAdventures > LIST_MAX)
	{
		m_bScrollable = true;
		Uint16 usNumPages = m_ucNumAdventures / LIST_MAX;
		if (m_ucNumAdventures % LIST_MAX != 0)
			usNumPages += 1;
		float fHeight = (1.0f - LIST_TOP * 2) / usNumPages;
		float fRight = 1.0f - LIST_LEFT + (LIST_DEAD_HEIGHT / 2);
		m_pScrollBar = CreateQuad(SDL_Color{ 200, 200, 200, 127 }, FloatRect{ fRight, fTop, LIST_DEAD_HEIGHT / 4, fHeight }, TOP_LEFT_POS, CUSTOM_QUAD, FRONT_LAYER);

		tColor = SDL_Color{ 0, 0, 0, 255 };
		CreateQuad(tColor, FloatRect{ 0.f, 0.f, 1.f, fTop });
		CreateQuad(tColor, FloatRect{ 0.f, 0.f, fLeft, 1.f });
		CreateQuad(tColor, FloatRect{ 0.f, 1.f, 1.f, fTop }, BOTTOM_LEFT_POS);
		CreateQuad(tColor, FloatRect{ 1.f, 0.f, fLeft, 1.f }, TOP_RIGHT_POS);
	}

	// Play Button
	m_ppButtons[PLAY_BTN] = m_pFontManager->TTFCreateText("Play!", SDL_Color{ 0, 255, 255, 127 }, TextData{ .95f, .05f, .05f, TOP_RIGHT_POS });
	m_bSelected = false;

	// Back Button
	m_ppButtons[BACK_BTN] = CreateQuad("BackButton.png", FloatRect{ 0.05f, 0.05f, .1f, .1f }, TOP_LEFT_POS, SQUAREH_QUAD, FRONT_LAYER);
	m_ppButtons[BACK_BTN]->SetColor(SDL_Color{ 127, 127, 127, 255 });
}

eSTATE_TYPE CGameState::SelectUpdate(float fDeltaTime)
{
	// Go back to main menu
	if (m_pInputManager->KeyEvent(SDLK_ESCAPE, KEY_UP))
		return MENU_STATE;

	if (m_cOverKey != INVALID_BUTTON)
	{
		if (m_pInputManager->SelectorUpEvent())
		{
			m_pInputManager->SetCursor(SDL_SYSTEM_CURSOR_ARROW);
			switch (m_cOverKey)
			{
			case BACK_BTN:
				return MENU_STATE;
			case PLAY_BTN:
			{
				if (m_bSelected)
				{
					ChangeToGame();
					return CBaseState::Update(fDeltaTime);
				}
			}
			default:
				break;
			}
		}

		// Go through list
		// Adventure Selection
		SDL_Color tColor{ 100, 100, 100, 0 };
		m_pHighlight->SetColor(tColor);

		float fTop = LIST_TOP - (LIST_DEAD_HEIGHT / 2);
		float fLeft = LIST_LEFT - (LIST_DEAD_HEIGHT / 2);
		FloatRect curItemDstRect{ fLeft, fTop, 1.f - fLeft, LIST_TEXT_HEIGHT + LIST_DEAD_HEIGHT };
		SDL_Rect curItemRect = m_pSelected->GetPixelDstRect();
		SDL_Point selectorPos = m_pInputManager->GetSelectorPos();
		for (Uint8 i = LIST_START_BTN; i < LIST_START_BTN + m_ucNumAdventures; ++i)
		{
			curItemRect.y = m_ppButtons[i]->GetPixelDstRect().y;
			curItemRect.y -= (curItemRect.h / 2);

			curItemDstRect.y = m_ppButtons[i]->GetDstRect().y;
			curItemDstRect.y -= (LIST_DEAD_HEIGHT / 2);

			if (m_cOverKey == i)
			{
				// Highlight
				tColor.a = 127;
				m_pHighlight->SetColor(tColor);
				m_pHighlight->MoveDstQuad(curItemDstRect);
				m_pRenderManager->UpdateQuad(m_pHighlight);
				if (m_pInputManager->SelectorUpEvent())
				{
					tColor.a = 255;
					m_pSelected->SetColor(tColor);
					m_pSelected->MoveDstQuad(curItemDstRect);
					m_pRenderManager->UpdateQuad(m_pSelected);
					m_szCurAdventure = SDL_strdup(m_szAdventures[i - LIST_START_BTN]);

					m_bSelected = true;
					m_ppButtons[PLAY_BTN]->SetColor(SDL_Color{ 0, 255, 255, 255 });
				}
				break;
			}
		}
	}

	// Scrolling
	if (m_pInputManager->ScrollEvent() && m_bScrollable)
	{
		Sint32 nAmount = m_pInputManager->GetScrollAmount();
		float fLimit = LIST_TOP - (LIST_DEAD_HEIGHT / 2);
		FloatRect tCurRect = m_pScrollBar->GetDstRect();
		float fBot = tCurRect.y + tCurRect.h;
		if ((nAmount > 0 && tCurRect.y > fLimit) || (nAmount < 0 && fBot < 1.0f - fLimit))
		{
			float fAmount = nAmount * 0.05f;
			Uint16 usNumPages = m_ucNumAdventures / LIST_MAX;
			if (m_ucNumAdventures % LIST_MAX != 0)
				usNumPages += 1;
			tCurRect.y -= fAmount / usNumPages;
			m_pScrollBar->MoveDstQuad(tCurRect);
			m_pRenderManager->UpdateQuad(m_pScrollBar);

			tCurRect = m_pHighlight->GetDstRect();
			tCurRect.y += fAmount;
			m_pHighlight->MoveDstQuad(tCurRect);
			m_pRenderManager->UpdateQuad(m_pHighlight);

			for (Uint8 i = LIST_START_BTN; i < LIST_START_BTN + m_ucNumAdventures; ++i)
			{
				tCurRect = m_ppButtons[i]->GetDstRect();
				tCurRect.y += fAmount;
				m_ppButtons[i]->MoveDstQuad(tCurRect);
				m_pRenderManager->UpdateQuad(m_ppButtons[i]);

				if (SDL_strcmp(m_szAdventures[i - LIST_START_BTN], m_szCurAdventure) == 0)
				{
					tCurRect = m_pSelected->GetDstRect();
					tCurRect.y += fAmount;
					m_pSelected->MoveDstQuad(tCurRect);
					m_pRenderManager->UpdateQuad(m_pSelected);
				}
			}
		}
	}

	return CBaseState::Update(fDeltaTime);
}

void CGameState::SelectShutdown(void)
{
	for (Uint8 i = 0; i < m_ucNumAdventures; ++i)
		delete[]m_szAdventures[i];
	delete[]m_szAdventures;
	m_szAdventures = NULL;

	m_ucNumAdventures = 0;
	m_pHighlight = NULL;
	m_pSelected = NULL;
	m_bScrollable = false;
	m_bSelected = false;

	CBaseState::Shutdown();
}

// Game Related Methods
void CGameState::GameInit(void)
{

}

eSTATE_TYPE CGameState::GameUpdate(float fDeltaTime)
{
	// Go back to select screen
	if (m_pInputManager->KeyEvent(SDLK_ESCAPE, KEY_UP))
	{
		ChangeToSelect();
		return CBaseState::Update(fDeltaTime);
	}

	return CBaseState::Update(fDeltaTime);
}

void CGameState::GameShutdown(void)
{
	CBaseState::Shutdown();
}


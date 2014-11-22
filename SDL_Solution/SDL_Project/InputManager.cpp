#include "std.h"
#include "InputManager.h"


CInputManager::CInputManager(void)
{
}

CInputManager::~CInputManager(void)
{
}

void CInputManager::Initialize(void)
{
	m_bQuit = false;
	m_bWindowResize = false;
	m_bSelectorUp = false;
	m_bSelectorDown = false;
	m_bAny = false;

	m_tWindowSize.x = m_tWindowSize.y = 0;
	m_tSelectorPos.x = m_tSelectorPos.y = 0;
}

void CInputManager::Input(void)
{
	m_bSelectorUp = false;
	m_bQuit = false;
	m_bWindowResize = false;
	m_bAny = false;

	std::map<SDL_Keycode, eKEY_STATE>::iterator keyIter;
	for (keyIter = m_KeyStates.begin(); keyIter != m_KeyStates.cend(); ++keyIter)
	{
		if (keyIter->second == KEY_UP)
			keyIter->second = KEY_STD;
	}

	SDL_Event e;
	while (SDL_PollEvent(&e) != 0)
	{
		//User requests quit
		switch (e.type)
		{
		case SDL_QUIT:
			m_bQuit = true;
			break;
		case SDL_WINDOWEVENT:
		{
			if (e.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
			{
				m_bWindowResize = true;
				m_tWindowSize.x = e.window.data1;
				m_tWindowSize.y = e.window.data2;
			}
			break;
		}
		case SDL_KEYDOWN:
			m_KeyStates[e.key.keysym.sym] = KEY_DOWN;
			m_bAny = true;
			break;
		case SDL_KEYUP:
			m_KeyStates[e.key.keysym.sym] = KEY_UP;
			m_bAny = true;
			break;
		case SDL_MOUSEBUTTONDOWN:
		case SDL_MOUSEBUTTONUP:
			MouseClick(e);
			m_bAny = true;
			break;
		case SDL_MOUSEMOTION:
			m_tSelectorPos.x = e.motion.x;
			m_tSelectorPos.y = e.motion.y;
			break;
		default:
			break;
		}
	}
}

void CInputManager::Shutdown(void)
{
	SDL_FreeCursor(SDL_GetCursor());
}

// Change Cursors
void CInputManager::SetArrowCursor(void)
{
	SetCursor(SDL_SYSTEM_CURSOR_ARROW);
}

void CInputManager::SetHandCursor(void)
{
	SetCursor(SDL_SYSTEM_CURSOR_HAND);
}

// Input Checks
bool CInputManager::QuitEvent(void)
{
	return m_bQuit;
}

bool CInputManager::WindowResizeEvent(void)
{
	return m_bWindowResize;
}

bool CInputManager::SelectorUpEvent(void)
{
	return m_bSelectorUp;
}

bool CInputManager::SelectorDownEvent(void)
{
	return m_bSelectorDown;
}

bool CInputManager::AnyEvent(void)
{
	return m_bAny;
}

bool CInputManager::KeyEvent(SDL_Keycode tKey, eKEY_STATE eState)
{
	if (m_KeyStates[tKey] == eState)
		return true;
	return false;
}

// Event Data Accessors
SDL_Point CInputManager::GetWindowSize(void)
{
	return m_tWindowSize;
}

SDL_Point CInputManager::GetSelectorPos(void)
{
	return m_tSelectorPos;
}

void CInputManager::SetCursor(SDL_SystemCursor tType)
{
	SDL_FreeCursor(SDL_GetCursor());
	SDL_SetCursor(SDL_CreateSystemCursor(tType));
}

// Input Helpers
void CInputManager::MouseClick(SDL_Event e)
{
	switch (e.button.button)
	{
	case SDL_BUTTON_LEFT:
	{
		if (e.button.clicks >= 1)
		{
			m_tSelectorPos.x = e.button.x;
			m_tSelectorPos.y = e.button.y;
			if (e.type == SDL_MOUSEBUTTONUP)
			{
				m_bSelectorUp = true;
				m_bSelectorDown = false;
			}
			else if (e.type == SDL_MOUSEBUTTONDOWN)
				m_bSelectorDown = true;
		}
		break;
	}
	}
}

// Extra Helpers
SDL_bool PointInRect(const SDL_Point* p, const SDL_Rect*  r)
{
	if (p->x >= r->x && p->x <= r->x + r->w && p->y >= r->y && p->y <= r->y + r->h)
		return SDL_TRUE;

	return SDL_FALSE;
}

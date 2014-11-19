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
	m_bSelect = false;
	m_bAny = false;

	m_tWindowSize.x = m_tWindowSize.y = 0;
	m_tSelectPos.x = m_tSelectPos.y = 0;
}

void CInputManager::Input(void)
{
	m_bSelect = false;
	m_bQuit = false;
	m_bWindowResize = false;
	m_bAny = false;

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
		}
			break;
		case SDL_KEYUP:
			KeyUp(e);
			m_bAny = true;
			break;
		case SDL_MOUSEBUTTONUP:
			MouseUp(e);
			m_bAny = true;
			break;
		case SDL_MOUSEMOTION:
			m_tSelectPos.x = e.motion.x;
			m_tSelectPos.y = e.motion.y;
			break;
		}
	}
}

void CInputManager::Shutdown(void)
{

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

bool CInputManager::SelectEvent(void)
{
	return m_bSelect;
}

bool CInputManager::AnyEvent(void)
{
	return m_bAny;
}

// Event Data Accessors
SDL_Point CInputManager::GetWindowSize(void)
{
	return m_tWindowSize;
}

SDL_Point CInputManager::GetSelectPoint(void)
{
	return m_tSelectPos;
}

// Input Helpers
void CInputManager::KeyUp(SDL_Event e)
{
	switch (e.key.keysym.sym)
	{
	case SDLK_ESCAPE:
		m_bQuit = true;
		break;
	}
}

void CInputManager::MouseUp(SDL_Event e)
{
	switch (e.button.button)
	{
	case SDL_BUTTON_LEFT:
	{
		if (e.button.clicks >= 1)
		{
			m_tSelectPos.x = e.button.x;
			m_tSelectPos.y = e.button.y;
			m_bSelect = true;
		}
	}
		break;
	}
}

// Extra Helpers
SDL_bool PointInRect(const SDL_Point* p, const SDL_Rect*  r)
{
	if (p->x >= r->x && p->x <= r->x + r->w && p->y >= r->y && p->y <= r->y + r->h)
		return SDL_TRUE;

	return SDL_FALSE;
}

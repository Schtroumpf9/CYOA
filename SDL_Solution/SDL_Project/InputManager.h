#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include <map>

SDL_bool PointInRect(const SDL_Point* p, const SDL_Rect*  r);

class CInputManager
{
public:
	CInputManager(void);
	~CInputManager(void);

	void Initialize(void);
	void Input(void);
	void Shutdown(void);

	// Change Cursors
	void SetArrowCursor();
	void SetHandCursor();

	// Input Checks
	bool QuitEvent(void);
	bool WindowResizeEvent(void);
	bool SelectorUpEvent(void);
	bool SelectorDownEvent(void);
	bool AnyEvent(void);
	bool KeyEvent(SDL_Keycode tKey, eKEY_STATE eState);

	// Event Data Accessors
	SDL_Point GetWindowSize(void);
	SDL_Point GetSelectorPos(void);

private:
	// Cursor Set Helper
	void SetCursor(SDL_SystemCursor tType);
	// Input Helpers
	void MouseClick(SDL_Event e);

	// Specific Event checks
	bool m_bQuit;
	bool m_bWindowResize;
	bool m_bSelectorUp;
	bool m_bSelectorDown;
	bool m_bAny;

	std::map<SDL_Keycode, eKEY_STATE> m_KeyStates;

	// Event Data
	SDL_Point m_tWindowSize;
	SDL_Point m_tSelectorPos;
};
#endif

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
	void SetCursor(SDL_SystemCursor tType);

	// Input Checks
	bool QuitEvent(void) const { return m_bQuit; }
	bool WindowResizeEvent(void) const { return m_bWindowResize; }
	bool SelectorUpEvent(void) const { return m_bSelectorUp; }
	bool SelectorDownEvent(void) const { return m_bSelectorDown; }
	bool AnyEvent(void) const { return m_bAny; }
	bool ScrollEvent(void) const { return m_bScroll; }
	bool KeyEvent(SDL_Keycode tKey, eKEY_STATE eState);

	// Event Data Accessors
	SDL_Point GetWindowSize(void) const { return m_tWindowSize; }
	SDL_Point GetSelectorPos(void) const { return m_tSelectorPos; }
	Sint32 GetScrollAmount(void) const { return m_nScrollAmount; }

private:
	// Input Helpers
	void MouseClick(SDL_Event e);

	// Specific Event checks
	bool m_bQuit;
	bool m_bWindowResize;
	bool m_bSelectorUp;
	bool m_bSelectorDown;
	bool m_bAny;
	bool m_bScroll;

	std::map<SDL_Keycode, eKEY_STATE> m_KeyStates;

	// Event Data
	SDL_Point m_tWindowSize;
	SDL_Point m_tSelectorPos;
	Sint32 m_nScrollAmount;
};
#endif

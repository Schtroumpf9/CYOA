#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

SDL_bool PointInRect(const SDL_Point* p, const SDL_Rect*  r);

class CInputManager
{
public:
	CInputManager(void);
	~CInputManager(void);

	void Initialize(void);
	void Input(void);
	void Shutdown(void);

	// Input Checks
	bool QuitEvent(void);
	bool WindowResizeEvent(void);
	bool SelectEvent(void);

	// Event Data Accessors
	SDL_Point GetWindowSize(void);
	SDL_Point GetSelectPoint(void);

private:
	// Input Helpers
	void KeyUp(SDL_Event e);
	void MouseUp(SDL_Event e);

	// Event checks
	bool m_bQuit;
	bool m_bWindowResize;
	bool m_bSelect;

	// Event Data
	SDL_Point m_tWindowSize;
	SDL_Point m_tSelectPos;
};
#endif

#ifndef RENDER_MANAGER_H
#define RENDER_MANAGER_H

#include <forward_list>

class CQuad;

class CRenderManager
{
public:
	CRenderManager(void);
	~CRenderManager(void);

	void Initialize(void);
	void Render(void);
	void Resize(const SDL_Point& tWindowSize);
	void Shutdown(void);

	// Helpers
	void AddQuad(CQuad* pQuad);
	void RemoveQuad(CQuad* pQuad);
	void DeleteAllQuads(void);
	void UpdateQuad(CQuad* pQuad);

	// Accessors
	inline SDL_Renderer* GetRenderer(void) const { return m_pRenderer; }

private:
	// Helpers
	void RenderQuads(void);

	// SDL Variables
	SDL_Window* m_pWindow;
	SDL_Renderer* m_pRenderer;

	// Screen variables
	Uint32 m_unWindowWidth;
	Uint32 m_unWindowHeight;
	bool m_bFullscreen;

	std::forward_list<CQuad*> m_Quads;
};
#endif

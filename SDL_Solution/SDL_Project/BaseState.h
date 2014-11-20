#ifndef BASE_STATE_H
#define BASE_STATE_H

// TODO: Change to map of buttons to determine which button is pressed

#include "RenderManager.h"
#include "TextureManager.h"
#include "InputManager.h"
#include "FontManager.h"
#include "Quad.h"
#include "structs.h"
#include <map>
#include <sstream>

class CBaseState
{
public:
	CBaseState(void);
	virtual ~CBaseState(void);

	virtual void Initialize(CRenderManager* pRenderManager, CTextureManager* pTextureManager,
		CInputManager* pInputManager, CFontManager* pFontManager);
	virtual eSTATE_TYPE Update(float fDeltaTime);
	void Shutdown(void);

	// Accessors
	const eSTATE_TYPE GetType(void) const { return m_eType; }

protected:
	// Helpers
	CQuad* CreateQuad(const char* szTextureName = NULL, const FloatRect& tDstRect = { 0.0f, 0.0f, 1.0f, 1.0f }, const eLAYER& ucLayer = MID_LAYER, const SDL_Color& tColor = { 255, 255, 255, 255 });

	eSTATE_TYPE m_eType;

	// Managers
	CRenderManager* m_pRenderManager;
	CTextureManager* m_pTextureManager;
	CInputManager* m_pInputManager;
	CFontManager* m_pFontManager;

	// Buttons to check against input
	std::map<Sint16, CQuad*> m_Buttons;
	Sint16 m_sOverKey;

private:
	// FPS Data
	Uint32 m_unFrameCount;
	Uint32 m_unStartTime;
	float m_fFPS;
	std::ostringstream m_OSS;
	CQuad* m_pFPSTextQuad;
	CQuad* m_pFPSQuad;
};
#endif

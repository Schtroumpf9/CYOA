#ifndef BASE_STATE_H
#define BASE_STATE_H

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
	CQuad* CreateQuad(const char* szTextureName, const FloatRect& tDstRect = { 0.0f, 0.0f, 1.0f, 1.0f },
		const eQUAD_POS_TYPE ePosType = TOP_LEFT_POS, const eQUAD_TYPE eType = CUSTOM_QUAD, const eLAYER eLayer = MID_LAYER);
	CQuad* CreateQuad(const SDL_Color tColor, const FloatRect& tDstRect = { 0.0f, 0.0f, 1.0f, 1.0f },
		const eQUAD_POS_TYPE ePosType = TOP_LEFT_POS, const eQUAD_TYPE eType = CUSTOM_QUAD, const eLAYER eLayer = MID_LAYER);
	void ProcessButtons(void);
	static char* ReadString(SDL_RWops* pFile);

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

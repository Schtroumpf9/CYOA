#include "std.h"
#include "OptionsState.h"


COptionsState::COptionsState()
{
	m_eType = OPTIONS_STATE;
}


COptionsState::~COptionsState()
{
}

void COptionsState::Initialize(CRenderManager* pRenderManager, CTextureManager* pTextureManager,
	CInputManager* pInputManager, CFontManager* pFontManager)
{
	CBaseState::Initialize(pRenderManager, pTextureManager, pInputManager, pFontManager);

	// Add Initial Images
	CQuad* pQuad;
	CQuad* pText;

	// Background
	CreateQuad(NULL, FloatRect{ 0.f, 0.f, 1.f, 1.f }, BACK, SDL_Color{ 0, 0, 0, 255 });

	// Options
	pText = m_pFontManager->TTFCreateText("Back", SDL_Color{ 0, 127, 127, 255 }, TextData{ .5f, .5f, .05f, MIDDLE });

	// Button
	FloatRect tDstRect(pText->GetDstRect());
	tDstRect.x -= 0.025f;
	tDstRect.y -= 0.025f;
	tDstRect.w += 0.05f;
	tDstRect.h += 0.05f;
	pQuad = CreateQuad(NULL, tDstRect, MID, SDL_Color{ 95, 95, 95, 255 });
	m_Buttons.push_front(pQuad);
}

eSTATE_TYPE COptionsState::Update(float fDeltaTime)
{
	if (m_pInputManager->SelectEvent())
	{
		SDL_Rect buttonRect;
		SDL_Point selectPos = m_pInputManager->GetSelectPoint();
		std::forward_list<CQuad*>::iterator buttonIter = m_Buttons.begin();
		for (; buttonIter != m_Buttons.cend(); ++buttonIter)
		{
			buttonRect = (*buttonIter)->GetPixelDstRect();

			if (PointInRect(&selectPos, &buttonRect) == SDL_TRUE)
			{
				return MENU_STATE;
			}
		}
	}

	return CBaseState::Update(fDeltaTime);
}

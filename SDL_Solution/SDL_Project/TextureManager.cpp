#include "std.h"
#include "TextureManager.h"
#include <SDL_image.h>
#include <string>

CTextureManager::CTextureManager(void) : m_pRenderer(NULL)
{
}


CTextureManager::~CTextureManager(void)
{
}

void CTextureManager::Initialize(SDL_Renderer* pRenderer)
{
	m_pRenderer = pRenderer;
}

void CTextureManager::Shutdown(void)
{
	std::map<const char*, SDL_Texture*>::const_iterator textureIter;
	for(textureIter = m_Textures.cbegin(); textureIter != m_Textures.cend(); ++textureIter)
	{
		SDL_DestroyTexture((*textureIter).second);
	}
	m_Textures.clear();
}

SDL_Texture* CTextureManager::GetTexture(const char* szName)
{
	if(m_Textures.find(szName) == m_Textures.cend())
	{
		std::string szFullPath = "../Textures/";
		szFullPath += szName;
		m_Textures[szName] = LoadTexture(szFullPath.c_str());
	}

	return m_Textures[szName];
}

SDL_Texture* CTextureManager::LoadTexture(const char* szPath)
{
	SDL_Texture* newTexture = NULL;

	SDL_Surface* loadedSurface = IMG_Load( szPath );
	SDL_ERROR_CHECK(loadedSurface == NULL, szPath);

	newTexture = SDL_CreateTextureFromSurface( m_pRenderer, loadedSurface );
	SDL_ERROR_CHECK(newTexture == NULL, szPath);

	SDL_FreeSurface( loadedSurface );

	return newTexture;
}

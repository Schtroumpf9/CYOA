#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

#include <map>

class CTextureManager
{
public:
	CTextureManager(void);
	~CTextureManager(void);

	void Initialize(SDL_Renderer* pRenderer);
	void Shutdown(void);

	SDL_Texture* GetTexture(const char* szName);

private:
	std::map<const char*, SDL_Texture*> m_Textures;
	SDL_Renderer* m_pRenderer;

	SDL_Texture* LoadTexture(const char* szPath);
};
#endif

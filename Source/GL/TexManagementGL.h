#ifndef TEXMANAGEMENTGL_H
#define TEXMANAGEMENTGL_H

#include "Texture.h"
#include "../GraphicsContainer.h"

static const std::string texPath		= "../../Textures/";

static const std::string texPacman		= "PacManTex.tga";
static const std::string texWall		= "Wall.tga";
static const std::string texPill		= "Pill.tga";
static const std::string texPillBloody	= "BloodyPill.tga";
static const std::string texPlaceHolder	= "PlaceHolder.tga";
static const std::string texConsume		= "Consume.tga";

class TexManagementGL
{
private:
	std::vector<Texture*>* textures;
protected:
	Texture* loadTexture(TextureId id, std::string completePath);
	std::string fetchTexPath(TextureId texId);
public:
	Texture* getTexture(TextureId textureId);

	void init();
	
	TexManagementGL();
	virtual ~TexManagementGL();
};

#endif //TEXMANAGEMENTGL_H
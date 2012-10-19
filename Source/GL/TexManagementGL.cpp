#include "TexManagementGL.h"

std::string TexManagementGL::fetchTexPath(TextureId texId)
{
	std::string pathComplete = texPath;
	switch(texId)
	{
	case TEXTURE_PACMAN:
		pathComplete += texPacman;
		break;
	case TEXTURE_WALL:
		pathComplete += texWall;
		break;
	case TEXTURE_PILL:
		pathComplete += texPill;
		break;
	case TEXTURE_PILL_BLOODY:
		pathComplete += texPillBloody;
		break;
	default:
		pathComplete += texPlaceHolder;
		break;
	}
	return pathComplete;
}

void TexManagementGL::init()
{
	std::vector<TextureId>* loadTex = new std::vector<TextureId>();
	loadTex->push_back(TEXTURE_PACMAN);
	loadTex->push_back(TEXTURE_PILL);
	loadTex->push_back(TEXTURE_PILL_BLOODY);
	loadTex->push_back(TEXTURE_GHOST);
	loadTex->push_back(TEXTURE_WALL);
	loadTex->push_back(TEXTURE_PLACEHOLDER);
	
	std::string completePath;
	for(unsigned int i = 0; i < loadTex->size(); i++)
	{
		completePath = fetchTexPath(loadTex->at(i));
		Texture* tex = loadTexture(loadTex->at(i), completePath);

		textures->push_back(tex);
	}
}
Texture* TexManagementGL::loadTexture(TextureId id, std::string completePath)
{
	Texture* texture = new Texture();
	texture->textureId = id;

	bool textureLoaded = LoadTGA(texture, completePath.c_str());
	if(textureLoaded)
	{
		//Creates a texture and put it's ID in the given integer variable
		glGenTextures(1, &(texture->texID));

		//Setting as active texture
		glBindTexture(GL_TEXTURE_2D, texture->texID);

		//Load texture into memory
		glTexImage2D(
			GL_TEXTURE_2D, 
			0, 
			texture->bpp / 8, 
			texture->width, 
			texture->height, 
			0, 
			texture->type, 
			GL_UNSIGNED_BYTE, 
			texture->imageData);
	}
	else
	{
		throw 0;
	}

	return texture;
}

Texture* TexManagementGL::getTexture(TextureId textureId)
{
	Texture* texture = NULL;

	bool textureFound = false;
	for(unsigned int i = 0; i < textures->size() && !textureFound; i++)
	{
		if(textures->at(i)->textureId == textureId)
		{
			texture = textures->at(i);
			textureFound = true;
		}
	}

	return texture;
}

TexManagementGL::TexManagementGL()
{
	textures = new std::vector<Texture*>();
}
TexManagementGL::~TexManagementGL()
{
	if(textures)
	{
		for(unsigned int i = 0; i < textures->size(); i++)
		{
			if(textures->at(i))
			{
				free(textures->at(i)->imageData); //Free raw image data
				delete textures->at(i);
			}
		}
		delete textures;
	}
}
#ifndef __TGA_HEADER__
#define __TGA_HEADER__

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "CommonGL.h"

#include "../TextureId.h"

typedef	struct									
{
	GLubyte* imageData;									// Image Data (Up To 32 Bits)
	GLuint	bpp;											// Image Color Depth In Bits Per Pixel
	GLuint	width;											// Image Width
	GLuint	height;											// Image Height
	GLuint	texID;											// Texture ID Used To Select A Texture
	GLuint	type;											// Image Type (GL_RGB, GL_RGBA)
	TextureId textureId;
} Texture;	

typedef struct
{
	GLubyte Header[12];									// TGA File Header
} TGAHeader;


typedef struct
{
	GLubyte		header[6];								// First 6 Useful Bytes From The Header
	GLuint		bytesPerPixel;							// Holds Number Of Bytes Per Pixel Used In The TGA File
	GLuint		imageSize;								// Used To Store The Image Size When Setting Aside Ram
	GLuint		temp;									// Temporary Variable
	GLuint		type;	
	GLuint		Height;									//Height of Image
	GLuint		Width;									//Width ofImage
	GLuint		Bpp;									// Bits Per Pixel
} TGA;

bool LoadTGA(Texture * texture, const char * filename);
bool LoadCompressedTGA(Texture * texture, const char * filename, FILE * fTGA);
bool LoadUncompressedTGA(Texture * texture, const char * filename, FILE * fTGA);

#endif //__TGA_HEADER__
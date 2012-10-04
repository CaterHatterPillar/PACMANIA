#ifndef FXMANAGEMENTGL_H
#define FXMANAGEMENTGL_H

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>

#include "FXGL.h"
#include "CommonGL.h"
#include "Texture.h"

#include "../GraphicsContainer.h"
#include "../../Common.h"

#define DEFAULT_VERTEX_PATH		"root/Resources/Shaders/GL/DefaultVertexShader.glsl"
#define DEFAULT_FRAGMENT_PATH	"root/Resources/Shaders/GL/DefaultFragmentShader.glsl"

class FXManagementGL
{
private:
	std::vector<FXGL*>* fxs;

	void initFXs();
	void createFX(
		ShaderId vertexShaderID,
		ShaderId fragmentShaderID);
	
	GLuint createProgramFX(
		ShaderId vertexShaderID,
		ShaderId fragmentShaderID);
	void fetchShaderPaths(
		ShaderId		vs,
		std::string&	vss,
		ShaderId		fs,
		std::string&	fss);

	GLuint createObjFX(
		const char*	shaderText,
		GLenum		shaderType);

	/*loading*/
	char* file2string(const char *path);
protected:
public:
	void init();

	FXGL* getFX(
		ShaderId vertexShaderID,
		ShaderId fragmentShaderID);

	FXManagementGL();
	~FXManagementGL();
};

#endif //FXMANAGEMENT_H
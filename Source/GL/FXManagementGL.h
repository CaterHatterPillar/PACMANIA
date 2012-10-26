#ifndef FXMANAGEMENTGL_H
#define FXMANAGEMENTGL_H
 
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
 
#include "FXGL.h"
#include "CommonGL.h"
#include "../GraphicsContainer.h"
#include "../Common.h"
     
#include "../Light.h"

#define SHADER_PATH				"../../Shaders/GL/"
#define SHADER_DEFAULT_VERTEX	"DefaultVertexShader.glsl"
#define SHADER_DEFAULT_FRAGMENT	"DefaultFragmentShader.glsl"
     
class FXManagementGL
{
private:
	std::vector<FXGL*>* fxs;
	
	GLuint		perFrameHandle;
	GLint		perFrameSize;
	GLubyte*	perFrameBuffer;
	
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
		const char*     shaderText,
		GLenum          shaderType);
 
	/*loading*/
	char* file2string(const char *path);
protected:
public:
	void init();
	void initPerFrame(GLuint programFX);

	void updatePerFrame(Light lights[], VecF3 camPos);
	
	FXGL* getFX(
		ShaderId vertexShaderID,
		ShaderId fragmentShaderID);
	
	FXManagementGL();
	virtual ~FXManagementGL();
};
 
#endif //FXMANAGEMENT_H

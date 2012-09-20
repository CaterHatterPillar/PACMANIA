#ifndef FXMANAGEMENTGL_H
#define FXMANAGEMENTGL_H

#include "../../Common.h"
#include "CommonGL.h"

#include "FXGL.h"

/*Tempshaders*/
static const char* VS = "													\n\
						#version 330										\n\
																			\n\
						layout (location = 0) in vec3 Position;				\n\
																			\n\
						uniform mat4 transform;								\n\
																			\n\
						out vec4 Color;										\n\
																			\n\
						void main()											\n\
						{													\n\
						gl_Position = transform * vec4(Position, 1.0f);		\n\
						Color = vec4(clamp(Position, 0.0, 1.0), 1.0);		\n\
						}";
static const char* PS = "												\n\
						#version 330									\n\
																		\n\
						in vec4 Color;									\n\
																		\n\
						out vec4 fragColor;								\n\
																		\n\
						void main()										\n\
						{												\n\
							fragColor = Color;							\n\
						}";

class FXManagementGL
{
private:
	std::vector<FXGL*>* fxs;

	void initFXs();

	//param - file name, enum
	void createFX(ID_FX idFX);
	GLuint createProgramFX();
	GLuint createObjFX(const char*	shaderText, GLenum shaderType);
protected:
public:
	void init();

	FXGL* getFX(ID_FX idFX);

	FXManagementGL();
	~FXManagementGL();
};

#endif //FXMANAGEMENT_H
#ifndef FXMANAGEMENTGL_H
#define FXMANAGEMENTGL_H

#include "../../Common.h"
#include "CommonGL.h"

#include "FXGL.h"

/*Tempshaders*/
static const char* VS = "							\n\
						#version 330										\n\
						\n\
						layout (location = 0) in vec3 Position;				\n\
						\n\
						uniform mat4 wvp;									\n\
						\n\
						out vec4 Color;										\n\
						\n\
						void main()											\n\
						{													\n\
						gl_Position = vec4(Position, 1.0f);		\n\
						Color = vec4(clamp(Position, 0.0, 1.0), 1.0);	\n\
						}";
static const char* PS = "						\n\
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
protected:
public:
	void init();
	void createFX(ID_FX idFX);

	FXGL* getFX();

	FXManagementGL();
	~FXManagementGL();
};

#endif //FXMANAGEMENT_H
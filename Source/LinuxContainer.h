#ifndef LINUXCONTAINER_H
#define LINUXCONTAINER_H

#include "Game/Game.h"
#include "Game/GameEntity.h"

#include "Camera.h"
#include "Common.h"

#include "GL/WindowGL.h"
#include "GL/RendererGL.h"
#include "GL/CameraGL.h"
#include "GL/InputGL.h"
#include "GL/GameEntityFactoryGL.h"

class LinuxContainer
{
private:
protected:
public:
	void initLinux(
		WindowGL*	windowGL, 
		RendererGL*	rendererGL,
		InputGL*	inputGL,
		CameraGL*	cameraGL);
	void mainContainer(int argc, char** argv);

	LinuxContainer() {}
	~LinuxContainer() {}
};

#endif //LINUXCONTAINER_H

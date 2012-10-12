#ifndef LINUXCONTAINER_H
#define LINUXCONTAINER_H

#include "Game.h"
#include "GameEntity.h"

#include "Renderer/Camera.h"

#include "Renderer/GL/WindowGL.h"
#include "Renderer/GL/RendererGL.h"
#include "Renderer/GL/CameraGL.h"
#include "Renderer/GL/InputGL.h"

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
	GameEntity* initPacman();
	void mainContainer(int argc, char** argv);

	LinuxContainer() {}
	~LinuxContainer() {}
};

#endif //LINUXCONTAINER_H

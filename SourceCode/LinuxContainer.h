#ifndef LINUXCONTAINER_H
#define LINUXCONTAINER_H

/*memleaks*/
#include <vld.h>
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include "Renderer/GL/WindowGL.h"
#include "Renderer/GL/RendererGL.h"
#include "Renderer/GL/CameraGL.h"
#include "Renderer/Camera.h"
#include "InputGL.h"
#include "GameEntity.h"
#include "Game.h"

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
	void main(int argc, char** argv);

	LinuxContainer() {}
	~LinuxContainer() {}
};

#endif //LINUXCONTAINER_H
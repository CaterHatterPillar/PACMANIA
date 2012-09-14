#ifndef WINDOWS

#include "WindowGL.h"

WindowGL::WindowGL(int argc, char** argv)
{
	this->argc = argc;
	this->argv = argv;
}
WindowGL::~WindowGL()
{

}

void WindowGL::init()
{
	/*Initialize window through GLUT*/
	glutInit(&argc, argv);								//Initialize GLUT
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);		//Set double buffer-swap and back-buffer

	glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);	//Initialize window
	glutInitWindowPosition(100, 100);					//...
	glutCreateWindow("PACMANIA");						//...
	
	//glutGameModeString("1920x1200@32");
	//glutEnterGameMode();

	/*Initialize GLUT-callback*/

	/*Initialize GLEW,
	* must be initialized after glut
	*/
	GLenum result = glewInit();
	if (result != GLEW_OK)
		throw 0; //fix

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f); //set a colour for brevity
}
void WindowGL::update(double delta)
{

}

#endif //WINDOWS
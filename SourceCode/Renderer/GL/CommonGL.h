#ifndef COMMONGL_H
#define COMMONGL_H

//Windows
#ifdef _WIN32
#include <windows.h>
#include <glew.h>
#include <freeglut.h>
#include <gl\gl.h>
#endif

//OSX
#ifdef __APPLE__
#include <TargetConditionals.h>
#if TARGET_OS_IPHONE | TARGET_IPHONE_SIMULATOR
#include <OpenGLES/ES2/gl.h>
#include <glut.h>
#include <OpenGLES/ES2/glext.h>
#define OPENGL_ES
#else
#include <GL/glew.h>
#include <OpenGL/gl.h>
#include <glut.h>
#endif
#endif

//Linux
#ifdef linux
//#define GLEW_STATIC
#include <glew.h>
#include <glut.h>
#include <freeglut.h>
#endif

#endif //COMMONGL_H

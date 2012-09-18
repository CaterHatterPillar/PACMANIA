#include "RendererGL.h"

FXManagementGL*			RendererGL::fxManagement;

RendererGL::RendererGL() : Renderer()
{
	fxManagement	= new FXManagementGL();
	renderList		= new std::vector<GraphicsContainer*>();
}
RendererGL::~RendererGL()
{
	if(fxManagement)
		delete fxManagement;

	if(renderList)
		delete renderList;
}
void RendererGL::cleanUp()
{

}

void RendererGL::init()
{
	/*Initialize shaders*/
	fxManagement->init();

	/*Subscribe*/
	SubscriptionMsg* subscription = new SubscriptionMsg(this, RENDER);
	Singleton<ObserverDirector>::get().push(subscription);

	/*Send initial callback-specs to GLUT*/
	MsgGlutCallback* callbackMsg = new MsgGlutCallback(renderSpec, DISPLAY_FUNC);
	Singleton<ObserverDirector>::get().push(callbackMsg);

	callbackMsg = new MsgGlutCallback(renderSpec, IDLE_FUNC);
	Singleton<ObserverDirector>::get().push(callbackMsg);
}
void RendererGL::update(double delta)
{
	/*Clear renderList*/
	renderList->resize(0);

	Msg* msg = peek();
	while(msg)
	{
		msg = pop();
		if(msg)
		{
			MsgType type = msg->Type();
			switch(type)
			{
			case RENDER:
				msgRender(msg);
				break;
			default:
				throw 0; //temp
			}
		}
	}
}
void RendererGL::msgRender(Msg* msg)
{
	MsgRender* msgRender = (MsgRender*)msg;
	renderList->push_back(msgRender->getGraphicsContainer());
	delete msgRender;
}

void RendererGL::renderFrame()
{
}

/*GLUT callbacks*/
void RendererGL::renderSpec()
{
	glutPostRedisplay();

	/*Clear backbuffer*/
	glClear(GL_COLOR_BUFFER_BIT);

	for(unsigned int i = 0; i < renderList->size(); i++)
	{
		GraphicsContainer* graphicsContainer = renderList->at(i);
		GraphicsContainerGL* currentContainer
			= (GraphicsContainerGL*)graphicsContainer;

		setShader();
		//Set resources
		//material
		//..etc

		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, currentContainer->vertexBuffer);
		glVertexAttribPointer(
			0,			//Index of attribute
			3,			//Number of components in attribute (x, y, z)
			GL_FLOAT,	//Data type of each component
			GL_FALSE,	//Specifies if we want attribute to be normalized
			0,			//Stride
			0);			//Offset
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, currentContainer->indexBuffer);

		glDrawElements(
			GL_TRIANGLES,		//Type to render
			12,					//Number of indices
			GL_UNSIGNED_INT,	//Index-type (for size)
			0);					//Offset
		glDisableVertexAttribArray(0);
	}
	
	glutSwapBuffers();

	//glutLeaveMainLoop();
}
void RendererGL::setShader()
{
	/*Get correct shader program*/
	FXGL* fx			= fxManagement->getFX(BASIC);
	GLuint programFX	= fx->ProgramFX();

	/*Checks whether or not the program object can execute the pipeline in it's current state*/
	glValidateProgram(programFX);
	/*Connect shader program to pipeline*/
	glUseProgram(programFX);
}
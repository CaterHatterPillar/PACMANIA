#include "RendererGL.h"

//FXManagementGL* RendererGL::fxManagement;
/*
MatF4	RendererGL::view;
GLuint	RendererGL::viewFX;

MatF4	RendererGL::proj;
GLuint	RendererGL::projFX;

MatF4	RendererGL::worldViewProj;
GLuint	RendererGL::worldViewProjFX;
*/

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
	fxManagement->init();

	/*Subscribe*/
	SubscriptionMsg* subscription = new SubscriptionMsg(this, RENDER);
	Singleton<ObserverDirector>::get().push(subscription);

	subscription = new SubscriptionMsg(this, CAMERA);
	Singleton<ObserverDirector>::get().push(subscription);

	/*Send initial callback-specs to GLUT*/
	MsgGlutCallback* callbackMsg = new MsgGlutCallback(renderSpec, DISPLAY_FUNC);
	Singleton<ObserverDirector>::get().push(callbackMsg);

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f); //set a colour for brevity
}

void RendererGL::update(double delta)
{
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
			case CAMERA:
				msgCamera(msg);
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
void RendererGL::msgCamera(Msg* msg)
{
	MsgCamera* cameraMsg = (MsgCamera*)msg;
	
	this->proj = cameraMsg->Proj();
	this->view = cameraMsg->View();

	delete cameraMsg;
}
void RendererGL::renderFrame()
{
}

/*Callback renderspec*/
void RendererGL::renderSpec()
{
	/*Clear backbuffer*/
	glClear(GL_COLOR_BUFFER_BIT);

	GraphicsContainerGL* graphicsGL;
	for(unsigned int i = 0; i < renderList->size(); i++)
	{
		graphicsGL = renderList->at(i);
		renderGraphicsGL(graphicsGL);
	}
	
	glutSwapBuffers();
}
void RendererGL::renderGraphicsGL(GraphicsContainerGL* containerGL)
{
	setShader();

	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	/*Specifies how buffer is to be interpreted*/
	glVertexAttribPointer(
		0,			//Index of attribute
		3,			//Number of components in attribute (x, y, z)
		GL_FLOAT,	//Data type of each component
		GL_FALSE,	//Specifies if we want attribute to be normalized
		0,			//Stride
		0);			//Offset

	/*Set index buffer*/
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);

	/*Draw-call using indices*/
	glDrawElements(
		GL_TRIANGLES,		//Type to render
		12,					//Number of indices
		GL_UNSIGNED_INT,	//Index-type (for size)
		0);					//Offset

	/*Disable*/
	glDisableVertexAttribArray(0);
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

	/*Connect uniforms*/
	std::vector<UniformGL*>* uniforms = fx->Uniforms();
	for(unsigned int i = 0; i < uniforms->size(); i++)
	{
		UniformGL*		uniformGL	= uniforms->at(i);
		GLuint			handle		= uniformGL->Uniform();
		UNIFORM_TYPE	type		= uniformGL->Type();

		if(type == MATRIX4F)
		{
			MatF4 world;
			world.translation(1.0f, 1.0f, 1.0f);

			MatF4 trans = world * view * proj;
			glUniformMatrix4fv(handle, 1, GL_TRUE, &trans.m[0][0]);
		}
		else
			throw 0; //temp

		GLuint uniform = glGetUniformLocation(programFX, "transform");//handle);
		assert(uniform != 0xFFFFFFFF);

		MatF4 world;
		world.translation(0.0f, 0.0f, 5.0f);

		MatF4 trans = proj * view * world;
		glUniformMatrix4fv(uniform, 1, GL_TRUE, &trans.m[0][0]);
	}
}

/*Update transform*/
		//MatF4 world;
		//world.translation(0.0f, 0.0f, 5.0f);
		//trans = proj * view * world;
		//glUniformMatrix4fv(worldViewProjFX, 1, GL_TRUE, &trans.m[0][0]);
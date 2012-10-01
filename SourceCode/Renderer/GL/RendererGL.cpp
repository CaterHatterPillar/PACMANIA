#include "RendererGL.h"

FXManagementGL* RendererGL::fxManagement;

MatF4	RendererGL::view;
MatF4	RendererGL::proj;
MatF4	RendererGL::worldViewProj;

GLuint	RendererGL::worldViewProjFX;

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

	glEnable(GL_DEPTH_TEST);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
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

void RendererGL::renderFrame()
{
}

/*Callback renderspec*/
void RendererGL::renderSpec()
{
	prepareRender();

	GraphicsContainerGL* graphicsGL;
	for(unsigned int i = 0; i < renderList->size(); i++)
	{
		graphicsGL = (GraphicsContainerGL*)(renderList->at(i));
		renderGraphicsGL(graphicsGL);
		deBindGraphicsGL();
	}
	
	glutSwapBuffers();
}
void RendererGL::prepareRender()
{
	glClear(GL_COLOR_BUFFER_BIT);	//clear backbuffer
	glClear(GL_DEPTH_BUFFER_BIT);	//clear depthbuffer
}
void RendererGL::renderGraphicsGL(GraphicsContainerGL* containerGL)
{
	if(containerGL->OutdatedVB())
	{
		containerGL->createVB();
		containerGL->OutdatedVB(false);
	}
	if(containerGL->OutdatedIB())
	{
		containerGL->createIB();
		containerGL->OutdatedIB(false);
	}

	unsigned int numVertices	= containerGL->getNumVertices();
	unsigned int numIndices		= containerGL->getNumIndices();
	unsigned int numFaces		= containerGL->getNumFaces();
	unsigned int stride			= containerGL->getStride();
	unsigned int offset			= containerGL->getOffset();

	ShaderId vertexShaderID		= containerGL->getVertexShaderId();
	ShaderId fragmentShaderID	= containerGL->getPixelShaderId();

	GLuint vb = containerGL->VB();
	GLuint ib = containerGL->IB();

	setShader(vertexShaderID, fragmentShaderID);
	setBuffers(vb, ib);

	glDrawElements(
		GL_TRIANGLES,		//Type to render
		numIndices,			//Number of indices
		GL_UNSIGNED_INT,	//Index-type (for size)
		0);					//Offset
}
void RendererGL::setShader(ShaderId vertexShader, ShaderId fragmentShader)
{
	/*Get correct shader program*/
	FXGL* fx			= fxManagement->getFX(vertexShader, fragmentShader);
	GLuint programFX	= fx->ProgramFX();

	/*Checks whether or not the program object can execute the pipeline in it's current state*/
	glValidateProgram(programFX);
	/*Connect shader program to pipeline*/
	glUseProgram(programFX);

	/*Connect uniforms*/
	worldViewProjFX = glGetUniformLocation(programFX, "wvp");
	assert(worldViewProjFX != 0xFFFFFFFF);

	MatF4 world;
	world.translation(0.0f, 0.0f, 5.0f);
	worldViewProj = proj * view * world;
	glUniformMatrix4fv(worldViewProjFX, 1, GL_TRUE, &worldViewProj.m[0][0]);
}
void RendererGL::setBuffers(GLuint vb, GLuint ib)
{
	glBindBuffer(GL_ARRAY_BUFFER, vb);

	glVertexAttribPointer(
		0,							//Index of attribute
		3,							//Number of components in attribute (x, y, z)
		GL_FLOAT,					//Data type of each component
		GL_FALSE,					//Specifies if we want attribute to be normalized
		sizeof(PosNormTex),			//Stride
		0);							//Offset of attribute
	glEnableVertexAttribArray(PosNormTex_POS);

	glVertexAttribPointer(
		1,
		3,
		GL_FLOAT,
		GL_FALSE,
		sizeof(PosNormTex),
		(void*)(sizeof(VecF3)));
	glEnableVertexAttribArray(PosNormTex_NORM);

	glVertexAttribPointer(
		2,
		2,
		GL_FLOAT,
		GL_FALSE,
		sizeof(PosNormTex),
		(void*)(sizeof(VecF3) * 2));
	glEnableVertexAttribArray(PosNormTex_TEX);

	/*Set index buffer*/
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ib);
}
void RendererGL::deBindGraphicsGL()
{
	glDisableVertexAttribArray(PosNormTex_POS);
	glDisableVertexAttribArray(PosNormTex_NORM);
	glDisableVertexAttribArray(PosNormTex_TEX);
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

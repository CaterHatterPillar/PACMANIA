#include "RendererGL.h"

FXManagementGL*		RendererGL::fxManagement;
TexManagementGL*	RendererGL::texManagement;

MatF4	RendererGL::view;
MatF4	RendererGL::proj;
MatF4	RendererGL::worldViewProj;
GLuint	RendererGL::worldViewProjFX;
GLuint	RendererGL::worldFX;

GLuint	RendererGL::sampler;

GraphicsContainerGL* RendererGL::prevGC;

Light RendererGL::lights[10];

RendererGL::RendererGL() : Renderer()
{
	fxManagement	= new FXManagementGL();
	texManagement	= new TexManagementGL();
	renderList		= new std::vector<MsgRender*>();

	prevGC = NULL;
}
RendererGL::~RendererGL()
{
	DELETE_NULL(fxManagement);
	DELETE_NULL(texManagement);

	prevGC = NULL;
}
void RendererGL::cleanUp()
{

}

void RendererGL::init()
{
	initFX();

	texManagement->init();

	/*Subscribe*/
	SubscriptionMsg* subscription = new SubscriptionMsg(this, RENDER);
	Singleton<ObserverDirector>::get().push(subscription);

	subscription = new SubscriptionMsg(this, CAMERA);
	Singleton<ObserverDirector>::get().push(subscription);

	subscription = new SubscriptionMsg(this, LIGHT);
	Singleton<ObserverDirector>::get().push(subscription);

	/*Send initial callback-specs to GLUT*/
	MsgGlutCallback* callbackMsg = new MsgGlutCallback((void*)renderSpec, DISPLAY_FUNC);
	Singleton<ObserverDirector>::get().push(callbackMsg);

	/*Set z-buffer*/
	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);

	/*Set backface cullint*/
	//glEnable(GL_CULL_FACE);
	//glCullFace(GL_FRONT);

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
}
void RendererGL::initFX()
{
	fxManagement->init();

	//Get correct shader program
	FXGL* fx			= fxManagement->getFX(VERTEX_SHADER_DEFAULT, PIXEL_SHADER_DEFAULT);
	GLuint programFX	= fx->ProgramFX();

	//Checks whether or not the program object can execute the pipeline in it's current state
	glValidateProgram(programFX);

	//Connect shader program to pipeline
	glUseProgram(programFX);

	//Connect uniforms
	worldViewProjFX = glGetUniformLocation(programFX, "wvp");
	assert(worldViewProjFX != 0xFFFFFFFF);
	worldFX = glGetUniformLocation(programFX, "world");
	assert(worldFX != 0xFFFFFFFF);
	sampler = glGetUniformLocation(programFX, "sampler");
	assert(sampler != 0xFFFFFFFF);

	glUniform1i(sampler, 0);
}

void RendererGL::update(double delta)
{
	for(unsigned int i = 0; i < renderList->size(); i++)
	{
		delete renderList->at(i);
		renderList->at(i) = NULL;
	}
	renderList->clear();
	renderList->resize(0);

	curLight = 0;

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
			case LIGHT:
				msgLight(msg);
				break;
			default:
				throw 0; //temp
			}
		}
	}

	fxManagement->updatePerFrame(lights, camPos);
}

void RendererGL::renderFrame()
{
}

/*Callback renderspec*/
void RendererGL::renderSpec()
{
	prepareRender();

	MsgRender* renderMsg;
	for(unsigned int i = 0; i < renderList->size(); i++)
	{
		renderMsg = renderList->at(i);
		renderGraphicsGL(
			(GraphicsContainerGL*)(renderMsg->getGraphicsContainer()),
			renderMsg->getTranslationMatrix(),
			renderMsg->getRotationMatrix(),
			renderMsg->getScalingMatrix());
		deBindGraphicsGL();
	}
	
	
	glutSwapBuffers();
}
void RendererGL::prepareRender()
{
	glClear(GL_COLOR_BUFFER_BIT);	//clear backbuffer
	glClear(GL_DEPTH_BUFFER_BIT);	//clear depthbuffer
}
void RendererGL::renderGraphicsGL(
	GraphicsContainerGL*	containerGL,
	MatF4					translation,
	MatF4					rotation,
	MatF4					scaling)
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
	if(containerGL->OutdatedTex())
	{
		Texture* preloadedTex = texManagement->getTexture(containerGL->getTextureId());
		containerGL->createTex(preloadedTex);
		containerGL->OutdatedTex(false);
	}

	if(containerGL != prevGC)
	{
		setBuffers(containerGL);
		setTextures(containerGL);

		prevGC = containerGL;
	}
	rotation.transpose();
	setUniform(translation, rotation, scaling);

	unsigned int numIndices = containerGL->getNumIndices();
	glDrawElements(
		GL_TRIANGLES,		//Type to render
		numIndices,			//Number of indices
		GL_UNSIGNED_INT,	//Index-type (for size)
		0);					//Offset
}

void RendererGL::setUniform(MatF4 translation, MatF4 rotation, MatF4 scaling)
{
	MatF4 world	= translation * scaling * rotation;
	
	worldViewProj = proj * view * world;
	glUniformMatrix4fv(worldViewProjFX, 1, GL_TRUE, &worldViewProj.m[0][0]);
	glUniformMatrix4fv(worldFX, 1, GL_TRUE, &world.m[0][0]);
}
void RendererGL::setBuffers(GraphicsContainerGL* containerGL)
{
	GLuint vb = containerGL->VB();
	GLuint ib = containerGL->IB();

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
void RendererGL::setTextures(GraphicsContainerGL* containerGL)
{
	Texture* tex = containerGL->Tex();

	//Setting as active texture
	glBindTexture(GL_TEXTURE_2D, tex->texID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glEnable(GL_TEXTURE_2D);
}
void RendererGL::deBindGraphicsGL()
{
	//glDisableVertexAttribArray(PosNormTex_POS);
	//glDisableVertexAttribArray(PosNormTex_NORM);
	//glDisableVertexAttribArray(PosNormTex_TEX);
}

void RendererGL::msgRender(Msg* msg)
{
	MsgRender* msgRender = (MsgRender*)msg;
	renderList->push_back(msgRender);
}
void RendererGL::msgCamera(Msg* msg)
{
	MsgCamera* cameraMsg = (MsgCamera*)msg;

	this->proj		= cameraMsg->Proj();
	this->view		= cameraMsg->View();
	this->camPos	= cameraMsg->CameraPosition();

	delete cameraMsg;
}
void RendererGL::msgLight(Msg* msg)
{
	MsgLight* lightMsg = (MsgLight*)msg;

	Light* light = lightMsg->getLight();

	lights[curLight].pos		= light->pos;
	lights[curLight].spotPow	= light->spotPow;
	lights[curLight].dir		= light->dir;
	lights[curLight].range		= light->range;
	lights[curLight].ambient	= light->ambient;
	lights[curLight].diffuse	= light->diffuse;
	lights[curLight].specular	= light->specular;
	lights[curLight].att		= light->att;

	curLight++;

	delete lightMsg;
}
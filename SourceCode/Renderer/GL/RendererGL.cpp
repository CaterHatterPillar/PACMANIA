#include "RendererGL.h"

//FXManagementGL* RendererGL::fxManagement;
GLuint RendererGL::vertexBuffer;
GLuint RendererGL::indexBuffer;
GLuint RendererGL::shaderProgram;
GLuint RendererGL::worldViewProjFX;
MatF4 RendererGL::view;
MatF4 RendererGL::proj;
MatF4 RendererGL::trans;

RendererGL::RendererGL() : Renderer()
{
	//fxManagement	= new FXManagementGL();
	renderList		= new std::vector<GraphicsContainer*>();
}
RendererGL::~RendererGL()
{
	//if(fxManagement)
	//	delete fxManagement;

	if(renderList)
		delete renderList;
}
void RendererGL::cleanUp()
{

}

void RendererGL::init()
{
	/*Subscribe*/
	SubscriptionMsg* subscription = new SubscriptionMsg(this, RENDER);
	Singleton<ObserverDirector>::get().push(subscription);

	subscription = new SubscriptionMsg(this, CAMERA);
	Singleton<ObserverDirector>::get().push(subscription);

	/*Send initial callback-specs to GLUT*/
	MsgGlutCallback* callbackMsg = new MsgGlutCallback(renderSpec, DISPLAY_FUNC);
	Singleton<ObserverDirector>::get().push(callbackMsg);

	callbackMsg = new MsgGlutCallback(renderSpec, IDLE_FUNC);
	Singleton<ObserverDirector>::get().push(callbackMsg);

	/*VB*/
	/*Create array of desired vertices*/
	VecF3 vertices[4];
	vertices[0] = VecF3(-1.0f, -1.0f, 0.0f);
	vertices[1] = VecF3(0.0f, -1.0f, 1.0f);
	vertices[2] = VecF3(1.0f, -1.0f, 0.0f);
	vertices[3] = VecF3(0.0f, 1.0f, 0.0f);

	/*Create buffer using glGen-function*/
	glGenBuffers(1, &vertexBuffer);
	/*Specify usage of buffer*/
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer); //GL_ARRAY_BUFFER specifies that the buffer will contain an array of vertices
	/*Fill buffer with data*/
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); //contents won't be changed, so flag STATIC is specified

	/*IB*/
	unsigned int indices[] = { 
		0, 3, 1,
		1, 3, 2,
		2, 3, 0,
		0, 2, 1};

	glGenBuffers(1, &indexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	initShaders();

	/*Uniform*/
	worldViewProjFX = glGetUniformLocation(shaderProgram, "wvp");
	assert(worldViewProjFX != 0xFFFFFFFF);
}
void RendererGL::initShaders()
{
	//fxManagement->init();

	//temp
	/*Creates and OpenGL shaderprogram
	 * Purpose of which is to link shader objects to
	 */
	shaderProgram = glCreateProgram();
	if(shaderProgram == 0)
		throw 0;

	addShader(shaderProgram, VS, GL_VERTEX_SHADER);
	addShader(shaderProgram, PS, GL_FRAGMENT_SHADER);

	GLint success = 0;
	GLchar errorLog[1024] = { 0 };

	/*Links our newly created shader program, with the attached shader objects
	 *If we so wish, we may now delete our shader objects by calling glDeleteShader for both of them
	 */
	glLinkProgram(shaderProgram);

	/*Check for program errors, such as linking errors
	 *Note that these are different from shader compilation errors
	 */
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if(success == 0)
	{
		glGetProgramInfoLog(shaderProgram, sizeof(errorLog), NULL, errorLog);
		fprintf(stderr, "Error linking shader program: '%s'\n", errorLog);
		throw 0;
	}

	/*Checks whether or not the program object can execute the pipeline in it's current state*/
	glValidateProgram(shaderProgram);

	/*Checks for other errors, unrelated to linking*/
	glGetProgramiv(shaderProgram, GL_VALIDATE_STATUS, &success);
	if(!success)
	{
		glGetProgramInfoLog(shaderProgram, sizeof(errorLog), NULL, errorLog);
		fprintf(stderr, "Invalid shader program: '%s'\n", errorLog);
		throw 0;
	}

	/*Connect shader program to pipeline*/
	glUseProgram(shaderProgram);
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

/*GLUT callbacks*/
void RendererGL::renderSpec()
{
	/*Clear backbuffer*/
	glClear(GL_COLOR_BUFFER_BIT);

	/*Update transform*/
	MatF4 world;
	world.translation(0.0f, 0.0f, 5.0f);
	trans = proj * view * world;
	glUniformMatrix4fv(worldViewProjFX, 1, GL_TRUE, &trans.m[0][0]);

	/*Enable*/
	glEnableVertexAttribArray(0);	//similar to semantics in dx? attribute

	/*Set vertex buffer*/
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
	
	glutSwapBuffers();
}

//temp
void RendererGL::addShader(
	GLuint		shaderProgram, 
	const char*	shaderText, 
	GLenum		shaderType)
{
	GLuint shaderObj = glCreateShader(shaderType);
	if(shaderObj == 0)
		throw 0;

	const GLchar* p[1];
	p[0] = shaderText;
	GLint lengths[1];
	lengths[0] = strlen(shaderText);

	/*Replaces source code in shader object*/
	glShaderSource(
		shaderObj,	//Handle of shader object
		1,			//Number of elements in string and length arrays
		p,			//Array of pointers to strings containing source (shader) code
		lengths);	//Array of string lengths
	glCompileShader(shaderObj);

	/*Gets compilation status*/
	GLint success;
	glGetShaderiv(shaderObj, GL_COMPILE_STATUS, &success);
	if(!success) 
	{
		GLchar info[1024];
		glGetShaderInfoLog(shaderObj, 1024, NULL, info);
		fprintf(stderr, "Error compiling shader type %d: '%s'\n", shaderType, info);
		throw 0;
	}

	/*Links the newly compiled shader object with the shader program object*/
	glAttachShader(shaderProgram, shaderObj);
}

//void RendererGL::setShader()
//{
//	/*Get correct shader program*/
//	FXGL* fx			= fxManagement->getFX(BASIC);
//	GLuint programFX	= fx->ProgramFX();
//
//	/*Checks whether or not the program object can execute the pipeline in it's current state*/
//	glValidateProgram(programFX);
//	/*Connect shader program to pipeline*/
//	glUseProgram(programFX);
//
//	/*Connect uniforms*/
//	std::vector<UniformGL*>* uniforms = fx->Uniforms();
//	for(unsigned int i = 0; i < uniforms->size(); i++)
//	{
//		UniformGL*		uniformGL	= uniforms->at(i);
//		GLuint			handle		= uniformGL->Uniform();
//		UNIFORM_TYPE	type		= uniformGL->Type();
//
//		/*
//		if(type == MATRIX4F)
//		{
//			MatF4 world;
//			world.translation(1.0f, 1.0f, 1.0f);
//
//			MatF4 trans = world * view * proj;
//			glUniformMatrix4fv(handle, 1, GL_TRUE, &trans.m[0][0]);
//		}
//		else
//		{
//			throw 0; //temp
//		}
//		*/
//
//		GLuint uniform = glGetUniformLocation(programFX, "transform");//handle);
//		assert(uniform != 0xFFFFFFFF);
//
//		MatF4 world;
//		world.translation(0.0f, 0.0f, 5.0f);
//
//		MatF4 trans = proj * view * world;
//		glUniformMatrix4fv(uniform, 1, GL_TRUE, &trans.m[0][0]);
//	}
//}

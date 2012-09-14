////#include "OpenGL.h"
////
/////*Define static member-variables*/
////float OpenGL::screenWidth;
////float OpenGL::screenHeight;
////float OpenGL::FOV;
////float OpenGL::zNear;
////float OpenGL::zFar;
////
////GLuint OpenGL::vertexBuffer;
////GLuint OpenGL::indexBuffer;
////
////Vector3f	OpenGL::scaleInfo;
////Vector3f	OpenGL::worldInfo;
////Vector3f	OpenGL::rotateInfo;
////
////Matrix4f	OpenGL::proj;
////Matrix4f	OpenGL::world;
////Matrix4f	OpenGL::scale;
////Matrix4f	OpenGL::rotation;
////Matrix4f	OpenGL::trans;
////
////Camera*		OpenGL::camera;
////Matrix4f	OpenGL::cameraTrans;
////Matrix4f	OpenGL::cameraRot;
////
////GLuint		OpenGL::worldViewProjFX;
////
////void OpenGL::initialize(
////	int		argc,
////	char**	argv)
////{
////	initializeGLUT(argc, argv);
////	camera = new Camera(screenWidth, screenHeight); //initialize cam after GLUT
////
////	initializeBuffers();
////	initializeShaders();
////	updateMatrices();
////	initializeUniform();
////
////	glutMainLoop(); //start glut main-loop
////}
////void OpenGL::initializeGLUT(
////	int		argc,
////	char**	argv)
////{
////	/*Initialize window through GLUT*/
////	glutInit(&argc, argv);							//Initialize GLUT
////	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);	//Set double buffer-swap and back-buffer
////
////	glutInitWindowSize(screenWidth, screenHeight);	//Initialize window
////	glutInitWindowPosition(100, 100);				//...
////	glutCreateWindow("TestOpenGL");					//...
////	
////	//glutGameModeString("1920x1200@32");
////	//glutEnterGameMode();
////
////	/*Initialize GLUT-callback*/
////	glutDisplayFunc(renderSpec);	//Set render spec, this function will then be called in glut main-loop 
////	glutIdleFunc(renderSpec);		//Specifies that renderFunc will be run even though no difference in rendering
////	glutSpecialFunc(specialKeyboardSpec);
////	glutPassiveMotionFunc(mouseSpec);
////	glutKeyboardFunc(keyboardSpec);
////
////	/*Initialize GLEW,
////	* must be initialized after glut
////	*/
////	GLenum result = glewInit();
////	if (result != GLEW_OK)
////		throw 0;
////
////	glClearColor(0.0f, 0.0f, 0.0f, 0.0f); //set a colour for brevity
////}
////void OpenGL::initializeBuffers()
////{
////	initializeVertexBuffer();
////	initializeIndexBuffer();
////}
////void OpenGL::initializeVertexBuffer()
////{
////	/*Create array of desired vertices*/
////	Vector3f vertices[4];
////	vertices[0] = Vector3f(-1.0f, -1.0f, 0.0f);
////	vertices[1] = Vector3f(0.0f, -1.0f, 1.0f);
////	vertices[2] = Vector3f(1.0f, -1.0f, 0.0f);
////	vertices[3] = Vector3f(0.0f, 1.0f, 0.0f);
////
////	/*Create buffer using glGen-function*/
////	glGenBuffers(1, &vertexBuffer);
////	/*Specify usage of buffer*/
////	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer); //GL_ARRAY_BUFFER specifies that the buffer will contain an array of vertices
////	/*Fill buffer with data*/
////	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); //contents won't be changed, so flag STATIC is specified
////}
////void OpenGL::initializeIndexBuffer()
////{
////	unsigned int indices[] = { 
////		0, 3, 1,
////		1, 3, 2,
////		2, 3, 0,
////		0, 2, 1};
////
////	/*Create buffer using glGen-function*/
////	glGenBuffers(1, &indexBuffer);
////	/*Specify usage of buffer*/
////	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
////	/*Fill buffer with data*/
////	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
////}
////void OpenGL::initializeShaders()
////{
////	/*Creates and OpenGL shaderprogram
////	 * Purpose of which is to link shader objects to
////	 */
////	shaderProgram = glCreateProgram();
////	if(shaderProgram == 0)
////		throw 0;
////
////	addShader(shaderProgram, VS, GL_VERTEX_SHADER);
////	addShader(shaderProgram, PS, GL_FRAGMENT_SHADER);
////
////	GLint success = 0;
////	GLchar errorLog[1024] = { 0 };
////
////	/*Links our newly created shader program, with the attached shader objects
////	 *If we so wish, we may now delete our shader objects by calling glDeleteShader for both of them
////	 */
////	glLinkProgram(shaderProgram);
////
////	/*Check for program errors, such as linking errors
////	 *Note that these are different from shader compilation errors
////	 */
////	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
////	if(success == 0)
////	{
////		glGetProgramInfoLog(shaderProgram, sizeof(errorLog), NULL, errorLog);
////		fprintf(stderr, "Error linking shader program: '%s'\n", errorLog);
////		throw 0;
////	}
////
////	/*Checks whether or not the program object can execute the pipeline in it's current state*/
////	glValidateProgram(shaderProgram);
////
////	/*Checks for other errors, unrelated to linking*/
////	glGetProgramiv(shaderProgram, GL_VALIDATE_STATUS, &success);
////	if(!success)
////	{
////		glGetProgramInfoLog(shaderProgram, sizeof(errorLog), NULL, errorLog);
////		fprintf(stderr, "Invalid shader program: '%s'\n", errorLog);
////		throw 0;
////	}
////
////	/*Connect shader program to pipeline*/
////	glUseProgram(shaderProgram);
////}
////
////void OpenGL::updateMatrices()
////{
////	updateTranslation();
////	updateScale();
////	updateRotation();
////	updateProj();
////	updateCamera();
////
////	trans = proj * cameraRot * cameraTrans * world * rotation * scale;
////}
////void OpenGL::updateProj()
////{
////	proj.InitPersProjTransform(FOV, screenWidth, screenHeight, zNear, zFar);
////}
////void OpenGL::updateTranslation()
////{
////	world.InitTranslationTransform(worldInfo.x, worldInfo.y, worldInfo.z);
////}
////void OpenGL::updateScale()
////{
////	scale.InitScaleTransform(scaleInfo.x, scaleInfo.y, scaleInfo.z);
////}
////void OpenGL::updateRotation()
////{
////	rotation.InitRotateTransform(rotateInfo.x, rotateInfo.y, rotateInfo.z);
////}
////void OpenGL::updateCamera()
////{
////	Vector3f pos = camera->getPos();
////	cameraTrans.InitTranslationTransform(pos.x, pos.y, pos.z);
////	cameraRot.InitCameraTransform(camera->getLook(), camera->getUp());
////}
////
////void OpenGL::initializeUniform()
////{
////	/*Connects handle scaleFX to shader*/
////	worldViewProjFX = glGetUniformLocation(shaderProgram, "wvp");
////	assert(worldViewProjFX != 0xFFFFFFFF);
////}
////
////void OpenGL::addShader(
////	GLuint		shaderProgram, 
////	const char*	shaderText, 
////	GLenum		shaderType)
////{
////	GLuint shaderObj = glCreateShader(shaderType);
////	if(shaderObj == 0)
////		throw 0;
////
////	const GLchar* p[1];
////	p[0] = shaderText;
////	GLint lengths[1];
////	lengths[0] = strlen(shaderText);
////	
////	/*Replaces source code in shader object*/
////	glShaderSource(
////		shaderObj,	//Handle of shader object
////		1,			//Number of elements in string and length arrays
////		p,			//Array of pointers to strings containing source (shader) code
////		lengths);	//Array of string lengths
////	glCompileShader(shaderObj);
////	
////	/*Gets compilation status*/
////	GLint success;
////	glGetShaderiv(shaderObj, GL_COMPILE_STATUS, &success);
////	if(!success) 
////	{
////		GLchar info[1024];
////		glGetShaderInfoLog(shaderObj, 1024, NULL, info);
////		fprintf(stderr, "Error compiling shader type %d: '%s'\n", shaderType, info);
////		throw 0;
////	}
////
////	/*Links the newly compiled shader object with the shader program object*/
////	glAttachShader(shaderProgram, shaderObj);
////}
////void OpenGL::renderSpec()
////{
////	camera->update();
////
////	/*Clear backbuffer*/
////	glClear(GL_COLOR_BUFFER_BIT);
////
////	static float tempScale = 0.0f;
////	tempScale += 0.001f;
////
////	/*Update transform*/
////	setScale(sinf(tempScale * 0.1f), sinf(tempScale * 0.1f), sinf(tempScale * 0.1f));
////	setWorld(0.0f, 0.0f, 5.0f);
////	setRotation(0.0f, tempScale, 0.0f);
////	updateMatrices();
////
////	glUniformMatrix4fv(worldViewProjFX, 1, GL_TRUE, &trans.m[0][0]);
////
////	/*Enable*/
////	glEnableVertexAttribArray(0);	//similar to semantics in dx? attribute
////
////	/*Set vertex buffer*/
////	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
////	/*Specifies how buffer is to be interpreted*/
////	glVertexAttribPointer(
////		0,			//Index of attribute
////		3,			//Number of components in attribute (x, y, z)
////		GL_FLOAT,	//Data type of each component
////		GL_FALSE,	//Specifies if we want attribute to be normalized
////		0,			//Stride
////		0);			//Offset
////
////	/*Set index buffer*/
////	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
////
////	/*Draw-call using indices*/
////	glDrawElements(
////		GL_TRIANGLES,		//Type to render
////		12,					//Number of indices
////		GL_UNSIGNED_INT,	//Index-type (for size)
////		0);					//Offset
////
////	/*Disable*/
////	glDisableVertexAttribArray(0);
////
////	glutSwapBuffers();
////}
////void OpenGL::specialKeyboardSpec(int key, int x, int y)
////{
////	camera->keyboard(key);
////}
////void OpenGL::keyboardSpec(unsigned char key, int x, int y)
////{
////	switch (key) {
////	case 'q':
////		exit(0);
////	}
////}
////void OpenGL::mouseSpec(int x, int y)
////{
////	camera->mouse(x, y);
////}
////
////OpenGL::OpenGL(
////	float screenWidth,
////	float screenHeight,
////	float FOV,
////	float zNear,
////	float zFar)
////{
////	/*Desc*/
////	this->screenWidth	= screenWidth;
////	this->screenHeight	= screenHeight;
////	this->FOV	= FOV;
////	this->zNear	= zNear;
////	this->zFar	= zFar;
////
////	scaleInfo	= Vector3f(1.0f, 1.0f, 1.0f);
////	worldInfo	= Vector3f(0.0f, 0.0f, 0.0f);
////	rotateInfo	= Vector3f(0.0f, 0.0f, 0.0f);
////}
////OpenGL::~OpenGL()
////{
////
////}
////
////void OpenGL::setScale(float x, float y, float z)
////{
////	scaleInfo.x = x;
////	scaleInfo.y = y;
////	scaleInfo.z = z;
////}
////void OpenGL::setRotation(float x, float y, float z)
////{
////	rotateInfo.x = x;
////	rotateInfo.y = y;
////	rotateInfo.z = z;
////}
////void OpenGL::setWorld(float x, float y, float z)
////{
////	worldInfo.x = x;
////	worldInfo.y = y;
////	worldInfo.z = z;
////}
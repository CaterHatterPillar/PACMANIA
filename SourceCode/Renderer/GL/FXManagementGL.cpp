////#include "FXManagementGL.h"
////
////void FXManagementGL::init()
////{
////	initFXs();
////}
////void FXManagementGL::initFXs()
////{
////	createFX(BASIC);
////}
////
////void FXManagementGL::createFX(ID_FX idFX)
////{
////	GLuint programFX = createProgramFX();
////	FXGL* fx = new FXGL(idFX, programFX);
////	fx->loadUniform("transform", MATRIX4F); //tmep
////
////	fxs->push_back(fx);
////}
////GLuint FXManagementGL::createProgramFX()
////{
////	/*Creates and OpenGL shaderprogram
////	 * Purpose of which is to link shader objects to
////	 */
////	GLuint programFX = glCreateProgram();
////	if(programFX == 0)
////		throw 0;
////
////	GLuint	vertexShader	= createObjFX(VS, GL_VERTEX_SHADER);
////	GLuint	fragmentShader	= createObjFX(PS, GL_FRAGMENT_SHADER);
////
////	/*Links the newly compiled shader object with the shader program object*/
////	glAttachShader(programFX, vertexShader);
////	glAttachShader(programFX, fragmentShader);
////
////	/*Links our newly created shader program, with the attached shader objects
////	 *If we so wish, we may now delete our shader objects by calling glDeleteShader for both of them
////	 */
////	glLinkProgram(programFX);
////
////	glDeleteShader(vertexShader);
////	glDeleteShader(fragmentShader);
////
////	/*Check for program errors, such as linking errors
////	 *Note that these are different from shader compilation errors
////	 */
////	GLint success = 0;
////	GLchar errorLog[1024] = { 0 };
////	glGetProgramiv(programFX, GL_LINK_STATUS, &success);
////	if(success == 0)
////	{
////		glGetProgramInfoLog(programFX, sizeof(errorLog), NULL, errorLog);
////		fprintf(stderr, "Error linking shader program: '%s'\n", errorLog);
////		throw 0;
////	}
////
////	/*Checks for other errors, unrelated to linking*/
////	glGetProgramiv(programFX, GL_VALIDATE_STATUS, &success);
////	if(!success)
////	{
////		glGetProgramInfoLog(programFX, sizeof(errorLog), NULL, errorLog);
////		fprintf(stderr, "Invalid shader program: '%s'\n", errorLog);
////		throw 0;
////	}
////}
////GLuint FXManagementGL::createObjFX(const char*	shaderText, GLenum shaderType)
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
////	return shaderObj;
////}
////
////FXGL* FXManagementGL::getFX(ID_FX idFX)
////{
////	FXGL* fx = nullptr;
////
////	bool foundFX = false;
////	for(unsigned int i = 0; 
////		i < fxs->size() && !foundFX; 
////		i++)
////	{
////		if(fxs->at(i)->IDFX() == idFX)
////		{
////			foundFX = true;
////			fx = fxs->at(i);
////		}
////	}
////
////	return fx;
////}
////
////FXManagementGL::FXManagementGL()
////{
////	fxs = new std::vector<FXGL*>();
////}
////FXManagementGL::~FXManagementGL()
////{
////	if(fxs)
////	{
////		for(unsigned int i = 0; i < fxs->size(); i++)
////			if(fxs->at(i))
////				delete fxs;
////		delete fxs;
////	}
////}
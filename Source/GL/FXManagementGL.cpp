#include "FXManagementGL.h"

void FXManagementGL::init()
{
        initFXs();
}
void FXManagementGL::initFXs()
{
        /*Create default shader-combination*/
        createFX(
                VERTEX_SHADER_DEFAULT,
                PIXEL_SHADER_DEFAULT);
}
 
void FXManagementGL::createFX(
        ShaderId vertexShaderID,
        ShaderId fragmentShaderID)
{
        GLuint programFX = createProgramFX(
                vertexShaderID,
                fragmentShaderID);
        FXGL* fx = new FXGL(
                vertexShaderID,
                fragmentShaderID,
                programFX);
        //fx->loadUniform("wvp", MATRIX4F); //temp
        fxs->push_back(fx);
}
GLuint FXManagementGL::createProgramFX(
        ShaderId vertexShaderID,
        ShaderId fragmentShaderID)
{
        GLuint programFX = glCreateProgram();
        if(programFX == 0)
                throw 0;
 
        std::string vertexPath;
        std::string fragmentPath;
        fetchShaderPaths(
                vertexShaderID,
                vertexPath,
                fragmentShaderID,
                fragmentPath);
 
        const char* VS = file2string(vertexPath.c_str());
        const char* PS = file2string(fragmentPath.c_str());
 
        GLuint  vertexShader    = createObjFX(VS, GL_VERTEX_SHADER);
        GLuint  fragmentShader  = createObjFX(PS, GL_FRAGMENT_SHADER);
 
        delete [] VS;
        delete [] PS;

	/*Links the newly compiled shader object with the shader program object*/
	glAttachShader(programFX, vertexShader);
	glAttachShader(programFX, fragmentShader);

	glLinkProgram(programFX);

	initPerFrame(programFX);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	GLint success = 0;
	GLchar errorLog[1024] = { 0 };
	glGetProgramiv(programFX, GL_LINK_STATUS, &success);
	if(success == 0)
	{
		glGetProgramInfoLog(programFX, sizeof(errorLog), NULL, errorLog);
		fprintf(stderr, "Error linking shader program: '%s'\n", errorLog);
		throw 0;
	}

	glGetProgramiv(programFX, GL_VALIDATE_STATUS, &success);
	if(!success)
	{
		glGetProgramInfoLog(programFX, sizeof(errorLog), NULL, errorLog);
		fprintf(stderr, "Invalid shader program: '%s'\n", errorLog);
		throw 0;
	}

	return programFX;
}
void FXManagementGL::initPerFrame(GLuint programFX)
{
	GLuint blockIndex = glGetUniformBlockIndex(programFX, "PerFrame"); //Get index of uniform block
	if(blockIndex == GL_INVALID_INDEX)
	{
		throw 0;
	}
	
	GLenum error = glGetError();
	if (error != GL_NO_ERROR)
	{
		const GLubyte* readError = gluErrorString(error);
		throw 0;
	}
	
	//Allocate space for buffer
	glGetActiveUniformBlockiv(
		programFX,					//Handle to program containing uniform block
		blockIndex,					//Index of block within programFX
		GL_UNIFORM_BLOCK_DATA_SIZE,	//What to query
		&perFrameSize);				//Result
	perFrameBuffer = (GLubyte*)malloc(perFrameSize); //Temporary buffer to hold data
	
	error = glGetError();
	if (error != GL_NO_ERROR)
	{
		const GLubyte* readError = gluErrorString(error);
		throw 0;
	}
	
	//Create OpenGL buffer-object and copy the data into it
	glGenBuffers(1, &perFrameHandle);
	glBindBuffer(GL_UNIFORM_BUFFER, perFrameHandle);
	glBufferData(
		GL_UNIFORM_BUFFER,	//Specifies target type
		perFrameSize,		//Size in bytes
		NULL,				//Pointer to initialization data
		GL_DYNAMIC_DRAW);	//Usage type
	
	//Finally, bind buffer to uniform block
	glBindBufferBase(GL_UNIFORM_BUFFER, blockIndex, perFrameHandle);
}

void FXManagementGL::updatePerFrame(Light lights[], VecF3 camPos)
{
	//Place data into buffer
	memcpy(perFrameBuffer, lights,	10 * sizeof(Light));
	memcpy(perFrameBuffer + 10 * sizeof(Light), &camPos, sizeof(VecF3));

	glBufferData(
		GL_UNIFORM_BUFFER,	//Specifies target type
		perFrameSize,		//Size in bytes
		perFrameBuffer,		//Pointer to initialization data
		GL_DYNAMIC_DRAW);	//Usage type
}

void FXManagementGL::fetchShaderPaths(
	ShaderId		vs,
	std::string&	vss,
	ShaderId		fs,
	std::string&	fss)
{
	std::string path = SHADER_PATH;
	std::string shader;

	switch(vs)
	{
	case VERTEX_SHADER_DEFAULT:
		shader	= SHADER_DEFAULT_VERTEX;
		break;
	default:
		throw 0;
		break;
	}
	vss = path + shader;

	switch(fs)
	{
	case PIXEL_SHADER_DEFAULT:
		shader	= SHADER_DEFAULT_FRAGMENT;
		break;
	default:
		throw 0;
		break;
	}
	fss = path + shader;
}

GLuint FXManagementGL::createObjFX(
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

	glShaderSource(
		shaderObj,	//Handle of shader object
		1,			//Number of elements in string and length arrays
		p,			//Array of pointers to strings containing source (shader) code
		lengths);	//Array of string lengths
	glCompileShader(shaderObj);

	GLint success;
	glGetShaderiv(shaderObj, GL_COMPILE_STATUS, &success);
	if(!success) 
	{
		GLchar info[1024];
		glGetShaderInfoLog(shaderObj, 1024, NULL, info);
		fprintf(stderr, "Error compiling shader type %d: '%s'\n", shaderType, info);
		throw 0;
	}

	return shaderObj;
}

char* FXManagementGL::file2string(const char *path)
{
	FILE *fd;
	long len,
		r;
	char *str;

	if (!(fd = fopen(path, "r")))
	{
		fprintf(stderr, "Can't open file '%s' for reading\n", path);
		throw 0;
	}

	fseek(fd, 0, SEEK_END);
	len = ftell(fd);

	printf("File '%s' is %ld long\n", path, len);

	fseek(fd, 0, SEEK_SET);

	if (!(str = (char*)malloc(len * sizeof(char))))
	{
		fprintf(stderr, "Can't malloc space for '%s'\n", path);
		throw 0;
	}

	r = fread(str, sizeof(char), len, fd);

	str[r - 1] = '\0'; /* Shader sources have to term with null */

	fclose(fd);

	return str;
}

FXGL* FXManagementGL::getFX(
	ShaderId vertexShaderID,
	ShaderId fragmentShaderID)
{
	FXGL* fx = NULL;

	bool foundFX = false;
	for(unsigned int i = 0; i < fxs->size() && !foundFX; i++)
	{
		if(fxs->at(i)->VertexShader() == vertexShaderID)
		{
			if(fxs->at(i)->FragmentShader() == fragmentShaderID)
			{
				fx		= fxs->at(i);
				foundFX	= true;
			}
		}
	}

	return fx;
}

FXManagementGL::FXManagementGL()
{
	fxs = new std::vector<FXGL*>();
}
FXManagementGL::~FXManagementGL()
{
	free(perFrameBuffer);

	if(fxs)
	{
		for(unsigned int i = 0; i < fxs->size(); i++)
			if(fxs->at(i))
				delete fxs->at(i);
		delete fxs;
	}
}

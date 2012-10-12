#ifndef UNIFORMGL_H
#define UNIFORMGL_H

enum UNIFORM_TYPE
{
	MATRIX4F,
	MATRIX4F_ARR
};

class UniformGL
{
private:
	GLuint			uniform;
	UNIFORM_TYPE	type;
protected:
public:
	UniformGL(GLuint uniform, UNIFORM_TYPE type)
	{
		this->uniform	= uniform;
		this->type		= type;
	}
	~UniformGL()
	{

	}

	GLuint Uniform()	{ return uniform;	}
	UNIFORM_TYPE Type()	{ return type;		}
};

#endif //UNIFORMGL_H
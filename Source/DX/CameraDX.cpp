#include "CameraDX.h"

CameraDX::CameraDX(float aspect, float fov, float zf, float zn, float zoomedIn, float zoomedOut) : Camera(zoomedIn, zoomedOut)
{
	Aspect(aspect);
	FOV(fov);
	ZFar(zf);
	ZNear(zn);
}

CameraDX::~CameraDX()
{
}

void CameraDX::mouse(const float dX, const float dY)
{
	yaw(dX);
	pitch(dY);
}

void CameraDX::keyboard(KEY key)
{
	switch(key)
	{
	case KEY_W:
		walk(STEP_SCALE);
		break;
	case KEY_A:
		strafe(-STEP_SCALE);
		break;
	case KEY_S:
		walk(-STEP_SCALE);
		break;
	case KEY_D:
		strafe(STEP_SCALE);
		break;
	default:
		break;
	}
}

void CameraDX::updateView()
{
	look.normalize();
	
	up = look.cross(right);
	up.normalize();

	right = up.cross(look);
	right.normalize();

	float x = -position.dot(right);
	float y = -position.dot(up);
	float z = -position.dot(look);

	view.m[0][0] = right.x;
	view.m[1][0] = right.y;
	view.m[2][0] = right.z;
	view.m[3][0] = x;
	
	view.m[0][1] = up.x;
	view.m[1][1] = up.y;
	view.m[2][1] = up.z;
	view.m[3][1] = y;

	view.m[0][2] = look.x;
	view.m[1][2] = look.y;
	view.m[2][2] = look.z;
	view.m[3][2] = z;

	view.m[0][3] = 0.0f;
	view.m[1][3] = 0.0f;
	view.m[2][3] = 0.0f;
	view.m[3][3] = 1.0f;
}

void CameraDX::updateProj()
{
	MatF4 perspective;
	ZeroMemory(&perspective, sizeof(MatF4));

	perspective.m[0][0] = 1/(Aspect()*(tan(FOV()/2)));
	perspective.m[1][1] = 1/(tan(FOV()/2));
	perspective.m[2][2] = ZFar()/(ZFar() - ZNear());
	perspective.m[2][3] = 1.0f;
	perspective.m[3][2] = (-ZNear() * ZFar())/(ZFar() - ZNear());

	projection = perspective;
}

void CameraDX::strafe(const float velocity)
{
	position += right*velocity;
}

void CameraDX::walk(const float velocity)
{
	position += look*velocity;
}

void CameraDX::pitch(const float angle)
{
	up.rotate(angle, right);
	look.rotate(angle, right);
}

void CameraDX::yaw(const float angle)
{
	VecF3 axis = VecF3(0.0f, 1.0f, 0.0f);
	right.rotate(angle, axis);
	up.rotate(angle, axis);
	look.rotate(angle, axis);
}
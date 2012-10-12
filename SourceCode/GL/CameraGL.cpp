#include "CameraGL.h"

void CameraGL::updateProj()
{
	MatF4 perspective;

	float tanRadFov = tan(RADIAN(FOV() / 2.0f));
	perspective.m[0][0] = 1.0f / (Aspect()*tanRadFov);
	perspective.m[1][1] = 1.0f / (tanRadFov);
	perspective.m[2][2] = (-ZNear() - ZFar()) / (ZNear() - ZFar());
	perspective.m[2][3] = 2.0f * ZFar() * ZNear() / (ZNear() - ZFar());
	perspective.m[3][2] = 1.0f;

	projection = perspective;
}
void CameraGL::updateView()
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
	view.m[0][1] = right.y;
	view.m[0][2] = right.z;
	view.m[0][3] = x;

	view.m[1][0] = up.x;
	view.m[1][1] = up.y;
	view.m[1][2] = up.z;
	view.m[1][3] = y;

	view.m[2][0] = look.x;
	view.m[2][1] = look.y;
	view.m[2][2] = look.z;
	view.m[2][3] = z;

	view.m[3][0] = 0.0f;
	view.m[3][1] = 0.0f;
	view.m[3][2] = 0.0f;
	view.m[3][3] = 1.0f;
}

void CameraGL::init()
{
	Camera::init();
}
void CameraGL::update(double delta)
{
	Camera::update(delta);
}

void CameraGL::strafe(const float velocity)
{
	position += right * velocity;
}
void CameraGL::walk(const float velocity)
{
	position += look * velocity;
}
void CameraGL::pitch(const float angle)
{
	look.rotate(angle, right);
	look.normalize();

	up.rotate(angle, right);
	up.normalize();
}
void CameraGL::yaw(const float angle)
{
	const VecF3 vAxis(0.0f, 1.0f, 0.0f);

	look.rotate(angle, vAxis);
	look.normalize();

	up.rotate(angle, vAxis);
	up.normalize();

	right.rotate(angle, vAxis);
	right.normalize();
}

void CameraGL::keyboard(KEY key)
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
void CameraGL::mouse(const float dX, const float dY)
{
	yaw(-dX);
	pitch(-dY);
}

CameraGL::CameraGL(float fov, float aspect, float zNear, float zFar)
{
	Aspect(aspect);
	FOV(fov);
	ZFar(zFar);
	ZNear(zNear);

	position	= VecF3(0.0f, 0.0f, -10.0f);
	right		= VecF3(1.0f, 0.0f, 0.0f);
	up			= VecF3(0.0f, 1.0f, 0.0f);
	look		= VecF3(0.0f, 0.0f, 1.0f);
}
CameraGL::~CameraGL() {}
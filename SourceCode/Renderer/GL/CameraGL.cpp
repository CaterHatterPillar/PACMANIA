#include "CameraGL.h"

CameraGL::CameraGL(
	float fov, 
	float aspect, 
	float zNear, 
	float zFar,

	unsigned int screenWidth,
	unsigned int screenHeight)
{
	FOV(fov);
	Aspect(aspect);
	ZNear(zNear);
	ZFar(zFar);
	ScreenWidth(screenWidth);
	ScreenHeight(screenHeight);

	position	= VecF3(0.0f, 0.0f, 0.0f);
	look		= VecF3(0.0f, 0.0f, 1.0f);
	up			= VecF3(0.0f, 1.0f, 0.0f);
}
CameraGL::~CameraGL()
{

}

/*Calculates horizontal and vertical angle*/
void CameraGL::init()
{
	//Subscribe to msgs
	Camera::init();

	VecF3 hTarget(look.x, 0.0, look.z);
	hTarget.normalize();

	if (hTarget.z >= 0.0f)
	{
		if (hTarget.x >= 0.0f)
			angleH = 360.0f - DEGREE(asin(hTarget.z));
		else
			angleH = 180.0f + DEGREE(asin(hTarget.z));
	}
	else
	{
		if (hTarget.x >= 0.0f)
			angleH = DEGREE(asin(-hTarget.z));
		else
			angleH = 90.0f + DEGREE(asin(-hTarget.z));
	}

	angleV = -DEGREE(asin(look.y));
}

void CameraGL::keyboard(KEY key)
{
	switch(key)
	{
	case KEY_UP:
		position -= (look * STEP_SCALE);
		break;
	case KEY_DOWN:
		position += (look * STEP_SCALE);
		break;
	case KEY_LEFT:
		{
			VecF3 left = look.cross(up);
			left.normalize();
			left *= -STEP_SCALE;
			position += left;
			break;
		}
	case KEY_RIGHT:
		{
			VecF3 right = up.cross(look);
			right.normalize();
			right *= STEP_SCALE;
			position -= right;
			break;
		}
	default:
		throw 0;
		break;
	}

	//updateRotation();
}
void CameraGL::mouse(const int x, const int y)
{
	angleH = x;
	angleV = y;

	updateRotation();
}
void CameraGL::update(double delta)
{
	//Handle msgs in base class
	Camera::update(delta);
}

void CameraGL::updateProj()
{
	MatF4 perspective;
	ZeroMemory(&perspective, sizeof(MatF4));

	const float ar         = Aspect();
	const float zRange     = ZNear() - ZFar();
	const float tanHalfFOV = tanf(RADIAN(FOV() / 2.0f));

	perspective.m[0][0] = 1.0f/(tanHalfFOV * ar); perspective.m[0][1] = 0.0f;            perspective.m[0][2] = 0.0f;								perspective.m[0][3] = 0.0;
	perspective.m[1][0] = 0.0f;                   perspective.m[1][1] = 1.0f/tanHalfFOV; perspective.m[1][2] = 0.0f;								perspective.m[1][3] = 0.0;
	perspective.m[2][0] = 0.0f;                   perspective.m[2][1] = 0.0f;            perspective.m[2][2] = (-ZNear() - ZFar()) / zRange;		perspective.m[2][3] = 2.0f * ZFar() * ZNear() / zRange;
	perspective.m[3][0] = 0.0f;                   perspective.m[3][1] = 0.0f;            perspective.m[3][2] = 1.0f;								perspective.m[3][3] = 0.0;

	projection = perspective;
}
void CameraGL::updateView()
{
	MatF4 camTran;
	camTran.m[0][0] = 1.0f; camTran.m[0][1] = 0.0f; camTran.m[0][2] = 0.0f; camTran.m[0][3] = position.x;
	camTran.m[1][0] = 0.0f; camTran.m[1][1] = 1.0f; camTran.m[1][2] = 0.0f; camTran.m[1][3] = position.y;
	camTran.m[2][0] = 0.0f; camTran.m[2][1] = 0.0f; camTran.m[2][2] = 1.0f; camTran.m[2][3] = position.z;
	camTran.m[3][0] = 0.0f; camTran.m[3][1] = 0.0f; camTran.m[3][2] = 0.0f; camTran.m[3][3] = 1.0f;

	MatF4 camRot;

	VecF3 N = look;
	N.normalize();
	VecF3 U = up;
	U.normalize();
	U = U.cross(N);
	VecF3 V = N.cross(U);

	camRot.m[0][0] = U.x;   camRot.m[0][1] = U.y;   camRot.m[0][2] = U.z;   camRot.m[0][3] = 0.0f;
	camRot.m[1][0] = V.x;   camRot.m[1][1] = V.y;   camRot.m[1][2] = V.z;   camRot.m[1][3] = 0.0f;
	camRot.m[2][0] = N.x;   camRot.m[2][1] = N.y;   camRot.m[2][2] = N.z;   camRot.m[2][3] = 0.0f;
	camRot.m[3][0] = 0.0f;  camRot.m[3][1] = 0.0f;  camRot.m[3][2] = 0.0f;  camRot.m[3][3] = 1.0f;

	view = camRot * camTran;
}
void CameraGL::updateRotation()
{
	// Rotate the view vector by the horizontal angle around the vertical axis
	//VecF3 view(1.0f, 0.0f, 0.0f);
	//view.rotate(angleH, vAxis);
	//view.normalize();
	pitch(angleH);

	// Rotate the view vector by the vertical angle around the horizontal axis
	//VecF3 hAxis = vAxis.cross(view);
	//hAxis.normalize();
	//view.rotate(angleV, hAxis);
	yaw(angleV);
}

void CameraGL::pitch(const float angle)
{
	//up.rotate(angle, right);
	//look.rotate(angle, right);

	const VecF3 vAxis(0.0f, 1.0f, 0.0f);

	look = VecF3(1.0f, 0.0f, 0.0f);
	look.rotate(angle, vAxis);
	look.normalize();
}
void CameraGL::yaw(const float angle)
{
	/*right.rotate(angle, VecF3(0.0f, 1.0f, 0.0f));
	up.rotate(angle, VecF3(0.0f, 1.0f, 0.0f));
	look.rotate(angle, VecF3(0.0f, 1.0f, 0.0f));*/

	const VecF3 vAxis(0.0f, 1.0f, 0.0f);

	VecF3 hAxis = vAxis.cross(look);
	hAxis.normalize();
	look.rotate(angle, hAxis);
	look.normalize();

	up = look.cross(hAxis);
	up.normalize();
}
void CameraGL::strafe(const float velocity)
{

}
void CameraGL::walk(const float velocity)
{

}
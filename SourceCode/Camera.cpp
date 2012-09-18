#include "Camera.h"

void Camera::init()
{
	VecF3 hLook(look.x, 0.0, look.z);
	hLook.normalize();

	if (hLook.z >= 0.0f)
	{
		if (hLook.x >= 0.0f)
			angleH = 360.0f - DEGREE(asin(hLook.z));
		else
			angleH = 180.0f + DEGREE(asin(hLook.z));
	}
	else
	{
		if (hLook.x >= 0.0f)
			angleH = DEGREE(asin(-hLook.z));
		else
			angleH = 90.0f + DEGREE(asin(-hLook.z));
	}

	angleV = -DEGREE(asin(look.y));
}
void Camera::update(double delta)
{
	//if changed
	updateCamera();
}
void Camera::updateCamera()
{
	const VecF3 vAxis(0.0f, 1.0f, 0.0f);

	//Rotate the view vector by the horizontal angle around the vertical axis
	VecF3 view(1.0f, 0.0f, 0.0f);
	view.rotate(angleH, vAxis);
	view.Normalize();

	// Rotate the view vector by the vertical angle around the horizontal axis
	Vector3f hAxis = vAxis.Cross(view);
	hAxis.Normalize();
	view.Rotate(angleV, hAxis);

	look = view;
	look.Normalize();

	up = look.Cross(hAxis);
	up.Normalize();
}

Camera::Camera(
	VecF3 pos,
	VecF3 look,
	VecF3 up)
{
	this->pos	= pos;

	this->look	= look;
	this->look.normalize();

	this->up	= up;
	this->up.normalize();
}
Camera::~Camera()
{

}
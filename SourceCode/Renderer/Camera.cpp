#include "Camera.h"

Camera::Camera()
{
	position = VecF3(0.0f, 2.0f, -10.0f);
	right = VecF3(1.0f, 0.0f, 0.0f);
	up = VecF3(0.0f, 1.0f, 0.0f);
	look = VecF3(0.0f, 0.0f, 1.0f);
}

Camera::~Camera()
{
}

void Camera::init()
{
	SubscriptionMsg* subscription
		= new SubscriptionMsg(this, INPUT_MOUSE_MOVE);
	Singleton<ObserverDirector>::get().push(subscription);
	
	subscription = new SubscriptionMsg(this, INPUT_KEYBOARD_MSG);
	Singleton<ObserverDirector>::get().push(subscription);

	setLens(PI/4, (float)SCREEN_WIDTH/(float)SCREEN_HEIGHT, 1.0f, 100.0f);
}
void Camera::update(double delta)
{
	bool updateMatrices = false;

	Msg* msg = peek();
	while(msg)
	{
		msg = pop();
		if(msg)
		{
			MsgType type = msg->Type();
			switch(type)
			{
			case INPUT_MOUSE_MOVE:
				msgMouseMove(msg);
				updateMatrices = true;
				break;
			case INPUT_KEYBOARD_MSG:
				msgKeyboard(msg);
				updateMatrices = true;
				break;
			}
		}
	}

	if(updateMatrices)
	{
		rebuildView();

		MsgCamera* cameraMsg = new MsgCamera(view, projection);
		Singleton<ObserverDirector>::get().push(cameraMsg);
	}
}
void Camera::msgMouseMove(Msg* msg)
{
	MsgMouseMove* mouseMoveMsg = (MsgMouseMove*)msg;

	rotateY(mouseMoveMsg->DX());
	pitch(mouseMoveMsg->DY());

	delete mouseMoveMsg;
}
void Camera::msgKeyboard(Msg* msg)
{
	MsgKeyboard* keyboardMsg = (MsgKeyboard*)msg;

	KEY key = keyboardMsg->Key();
	switch(key)
	{
	case KEY_W:
		walk(0.01f);
		break;
	case KEY_S:
		walk(-0.01f);
		break;
	case KEY_A:
		strafe(-0.01f);
		break;
	case KEY_D:
		strafe(0.01f);
		break;
	}

	delete keyboardMsg;
}

VecF3 Camera::getPosition() const
{
	return position;
}

VecF3 Camera::getRight() const
{
	return right;
}

VecF3 Camera::getLook() const
{
	return look;
}

VecF3 Camera::getUp() const
{
	return up;
}

MatF4 Camera::getView() const
{
	return view;
}

MatF4 Camera::getProjection() const
{
	return projection;
}

void Camera::setLens(float fov, float aspect, float zn, float zf)
{
	MatF4 perspective;
	ZeroMemory(&perspective, sizeof(MatF4));

	perspective.m[0][0] = 1/(aspect * (tan(fov/2)));
	perspective.m[1][1] = 1/(tan(fov/2));
	perspective.m[2][2] = zf/(zf-zn);
	perspective.m[2][3] = 1.0f;
	perspective.m[3][2] = (-zn*zf)/(zf-zn);

	projection = perspective;
}

void Camera::strafe(float velocity)
{
	position += right*velocity;
}

void Camera::walk(float velocity)
{
	position += look*velocity;
}

void Camera::verticalWalk(float velocity)
{
	position.y += velocity;
}

void Camera::setHeight(float height)
{
	position.y = height;
}

void Camera::pitch(float angle)
{
	/*D3DXMATRIX rotation;
	D3DXMatrixRotationAxis(&rotation, &right, angle);
*/
	up.rotate(angle, right);
	look.rotate(angle, right);

	/*D3DXVec3TransformNormal(&up, &up, &rotation);
	D3DXVec3TransformNormal(&look, &look, &rotation);*/
}

void Camera::rotateY(float angle)
{
	//D3DXMATRIX rotation;
	//D3DXMatrixRotationY(&rotation, angle);

	right.rotate(angle, VecF3(0.0f, 1.0f, 0.0f));
	up.rotate(angle, VecF3(0.0f, 1.0f, 0.0f));
	look.rotate(angle, VecF3(0.0f, 1.0f, 0.0f));

	//D3DXVec3TransformNormal(&right, &right, &rotation);
	//D3DXVec3TransformNormal(&up, &up, &rotation);
	//D3DXVec3TransformNormal(&look, &look, &rotation);
}

void Camera::rebuildView()
{
	//D3DXVec3Normalize(&look, &look);
	look.normalize();

	//D3DXVec3Cross(&up, &look, &right);
	//D3DXVec3Normalize(&up, &up);

	up = look.cross(right);
	up.normalize();

	//D3DXVec3Cross(&right, &up, &look);
	//D3DXVec3Normalize(&right, &right);

	right = up.cross(look);
	right.normalize();

	float x = -position.dot(right); // -D3DXVec3Dot(&position, &right);
	float y = -position.dot(up); // -D3DXVec3Dot(&position, &up);
	float z = -position.dot(look); // -D3DXVec3Dot(&position, &look);

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
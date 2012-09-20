#include "Camera.h"

void Camera::init()
{
	/*Subscribe to input*/
	SubscriptionMsg* subscription
		= new SubscriptionMsg(this, INPUT_MOUSE_MOVE);
	Singleton<ObserverDirector>::get().push(subscription);

	subscription = new SubscriptionMsg(this, INPUT_MOUSE_CLICK);
	Singleton<ObserverDirector>::get().push(subscription);
	
	subscription = new SubscriptionMsg(this, INPUT_KEYBOARD_MSG);
	Singleton<ObserverDirector>::get().push(subscription);

	VecF3 hLook(look.x, 0.0, look.z);
	hLook.normalize();

	if (hLook.z >= 0.0f)
	{
		if (hLook.x >= 0.0f)
			angleH = 360.0f - (float)DEGREE(asin(hLook.z));
		else
			angleH = 180.0f + (float)DEGREE(asin(hLook.z));
	}
	else
	{
		if (hLook.x >= 0.0f)
			angleH = (float)DEGREE(asin(-hLook.z));
		else
			angleH = 90.0f + (float)DEGREE(asin(-hLook.z));
	}

	angleV = -(float)DEGREE(asin(look.y));

	onUpperEdge = false;
	onLowerEdge = false;
	onLeftEdge  = false;
	onRightEdge = false;
	mousePos.x  = SCREEN_WIDTH / 2;
	mousePos.y  = SCREEN_HEIGHT / 2;

	MsgGlut* glutMsg = new MsgGlut(
		WARP_POINTER, 
		(int)mousePos.x, 
		(int)mousePos.y);
	Singleton<ObserverDirector>::get().push(glutMsg);
}
void Camera::update(double delta)
{
	MsgMouseMove*	mouseMoveMsg;
	MsgMouseClick*	mouseClickMsg;
	MsgKeyboard*	keyboardMsg;

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
				mouseMoveMsg = (MsgMouseMove*)msg;
				inputMouseMove(mouseMoveMsg);
				break;
			case INPUT_MOUSE_CLICK:
				mouseClickMsg = (MsgMouseClick*)msg;
				inputMouseClick(mouseClickMsg);
				break;
			case INPUT_KEYBOARD_MSG:
				keyboardMsg = (MsgKeyboard*)msg;
				inputKeyboard(keyboardMsg);
				break;
			default:
				throw 0; //temp
				break;
			}
		}
	}

	bool shouldUpdate = false;
	if(onLeftEdge)
	{
		angleH -= 0.1f;
		shouldUpdate = true;
	}
	else if(onRightEdge)
	{
		angleH += 0.1f;
		shouldUpdate = true;
	}

	if(onUpperEdge)
	{
		if(angleV > -90.0f)
		{
			angleV -= 0.1f;
			shouldUpdate = true;
		}
	}
	else if(onLowerEdge) 
	{
		if(angleV < 90.0f) 
		{
			angleV += 0.1f;
			shouldUpdate = true;
		}
	}

	if(shouldUpdate)
		updateCamera();
}
void Camera::inputMouseMove(MsgMouseMove* msg)
{
	const int deltaX = (int)(msg->DX() - mousePos.x);
	const int deltaY = (int)(msg->DY() - mousePos.y);

	mousePos.x = mousePos.x;
	mousePos.y = mousePos.y;

	angleH += (float)deltaX / 20.0f;
	angleV += (float)deltaY / 20.0f;

	if (deltaX == 0) 
	{
		if (mousePos.x <= MARGIN)
			onLeftEdge = true;
		else if(mousePos.x >= (SCREEN_WIDTH - MARGIN)) 
			onRightEdge = true;
	}
	else
	{
		onLeftEdge = false;
		onRightEdge = false;
	}

	if (deltaY == 0)
	{
		if (mousePos.y <= MARGIN)
			onUpperEdge = true;
		else if(mousePos.y >= (SCREEN_HEIGHT - MARGIN))
			onLowerEdge = true;
	}
	else
	{
		onUpperEdge = false;
		onLowerEdge = false;
	}

	delete msg;
	updateCamera();
}
void Camera::inputMouseClick(MsgMouseClick* msg)
{
	delete msg;
}
void Camera::inputKeyboard(MsgKeyboard* msg)
{
	KEY key = msg->Key();
	switch(key)
	{
	case UP:
		keyW();
		break;
	case DOWN:
		keyS();
		break;
	case LEFT:
		keyA();
		break;
	case RIGHT:
		keyD();
		break;
	}

	delete msg;
	updateCamera();
}

void Camera::keyW()
{
	pos += (look * STEP_SCALE);
}
void Camera::keyS()
{
	pos -= (look * STEP_SCALE);
}
void Camera::keyA()
{
	VecF3 left = look.cross(up);
	left.normalize();
	left *= STEP_SCALE;
	pos += left;
}
void Camera::keyD()
{
	VecF3 right = up.cross(look);
	right.normalize();
	right *= STEP_SCALE;
	pos += right;
}

void Camera::updateCamera()
{
	const VecF3 vAxis(0.0f, 1.0f, 0.0f);

	//Rotate the view vector by the horizontal angle around the vertical axis
	VecF3 look(1.0f, 0.0f, 0.0f);
	look.rotate(angleH, vAxis);
	look.normalize();

	// Rotate the view vector by the vertical angle around the horizontal axis
	VecF3 hAxis = vAxis.cross(look);
	hAxis.normalize();
	look.rotate(angleV, hAxis);

	this->look = look;
	this->look.normalize();

	up = look.cross(hAxis);
	up.normalize();

	/*Get updated matrices*/
	MatF4 view = getView();
	MatF4 proj = getProj();
	
	/*Send updated matrices*/
	MsgCamera* cameraMsg = new MsgCamera(view, proj);
	Singleton<ObserverDirector>::get().push(cameraMsg);
}

MatF4 Camera::getView()
{
	/*Camera translation*/
	MatF4 camTrans;
	camTrans.translation(pos.x, pos.y, pos.z);
	
	/*Camera rotation*/
	VecF3 n = look;
	n.normalize();

	VecF3 u = up;
	u.normalize();

	u = u.cross(n);
	VecF3 v = n.cross(u);

	MatF4 camRot;
	camRot.m[0][0] = u.x;	camRot.m[0][1] = u.y;	camRot.m[0][2] = u.z;	camRot.m[0][3] = 0.0f;
	camRot.m[1][0] = v.x;	camRot.m[1][1] = v.y;	camRot.m[1][2] = v.z;	camRot.m[1][3] = 0.0f;
	camRot.m[2][0] = n.x;	camRot.m[2][1] = n.y;	camRot.m[2][2] = n.z;	camRot.m[2][3] = 0.0f;
	camRot.m[3][0] = 0.0f;	camRot.m[3][1] = 0.0f;	camRot.m[3][2] = 0.0f;	camRot.m[3][3] = 1.0f;

	MatF4 view = camRot * camTrans;
	return view;
}
MatF4 Camera::getProj()
{
	const float ar         = SCREEN_WIDTH / SCREEN_HEIGHT;
	const float zRange     = Z_NEAR - Z_FAR;
	const float tanHalfFOV = tanf((float)RADIAN(F_O_V / 2.0f));

	MatF4 proj;
	proj.m[0][0] = 1.0f/(tanHalfFOV * ar); proj.m[0][1] = 0.0f;					proj.m[0][2] = 0.0f;						proj.m[0][3] = 0.0;
	proj.m[1][0] = 0.0f;                   proj.m[1][1] = 1.0f / tanHalfFOV;	proj.m[1][2] = 0.0f;						proj.m[1][3] = 0.0;
	proj.m[2][0] = 0.0f;                   proj.m[2][1] = 0.0f;					proj.m[2][2] = (-Z_NEAR - Z_FAR) / zRange;	proj.m[2][3] = 2.0f * Z_FAR * Z_NEAR / zRange;
	proj.m[3][0] = 0.0f;                   proj.m[3][1] = 0.0f;					proj.m[3][2] = 1.0f;						proj.m[3][3] = 0.0;
	return proj;
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
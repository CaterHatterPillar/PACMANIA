#include "Camera.h"

Camera::Camera(float zoomedIn, float zoomedOut)
{
	zoomingIn = false;
	zoomingOut = false;

	this->zoomedIn = zoomedIn;
	this->zoomedOut = zoomedOut;

	position	= VecF3(0.0f, 0.0f, zoomedOut);
	right		= VecF3(1.0f, 0.0f, 0.0f);
	up			= VecF3(0.0f, 1.0f, 0.0f);
	look		= VecF3(0.0f, 0.0f, 1.0f);
}
Camera::~Camera()
{
}

void Camera::init()
{
	//Subscribe to mouse movement
	SubscriptionMsg* subscription = new SubscriptionMsg(this, INPUT_MOUSE_MOVE);
	Singleton<ObserverDirector>::get().push(subscription);

	//Subscribe to keyboard input
	subscription = new SubscriptionMsg(this, INPUT_KEYBOARD_MSG);
	Singleton<ObserverDirector>::get().push(subscription);

	//Subscribe to game state
	subscription = new SubscriptionMsg(this, ENTITY_PLAYER_POS);
	Singleton<ObserverDirector>::get().push(subscription);

	//Subscribe to zoom
	subscription = new SubscriptionMsg(this, ZOOM);
	Singleton<ObserverDirector>::get().push(subscription);
}
void Camera::update(double delta)
{
	STEP_SCALE = 1.0f;
	bool updateMatrices = false;

	if(zoomingIn)
		zoomIn();
	if(zoomingOut)
		zoomOut();

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
			case ENTITY_PLAYER_POS:
				msgEntityPlayerPos(msg);
				updateMatrices = true;
				break;
			case ZOOM:
				msgZoom(msg);
				updateMatrices = true;
				break;
			}
		}
	}

	if(updateMatrices)
	{
		updateProj();
		updateView();

		//Send new matrices
		MsgCamera* cameraMsg = new MsgCamera(view, projection, position);
		Singleton<ObserverDirector>::get().push(cameraMsg);
	}
}

void Camera::zoomIn()
{
	position.z = lerp(position.z, zoomedIn, lerpFac);
	if(position.z >= zoomedIn - lerpFac)
		zoomingIn = false;
}
void Camera::zoomOut()
{
	position.z = lerp(position.z, zoomedOut, lerpFac);
	if(position.z <= zoomedOut + lerpFac)
		zoomingOut = false;
}

void Camera::msgMouseMove(Msg* msg)
{
	MsgMouseMove* mouseMoveMsg = (MsgMouseMove*)msg;
	//mouse(
	//	(float)mouseMoveMsg->DX(),
	//	(float)mouseMoveMsg->DY());
	delete mouseMoveMsg;
}
void Camera::msgKeyboard(Msg* msg)
{
	MsgKeyboard* keyboardMsg = (MsgKeyboard*)msg;
	keyboard(keyboardMsg->Key());
	delete keyboardMsg;
}
void Camera::msgEntityPlayerPos(Msg* msg)
{
	MsgEntityPlayerPos* childMsg = (MsgEntityPlayerPos*)msg;
	
	// Use LERP-to smooth out camera movement
	VecF3 goalPos(childMsg->pos);
	goalPos.z = position.z;

	lerpCameraTransition(&goalPos);
	delete childMsg;
}
void Camera::msgZoom(Msg* msg)
{
	MsgZoom* zoomMsg = (MsgZoom*)msg;
	ZoomState state = zoomMsg->getState();

	position.x = zoomMsg->getX();
	position.y = zoomMsg->getY();
	
	if(state == STATE_ZOOM_IN)
	{
		zoomingIn = true;
		zoomingOut = false;
	}
	if(state == STATE_ZOOM_OUT)
	{
		zoomingOut = true;
		zoomingIn = false;
	}

	delete zoomMsg;
}
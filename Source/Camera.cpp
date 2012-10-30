#include "Camera.h"

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
}
void Camera::update(double delta)
{
	STEP_SCALE = 1.0f;
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
			case ENTITY_PLAYER_POS:
				msgEntityPlayerPos(msg);
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

void Camera::msgMouseMove(Msg* msg)
{
	MsgMouseMove* mouseMoveMsg = (MsgMouseMove*)msg;
	mouse(
		mouseMoveMsg->DX(),
		mouseMoveMsg->DY());
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
	delete msg;
}
#ifndef CAMERA_H
#define CAMERA_H

#include "Common.h"
#include "Component.h"
#include "Singleton.h"
#include "Math/PacMath.h"

#include "Messaging/ObserverDirector.h"
#include "Messaging/SubscriptionMsg.h"
#include "Messaging/MsgMouseClick.h"
#include "Messaging/MsgMouseMove.h"
#include "Messaging/MsgKeyboard.h"
#include "Messaging/MsgCamera.h"

const static float STEP_SCALE = 0.1f;
const static int MARGIN = 10;

class Camera : public Component
{
private:
	float angleH;
	float angleV;

	VecF3 pos;
	VecF3 look;
	VecF3 up;

	/*Mouse movement*/
	VecF2 mousePos;
	bool onUpperEdge;
	bool onLowerEdge;
	bool onLeftEdge;
	bool onRightEdge;

	void updateCamera();
	void inputMouseMove(MsgMouseMove* msg);
	void inputMouseClick(MsgMouseClick* msg);
	void inputKeyboard(MsgKeyboard* msg);

	void keyW();
	void keyS();
	void keyA();
	void keyD();

	MatF4 getView();
	MatF4 getProj();
protected:
public:
	void init();
	void update(double delta);

	Camera(
		VecF3 pos,
		VecF3 look,
		VecF3 up);
	virtual ~Camera();
};

#endif //CAMERA_H
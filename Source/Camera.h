#ifndef CAMERA_H
#define CAMERA_H

#include "Math/PacMath.h"

#include "Common.h"
#include "Component.h"
#include "Singleton.h"

#include "Messaging/ObserverDirector.h"
#include "Messaging/MsgMouseMove.h"
#include "Messaging/MsgKeyboard.h"
#include "Messaging/MsgCamera.h"
#include "Messaging/MsgZoom.h"

static const float lerpFac = 3.0f;

class Camera : public Component
{
private:
	float fov;
	float aspect; 
	float zNear; 
	float zFar;

	unsigned int screenWidth;
	unsigned int screenHeight;

	bool zoomingIn;
	float zoomedIn;
	bool zoomingOut;
	float zoomedOut;
	VecF3 lerpTarget;

	void zoomIn(double delta);
	void zoomOut(double delta);
	void msgZoom(Msg* msg);
protected:
	// Makes a smooth camera transition between this position and a goal position
	// anyone with better name suggestions?
	virtual void lerpCameraTransition(double delta)
	{
		position.lerp(&lerpTarget, 2.5f*delta);
		//position.lerp(&lerpTarget, 0.02f);
	}

	float STEP_SCALE;
	VecF3 position;
	VecF3 right;
	VecF3 up;
	VecF3 look;

	MatF4 view;
	MatF4 projection;

	virtual void updateProj() = 0;
	virtual void updateView() = 0;

	void msgMouseMove(Msg* msg);
	virtual void mouse(const float dX, const float dY)	= 0;

	void msgKeyboard(Msg* msg);
	virtual void keyboard(KEY key)		= 0;

	void msgEntityPlayerPos(Msg* _msg);


	virtual void strafe(const float velocity)	= 0;
	virtual void walk(const float velocity)		= 0;
	virtual void pitch(const float angle)		= 0;
	virtual void yaw(const float angle)			= 0;

	//Protected gets
	const float FOV()		{ return fov;		}
	const float Aspect()	{ return aspect;	}
	const float ZNear()		{ return zNear;		}
	const float ZFar()		{ return zFar;		}
	const unsigned int ScreenWidth()	{ return screenWidth;	}
	const unsigned int ScreenHeight()	{ return screenHeight;	}

	//Protected sets
	void FOV(const float fov)		{ this->fov		= fov;		}
	void Aspect(const float aspect)	{ this->aspect	= aspect;	}
	void ZNear(const float zNear)	{ this->zNear	= zNear;	}
	void ZFar(const float zFar)		{ this->zFar	= zFar;		}
	void ScreenWidth(const unsigned int screenWidth)	{ this->screenWidth = screenWidth;		}
	void ScreenHeight(const unsigned int screenHeight)	{ this->screenHeight = screenHeight;	}
public:
	Camera(float zoomedIn, float zoomedOut);
	~Camera();

	virtual void init();
	virtual void update(double delta);
};

//void verticalWalk(float velocity);
//void setHeight(float height);

#endif //CAMERA_H
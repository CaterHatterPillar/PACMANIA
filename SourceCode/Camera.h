#ifndef CAMERA_H
#define CAMERA_H

#include "Common.h"
#include "Component.h"
#include "Math/PacMath.h"

class Camera : public Component
{
private:
	float angleH;
	float angleV;

	VecF3 pos;
	VecF3 look;
	VecF3 up;

	void updateCamera();
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
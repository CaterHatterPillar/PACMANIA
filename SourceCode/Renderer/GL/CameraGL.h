#ifndef CAMERAGL_H
#define CAMERAGL_H

#include "CommonGL.h"
#include "../Camera.h"
#include "../../Math/PacMath.h"

class CameraGL : public Camera
{
private:
	float angleH;
	float angleV;

	void updateProj();
	void updateView();
	void updateRotation();
protected:
public:
	CameraGL(
		float fov, 
		float aspect, 
		float zNear, 
		float zFar,

		unsigned int screenWidth,
		unsigned int screenHeight);
	~CameraGL();

	void init();
	void update(double delta);

	void keyboard(KEY key);
	void mouse(const int x, const int y);

	void pitch(const float angle);
	void yaw(const float angle);
	void strafe(const float velocity);
	void walk(const float velocity);
};

#endif //CAMERAGL_H
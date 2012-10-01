#ifndef MSGCAMERA_H
#define MSGCAMERA_H

#include "Msg.h"
#include "../Math/PacMath.h"

class MsgCamera : public Msg
{
private:
	MatF4 view;
	MatF4 proj;
protected:
public:
	MsgCamera(MatF4 view, MatF4 proj) : Msg(CAMERA)
	{
		this->view = view;
		this->proj = proj;
	}
	MsgCamera(MsgCamera* msgCamera) : Msg(CAMERA)
	{
		view = msgCamera->View();
		proj = msgCamera->Proj();
	}
	virtual ~MsgCamera() {}

	MatF4 View() { return view; }
	MatF4 Proj() { return proj; }
};

#endif //MSGCAMERA_H
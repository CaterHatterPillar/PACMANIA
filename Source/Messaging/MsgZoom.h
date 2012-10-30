#ifndef MSGZOOM_H
#define MSGZOOM_H

#include "Msg.h"

enum ZoomState { STATE_ZOOM_IN, STATE_ZOOM_OUT };

class MsgZoom : public Msg
{
private:
	float x;
	float y;
	ZoomState state;
protected:
public:
	MsgZoom(float x, float y, ZoomState state) : Msg(ZOOM)
	{
		this->x = x;
		this->y = y;
		this->state = state;
	}
	MsgZoom(MsgZoom* zoomMsg) : Msg(ZOOM)
	{
		x = zoomMsg->getX();
		y = zoomMsg->getY();
		state = zoomMsg->getState();
	}
	virtual ~MsgZoom()
	{
	}

	float getX() { return x; }
	float getY() { return y; }
	ZoomState getState() { return state; }
};

#endif //MSGZOOM_H
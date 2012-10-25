#ifndef MSGLIGHT_H
#define MSGLIGHT_H

#include "../Light.h"

class MsgLight : public Msg
{
private:
	Light* light;
protected:
public:
	MsgLight(Light* light) : Msg(LIGHT)
	{
		this->light = light;
	}

	MsgLight(MsgLight* msg) : Msg(LIGHT)
	{
		this->light = msg->getLight();
	}

	virtual ~MsgLight() {}

	Light* getLight() { return light; }
};

#endif  //MSGLIGHT_H
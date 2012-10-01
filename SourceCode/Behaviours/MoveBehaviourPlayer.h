#ifndef MOVEBEHAVIOURPLAYER_H
#define MOVEBEHAVIOURPLAYER_H

#include "MoveBehaviour.h"
#include "../Messaging/MsgKeyboard.h"

class MoveBehaviourPlayer : public MoveBehaviour
{
private:
	void keyboard(KEY key);
protected:
public:
	MoveBehaviourPlayer();
	virtual ~MoveBehaviourPlayer();

	virtual void init();
	virtual void update(double delta);

	void msgKeyboard(Msg* msg);
};

#endif //MOVEBEHAVIORPLAYER_H
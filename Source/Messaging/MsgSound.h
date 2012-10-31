#ifndef MSGSOUND_H
#define MSGSOUND_H

#include "../SoundEffect.h"

class MsgSound : public Msg
{
private:
	SoundEffect effect;
	bool loop;
protected:
public:
	MsgSound(SoundEffect effect) : Msg(SOUND)
	{
		this->effect = effect;
	}

	MsgSound(MsgSound* msgSound) : Msg(SOUND)
	{
		effect = msgSound->getSoundEffect();
	}

	virtual ~MsgSound()
	{
	}

	SoundEffect getSoundEffect()
	{
		return effect;
	}
};

#endif //MSGSOUND_H
#ifndef MSGSOUNDVOLUME_H
#define MSGSOUNDVOLUME_H

#include "Msg.h"
#include "../SoundEffect.h"

class MsgSoundVolume : public Msg
{
private:
	SoundEffect effect;
	float volume;
protected:
public:
	MsgSoundVolume(SoundEffect effect, float volume) : Msg(SOUND_VOLUME)
	{
		this->effect = effect;
		this->volume = volume;
	}

	MsgSoundVolume(MsgSoundVolume* msgSoundVolume) : Msg(SOUND_VOLUME)
	{
		effect = msgSoundVolume->getSoundEffect();
		volume = msgSoundVolume->getVolume();
	}

	virtual ~MsgSoundVolume()
	{
	}

	SoundEffect getSoundEffect()
	{
		return effect;
	}

	float getVolume()
	{
		return volume;
	}
};

#endif //MSGSOUNDVOLUME_H
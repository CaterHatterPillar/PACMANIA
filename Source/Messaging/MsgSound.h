#ifndef MSGSOUND_H
#define MSGSOUND_H

enum SoundEffect
{
	SOUND_AMBIENT,
	SOUND_DEATH
};

class MsgSound : public Msg
{
private:
	SoundEffect effect;
	bool loop;
protected:
public:
	MsgSound(SoundEffect effect, bool loop) : Msg(SOUND)
	{
		this->effect = effect;
		this->loop = loop;
	}

	MsgSound(MsgSound* msgSound) : Msg(SOUND)
	{
		effect = msgSound->getSoundEffect();
		loop = msgSound->getLoop();
	}

	virtual ~MsgSound()
	{
	}

	SoundEffect getSoundEffect()
	{
		return effect;
	}

	bool getLoop()
	{
		return loop;
	}
};

#endif //MSGSOUND_H
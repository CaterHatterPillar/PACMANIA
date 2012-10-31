#ifndef SOUNDENGINE_H
#define SOUNDENGINE_H

#include <fmod.hpp>
#include <fmod.h>
#include <fmod_errors.h>
#include <fmod_codec.h>
#include <fmod_dsp.h>
#include <fmod_memoryinfo.h>
#include <fmod_output.h>

#include <stdio.h>

#include "Component.h"

#include "Singleton.h"
#include "Messaging/ObserverDirector.h"
#include "Messaging/MsgSound.h"
#include "Messaging/MsgSoundVolume.h"

class SoundEngine : public Component
{
private:
	FMOD::System*		system;
	FMOD_RESULT			result;
	unsigned int		version;
	int					numDrivers;
	FMOD_SPEAKERMODE	speakerMode;
	FMOD_CAPS			caps;
	char				name[256];

	FMOD::Sound*		soundAmbient;
	FMOD::Sound*		soundGhost;
	FMOD::Sound*		soundDeath;
	FMOD::Sound*		soundEatPill;
	FMOD::Sound*		soundConsume;
	
	FMOD::Channel*		channelAmbient;
	FMOD::Channel*		channelGhost;
	FMOD::Channel*		channelDeath;
	FMOD::Channel*		channelEatPill;
	FMOD::Channel*		channelConsume;
	



	void ERRCHECK(FMOD_RESULT result);
	void windowsInit();
	
	void loadSounds();

	void msgSound(Msg* msg);
	void msgSoundVolume(Msg* msg);
protected:
public:
	SoundEngine();
	virtual ~SoundEngine();

	void playSound();

	virtual void init();
	virtual void update(double delta);
};


#endif //SOUNDENGINE_H
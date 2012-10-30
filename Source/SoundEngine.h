#ifndef SOUND_H
#define SOUND_H

#include <fmod.hpp>
#include <fmod.h>
#include <fmod_errors.h>
#include <fmod_codec.h>
#include <fmod_dsp.h>
#include <fmod_memoryinfo.h>
#include <fmod_output.h>

#include <stdio.h>

#include "Component.h"

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

	FMOD::Sound*		sound;
	FMOD::Channel*		channel;

	void ERRCHECK(FMOD_RESULT result);
	void windowsInit();
	void loadSounds();
protected:
public:
	SoundEngine();
	virtual ~SoundEngine();

	void playSound();

	virtual void init();
	virtual void update(double delta);
};


#endif //SOUND_H
#include "SoundEngine.h"

SoundEngine::SoundEngine()
{
	system	= NULL;
	sound	= NULL;
	channel = NULL;
}

SoundEngine::~SoundEngine()
{
	if(system)
		delete system;
	if(sound)
		delete sound;
	if(channel)
		delete channel;
}

void SoundEngine::ERRCHECK(FMOD_RESULT result)
{
	if(result != FMOD_OK)
	{
		printf("FMOD Error!  (%d) %s\n", result, FMOD_ErrorString(result));
		throw 0;
	}
}

void SoundEngine::windowsInit()
{
	result = FMOD::System_Create(&system);
	ERRCHECK(result);

	result = system->setSpeakerMode(FMOD_SPEAKERMODE_STEREO);
	ERRCHECK(result);

	result = system->setSoftwareChannels(100);
	ERRCHECK(result);

	result = system->setHardwareChannels(32);
	ERRCHECK(result);

	result = system->init(200, FMOD_INIT_NORMAL, 0);
	ERRCHECK(result);
}

void SoundEngine::loadSounds()
{
	int flags = FMOD_LOOP_NORMAL | FMOD_2D | FMOD_HARDWARE;

	result = system->createSound("../../Sounds/Ambient_Storm.mp3", flags, 0, &sound);
	ERRCHECK(result);
}

void SoundEngine::playSound()
{
	result = system->playSound(FMOD_CHANNEL_FREE, sound, false, &channel);
}

void SoundEngine::init()
{
	windowsInit();
	loadSounds();
}

void SoundEngine::update(double delta)
{
}
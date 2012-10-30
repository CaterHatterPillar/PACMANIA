#include "SoundEngine.h"

SoundEngine::SoundEngine()
{
	system			= NULL;
	soundAmbient	= NULL;
	channelAmbient	= NULL;
}

SoundEngine::~SoundEngine()
{
	if(system)
		delete system;
	if(soundAmbient)
		delete soundAmbient;
	if(channelAmbient)
		delete channelAmbient;
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

	result = system->createSound("../../Sounds/Ambient_Storm.mp3", flags, 0, &soundAmbient);
	ERRCHECK(result);
}

void SoundEngine::msgSound(Msg* msg)
{
	MsgSound* msgSound = (MsgSound*)msg;
	SoundEffect effect = msgSound->getSoundEffect();
	bool loop = msgSound->getLoop();

	switch(effect)
	{
	case SOUND_AMBIENT:
		system->playSound(FMOD_CHANNEL_FREE, soundAmbient, false, &channelAmbient);
		break;
	case SOUND_DEATH:
		break;
	default:
		break;
	}
}

void SoundEngine::playSound()
{
	result = system->playSound(FMOD_CHANNEL_FREE, soundAmbient, false, &channelAmbient);
}

void SoundEngine::init()
{
	SubscriptionMsg* msg = new SubscriptionMsg(this, SOUND);
	Singleton<ObserverDirector>::get().push(msg);

	windowsInit();
	loadSounds();
}

void SoundEngine::update(double delta)
{
	Msg* msg = peek();
	while(msg)
	{
		msg = pop();
		if(msg)
		{
			MsgType type = msg->Type();
			switch(type)
			{
			case SOUND:
				msgSound(msg);
				break;
			default:
				break;
			}
		}
	}
}
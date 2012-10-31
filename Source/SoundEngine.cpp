#include "SoundEngine.h"

SoundEngine::SoundEngine()
{
	system			= NULL;
	soundAmbient	= NULL;
	soundGhost		= NULL;
	soundDeath		= NULL;
	soundEatPill	= NULL;
	soundConsume	= NULL;
	
	channelAmbient	= NULL;
	channelGhost	= NULL;
	channelDeath	= NULL;
	channelEatPill	= NULL;
	channelConsume	= NULL;
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

	result = system->createSound("../../Sounds/AMBIENT.mp3", flags, 0, &soundAmbient);
	ERRCHECK(result);

	result = system->createSound("../../Sounds/GHOST.mp3", flags, 0, &soundGhost);
	ERRCHECK(result);

	result = system->createSound("../../Sounds/CONSUME.mp3", flags, 0, &soundConsume);
	ERRCHECK(result);


	flags = FMOD_LOOP_OFF | FMOD_2D | FMOD_HARDWARE;

	result = system->createSound("../../Sounds/DEATH.mp3", flags, 0, &soundDeath);
	ERRCHECK(result);

	result = system->createSound("../../Sounds/EAT_PILL.mp3", flags, 0, &soundEatPill);
	ERRCHECK(result);
}

void SoundEngine::msgSound(Msg* msg)
{
	MsgSound* msgSound = (MsgSound*)msg;
	SoundEffect effect = msgSound->getSoundEffect();
	

	switch(effect)
	{
	case SOUND_AMBIENT:
		system->playSound(FMOD_CHANNEL_FREE, soundAmbient, false, &channelAmbient);
		break;
	case SOUND_GHOST:
		system->playSound(FMOD_CHANNEL_FREE, soundGhost, false, &channelGhost);
		break;
	case SOUND_DEATH:
		system->playSound(FMOD_CHANNEL_FREE, soundDeath, false, &channelDeath);
		break;
	case SOUND_EAT_PILL:
		result = system->playSound(FMOD_CHANNEL_FREE, soundEatPill, false, &channelEatPill);
		channelEatPill->setVolume(0.1f);
		break;
	case SOUND_CONSUME:
		system->playSound(FMOD_CHANNEL_FREE, soundConsume, false, &channelConsume);
		break;
	default:
		break;
	}

	delete msgSound;
}

void SoundEngine::msgSoundVolume(Msg* msg)
{
	MsgSoundVolume* msgSoundVolume = (MsgSoundVolume*)msg;
	SoundEffect effect = msgSoundVolume->getSoundEffect();
	float volume = msgSoundVolume->getVolume();

	switch(effect)
	{
	case SOUND_AMBIENT:
		if(channelAmbient)
			channelAmbient->setVolume(volume);
		break;
	case SOUND_GHOST:
		if(channelGhost)
			channelGhost->setVolume(volume);
		break;
	case SOUND_DEATH:
		if(channelDeath)
			channelDeath->setVolume(volume);
		break;
	case SOUND_EAT_PILL:
		if(channelEatPill)
			channelEatPill->setVolume(volume);
		break;
	case SOUND_CONSUME:
		if(channelConsume)
			channelConsume->setVolume(volume);
		break;
	default:
		break;
	}

	delete msgSoundVolume;
}

void SoundEngine::playSound()
{
	result = system->playSound(FMOD_CHANNEL_FREE, soundAmbient, false, &channelAmbient);
}

void SoundEngine::init()
{
	SubscriptionMsg* msg = new SubscriptionMsg(this, SOUND);
	Singleton<ObserverDirector>::get().push(msg);

	msg = new SubscriptionMsg(this, SOUND_VOLUME);
	Singleton<ObserverDirector>::get().push(msg);



	windowsInit();
	loadSounds();
}

void SoundEngine::update(double delta)
{
	system->update();

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
			case SOUND_VOLUME:
				msgSoundVolume(msg);
			default:
				break;
			}
		}
	}
}
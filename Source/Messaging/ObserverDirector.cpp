#include "ObserverDirector.h"

void ObserverDirector::init()
{
}
void ObserverDirector::update(double delta)
{
	while(peek())
	{
		Msg* msg = pop();

		MsgType type = msg->Type();
		switch(type)
		{
		case SUBSCRIBE:
			subscribeMsg(msg);
			break;
		case MSG_GLUT:
			msgGlut(msg);
			break;
		case MSG_GLUT_CALLBACK:
			msgGlutCallback(msg);
			break;
		case RENDER:
			msgRender(msg);
			break;
		case INPUT_MOUSE_MOVE:
			msgMouseMove(msg);
			break;
		case INPUT_MOUSE_CLICK:
			msgMouseClick(msg);
			break;
		case INPUT_KEYBOARD_MSG:
			msgKeyboard(msg);
			break;
		case CAMERA:
			msgCamera(msg);
			break;
		case DX_WINDOW_HANDLE:
			msgDXWindowHandle(msg);
			break;

		// Entity messages
		case ENTITY_PLAYER_POS:
			msgEntityPlayerPos(msg);
			break;
		case ENTITY_PACMAN_POS:
			msgEntityPacmanPos(msg);
			break;
		case ENTITY_GHOST_POS:
			msgEntityGhostPos(msg);
			break;
		case ENTITY_PILL_POS:
			msgEntityPillPos(msg);
			break;

		case ENTITY_GHOST_SPAWN:
			msgEntityGhostSpawn(msg);
			break;
		case ENTITY_PILL_EATEN:
			msgEntityPillEaten(msg);
			break;
		case ENTITY_PILL_BLOODY_EATEN:
			msgEntityPillBloodyEaten(msg);
			break;

		case GAME_OVER:
			msgGameOver(msg);
			break;
		case GAME_WON:
			msgGameWon(msg);
			break;

		case CONSUME:
			msgConsume(msg);
			break;

		case LIGHT:
			msgLight(msg);
			break;

		case ZOOM:
			msgZoom(msg);
			break;

		case SOUND:
			msgSound(msg);
			break;
		case SOUND_VOLUME:
			msgSoundVolume(msg);
			break;
		default:
			throw 0; //temp, make fix
			break;
		}
	}
}

void ObserverDirector::msgDXWindowHandle(Msg* msg)
{
	MsgDXWindowHandle* msgDX = (MsgDXWindowHandle*)msg;

	for(int i=0; i<(int)observers->size(); i++)
	{
		Observer* observer = observers->at(i);
		if(observer->isSubscriber(msg->Type()))
			observer->getComponent()->push(msgDX);
	}
}

void ObserverDirector::subscribeMsg(Msg* msg)
{
	SubscriptionMsg* subMsg = (SubscriptionMsg*)msg;
	subscribe(subMsg->Subscriber(), subMsg->Subscription());
	delete subMsg;
}

void ObserverDirector::subscribe(Component* subscriber, MsgType subscription)
{	//todoist, check if observer already exists - modify original subscriber
	observers->push_back(new Observer(subscriber, subscription));
}
void ObserverDirector::msgGlut(Msg* msg)
{
	MsgType type = msg->Type();
	MsgGlut* glutMsg = (MsgGlut*)msg;
	for(unsigned int i = 0; i < observers->size(); i++)
	{
		Observer* observer = observers->at(i);
		if(observer->isSubscriber(type))
		{
			MsgGlut* newInstance = new MsgGlut(glutMsg);
			observer->getComponent()->push(newInstance);
		}
	}
	delete glutMsg;
}
void ObserverDirector::msgGlutCallback(Msg* msg)
{
	MsgType type = msg->Type();
	MsgGlutCallback* glutCallback = (MsgGlutCallback*)msg;
	for(unsigned int i = 0; i < observers->size(); i++)
	{
		Observer* observer = observers->at(i);
		if(observer->isSubscriber(type))
		{
			MsgGlutCallback* newInstance = new MsgGlutCallback(glutCallback);
			observer->getComponent()->push(newInstance);
		}
	}
	delete glutCallback;
}
void ObserverDirector::msgRender(Msg* msg)
{
	MsgType type = msg->Type();
	MsgRender* renderMsg = (MsgRender*)msg;

	for(unsigned int i = 0; i < observers->size(); i++)
	{
		Observer* observer = observers->at(i);
		if(observer->isSubscriber(type))
		{
			MsgRender* newInstance = new MsgRender(renderMsg);
			observer->getComponent()->push(newInstance);
		}
	}
	delete renderMsg;
}
void ObserverDirector::msgMouseClick(Msg* msg)
{
	MsgType type = msg->Type();
	MsgMouseClick* msgClick = (MsgMouseClick*)msg;
	for(unsigned int i = 0; i < observers->size(); i++)
	{
		Observer* observer = observers->at(i);
		if(observer->isSubscriber(type))
		{
			MsgMouseClick* newInstance = new MsgMouseClick(msgClick);
			observer->getComponent()->push(newInstance);
		}
	}
	delete msgClick;
}
void ObserverDirector::msgMouseMove(Msg* msg)
{
	MsgType type = msg->Type();
	MsgMouseMove* msgMove = (MsgMouseMove*)msg;
	for(unsigned int i = 0; i < observers->size(); i++)
	{
		Observer* observer = observers->at(i);
		if(observer->isSubscriber(type))
		{
			MsgMouseMove* newInstance = new MsgMouseMove(msgMove);
			observer->getComponent()->push(newInstance);
		}
	}
	delete msgMove;
}
void ObserverDirector::msgKeyboard(Msg* msg)
{
	MsgType type = msg->Type();
	MsgKeyboard* msgKeyboard = (MsgKeyboard*)msg;
	for(unsigned int i = 0; i < observers->size(); i++)
	{
		Observer* observer = observers->at(i);
		if(observer->isSubscriber(type))
		{
			MsgKeyboard* newInstance = new MsgKeyboard(msgKeyboard);
			observer->getComponent()->push(newInstance);
		}
	}
	delete msgKeyboard;
}
void ObserverDirector::msgCamera(Msg* msg)
{
	MsgType type = msg->Type();
	MsgCamera* msgCam = (MsgCamera*)msg;
	for(unsigned int i = 0; i < observers->size(); i++)
	{
		Observer* observer = observers->at(i);
		if(observer->isSubscriber(type))
		{
			MsgCamera* newInstance = new MsgCamera(msgCam);
			observer->getComponent()->push(newInstance);
		}
	}
	delete msgCam;
}
void ObserverDirector::msgZoom(Msg* msg)
{
	MsgType type = msg->Type();
	MsgZoom* msgZoom = (MsgZoom*)msg;
	for(unsigned int i = 0; i < observers->size(); i++)
	{
		Observer* observer = observers->at(i);
		if(observer->isSubscriber(type))
		{
			MsgZoom* newInstance = new MsgZoom(msgZoom);
			observer->getComponent()->push(newInstance);
		}
	}
	delete msgZoom;
}

void ObserverDirector::msgEntityPlayerPos(Msg* msg)
{
	MsgType type = msg->Type();
	MsgEntityPlayerPos* msgCast = (MsgEntityPlayerPos*)msg;
	for(unsigned int i = 0; i < observers->size(); i++)
	{
		Observer* observer = observers->at(i);
		if(observer->isSubscriber(type))
		{
			MsgEntityPlayerPos* newInstance = new MsgEntityPlayerPos(msgCast);
			observer->getComponent()->push(newInstance);
		}
	}
	delete msgCast;
}
void ObserverDirector::msgEntityPacmanPos(Msg* msg)
{
	MsgType type = msg->Type();
	MsgEntityPacmanPos* msgCast = (MsgEntityPacmanPos*)msg;
	for(unsigned int i = 0; i < observers->size(); i++)
	{
		Observer* observer = observers->at(i);
		if(observer->isSubscriber(type))
		{
			MsgEntityPacmanPos* newInstance = new MsgEntityPacmanPos(msgCast);
			observer->getComponent()->push(newInstance);
		}
	}
	delete msgCast;
}
void ObserverDirector::msgEntityGhostPos(Msg* msg)
{
	MsgType type = msg->Type();
	MsgEntityGhostPos* msgCast = (MsgEntityGhostPos*)msg;
	for(unsigned int i = 0; i < observers->size(); i++)
	{
		Observer* observer = observers->at(i);
		if(observer->isSubscriber(type))
		{
			MsgEntityGhostPos* newInstance = new MsgEntityGhostPos(msgCast);
			observer->getComponent()->push(newInstance);
		}
	}
	delete msgCast;
}
void ObserverDirector::msgEntityPillPos(Msg* msg)
{
	MsgType type = msg->Type();
	MsgEntityPillPos* msgCast = (MsgEntityPillPos*)msg;
	for(unsigned int i = 0; i < observers->size(); i++)
	{
		Observer* observer = observers->at(i);
		if(observer->isSubscriber(type))
		{
			MsgEntityPillPos* newInstance = new MsgEntityPillPos(msgCast);
			observer->getComponent()->push(newInstance);
		}
	}
	delete msgCast;
}
void ObserverDirector::msgEntityGhostSpawn(Msg* msg)
{
	for(unsigned int i = 0; i < observers->size(); i++)
	{
		Observer* observer = observers->at(i);
		if(observer->isSubscriber(msg->Type()))
		{
			observer->getComponent()->push(new MsgEntityGhostSpawn());
		}
	}
	delete msg;
}
void ObserverDirector::msgEntityPillEaten(Msg* msg)
{
	for(unsigned int i = 0; i < observers->size(); i++)
	{
		Observer* observer = observers->at(i);
		if(observer->isSubscriber(msg->Type()))
		{
			observer->getComponent()->push(new MsgEntityPillEaten());
		}
	}
	delete msg;
}
void ObserverDirector::msgEntityPillBloodyEaten(Msg* msg)
{
	for(unsigned int i = 0; i < observers->size(); i++)
	{
		Observer* observer = observers->at(i);
		if(observer->isSubscriber(msg->Type()))
		{
			observer->getComponent()->push(new MsgEntityPillBloodyEaten());
		}
	}
	delete msg;
}

void ObserverDirector::msgGameOver(Msg* msg)
{
	for(unsigned int i = 0; i < observers->size(); i++)
	{
		Observer* observer = observers->at(i);
		if(observer->isSubscriber(msg->Type()))
		{
			observer->getComponent()->push(new MsgGameOver());
		}
	}
	delete msg;
}
void ObserverDirector::msgGameWon(Msg* msg)
{
	for(unsigned int i = 0; i < observers->size(); i++)
	{
		Observer* observer = observers->at(i);
		if(observer->isSubscriber(msg->Type()))
		{
			observer->getComponent()->push(new MsgGameWon());
		}
	}
	delete msg;
}
void ObserverDirector::msgConsume(Msg* msg)
{
	MsgType type = msg->Type();
	MsgConsume* consumeMsg = (MsgConsume*)msg;
	for(unsigned int i = 0; i < observers->size(); i++)
	{
		Observer* observer = observers->at(i);
		if(observer->isSubscriber(type))
		{
			MsgConsume* newInstance = new MsgConsume(consumeMsg);
			observer->getComponent()->push(newInstance);
		}
	}
	delete consumeMsg;
}

void ObserverDirector::msgSound(Msg* msg)
{
	MsgType type = msg->Type();
	MsgSound* soundMsg = (MsgSound*)msg;
	for(unsigned int i=0; i<observers->size(); i++)
	{
		Observer* observer = observers->at(i);
		if(observer->isSubscriber(type))
		{
			MsgSound* newInstance =  new MsgSound(soundMsg);
			observer->getComponent()->push(newInstance);
		}
	}
	delete soundMsg;
}
void ObserverDirector::msgSoundVolume(Msg* msg)
{
	MsgType type = msg->Type();
	MsgSoundVolume* msgSoundVolume = (MsgSoundVolume*)msg;
	for(unsigned int i=0; i<observers->size(); i++)
	{
		Observer* observer = observers->at(i);
		if(observer->isSubscriber(type))
		{
			MsgSoundVolume* newInstance = new MsgSoundVolume(msgSoundVolume);
			observer->getComponent()->push(newInstance);
		}
	}
	delete msgSoundVolume;
}

void ObserverDirector::msgLight(Msg* msg)
{
	MsgType type = msg->Type();
	MsgLight* msgLight = (MsgLight*)msg;
	for(unsigned int i = 0; i<observers->size(); i++)
	{
		Observer* observer = observers->at(i);
		if(observer->isSubscriber(type))
		{
			MsgLight* newInstance = new MsgLight(msgLight);
			observer->getComponent()->push(newInstance);
		}
	}
	delete msgLight;
}

ObserverDirector::ObserverDirector() : Component()
{
	observers = new std::vector<Observer*>();
}
ObserverDirector::~ObserverDirector()
{
	if(observers != NULL)
	{
		for(unsigned int i = 0; i < observers->size(); i++)
			if(observers->at(i) != NULL)
				delete observers->at(i);
		delete observers;
	}
}

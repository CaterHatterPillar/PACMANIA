#ifndef INPUTGL_H
#define INPUTGL_H

#include "../Common.h"
#include "../Component.h"
#include "../Singleton.h"

#include "../Math/PacMath.h"

#include "../GL/CommonGL.h"

#include "../Messaging/ObserverDirector.h"
#include "../Messaging/MsgGlutCallback.h"
#include "../Messaging/MsgKeyboard.h"
#include "../Messaging/MsgMouseClick.h"
#include "../Messaging/MsgMouseMove.h"

class InputGL : public Component
{
private:
	static int halfWidth;
	static int halfHeight;

	static bool warpLock;
protected:
public:
	void init();
	void update(double delta);
	
	static void mouseSpec(int x, int y);
	static void keyboardSpec(unsigned char key, int x, int y);
	static void keyboardSpecialSpec(int key, int x, int y);

	InputGL();
	~InputGL();
};

#endif //INPUTGL_H
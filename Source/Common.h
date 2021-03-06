#ifndef COMMON_H
#define COMMON_H

#include "assert.h"
#include <stdio.h>

/*Lists*/
#include <vector>
#include <queue>
#include <map>

#include <string>
#include <sstream>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

#define F_O_V	45
#define Z_NEAR	1
#define Z_FAR	1000
#define ZOOMED_IN -10.0f
#define ZOOMED_OUT -1000.0f

#define DELETE_NULL(param) { if(param) { delete param; } param = NULL; }

template <class T>
inline std::string TO_STRING(const T& t)
{
	std::stringstream ss;
	ss << t;
	return ss.str();
}

class PlatformCheck
{
public:
	bool openGL;
};

#endif //COMMON_H
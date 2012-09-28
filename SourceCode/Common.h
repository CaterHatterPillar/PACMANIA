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

#define F_O_V	60
#define Z_NEAR	1
#define Z_FAR	1000

template <class T>
inline std::string TO_STRING(const T& t)
{
	std::stringstream ss;
	ss << t;
	return ss.str();
}

#endif //COMMON_H
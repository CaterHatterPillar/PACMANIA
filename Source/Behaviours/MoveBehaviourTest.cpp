#ifndef MOVEBEHAVIOURTEST_H
#define MOVEBEHAVIOURTEST_H

#include <gmock/gmock.h>
#include "../../Source/Behaviours/MoveBehaviourPlayer.h"
#include "../../Source/Math/PacMath.h"

//class MoveBehaviourPlayerTest : public ::testing::Test
//{
//protected:
//	MoveBehaviourPlayer* moveBehaviour;
//	//MoveBehaviourPlayer moveBehaviour;
//
//	//MoveBehaviourPlayerTest(void)
//	//{
//	//	moveBehaviour = new MoveBehaviourPlayer();
//	//}
//	//~MoveBehaviourPlayerTest(void)
//	//{
//	//	if (moveBehaviour)
//	//		delete moveBehaviour;
//	//}
//};

//void foo()
//{
//	MoveBehaviourPlayer* moveBehaviour = new MoveBehaviourPlayer();
//	delete moveBehaviour;
//}

//TEST(MoveBehaviourPlayerTest, PositionIsCorrectlyInitialized)
//{
//	MoveBehaviourPlayer* moveBehaviour = new MoveBehaviourPlayer(0);
//	VecF3 pos = moveBehaviour->getPosition();
//	//VecF3 dir = moveBehaviour.getDirection();
//	EXPECT_FLOAT_EQ(0.0f, pos.x);
//	EXPECT_FLOAT_EQ(0.0f, pos.y);
//	EXPECT_FLOAT_EQ(0.0f, pos.z);
//}

#endif //MOVEBEHAVIOURTEST_H
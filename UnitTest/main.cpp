#include <gtest/gtest.h>

#include "math/toolbox_typedef.hpp"
#include "core/motion_core_engine.hpp"

using namespace Tbx;


// Demonstrate some basic assertions.
TEST(HelloTest, BasicAssertions) 
{
	MotionCoreEngine::HelloEngine();

  // Expect two strings not to be equal.
  //EXPECT_STRNE("hello", "world");
  // Expect equality.
  //EXPECT_EQ(7 * 6, 42);
}
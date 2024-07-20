#pragma once

#include <MotionCoreHeader.h>

namespace MotionCore
{

	float GetSeparatintVelocity(const ToolBox::Vector2f& _pos1, const ToolBox::Vector2f& _pos2,
		const ToolBox::Vector2f& _vel1, const ToolBox::Vector2f& _vel2);

}

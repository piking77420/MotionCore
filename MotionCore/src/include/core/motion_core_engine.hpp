#pragma once

#include "rigid_body.hpp"

namespace MotionCore
{
	struct CreateBodyInfo
	{
		ColliderType type;
		union 
		{
			numeric radius;
			Quat q;
		}info;
		Vec3 position;
	};

	struct MotionCoreEngineCreateInfo
	{
		uint32_t maxBodies;
	};


	class MotionCoreEngine
	{
	public:
		
		MOTION_CORE_API void Init(const MotionCoreEngineCreateInfo& _MotionCoreEngineCreateInfo);

		MOTION_CORE_API MotionCoreEngine();

		MOTION_CORE_API ~MotionCoreEngine();

		MOTION_CORE_API static void HelloEngine();
	private:
		RigidBody* bodies = nullptr;
		
	};


}


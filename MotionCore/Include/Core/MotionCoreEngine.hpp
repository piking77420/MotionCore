#pragma once

#include "RigidBody.hpp"

namespace MotionCore
{
	
	struct CreateBodyInfo
	{
		ShapeType type;
		union 
		{
			numeric radius;
			numeric height;
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
		
		MOTION_CORE_API void InitExternalDevice();
	private:
		RigidBody* bodies = nullptr;
		
	};


}


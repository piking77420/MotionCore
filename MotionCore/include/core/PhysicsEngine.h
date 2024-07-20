#pragma once

#include "MotionCoreHeader.h"
#include "Core/MotionCoreAllocator.h"
#include <body/Circle.h>
#include <queue>

namespace MotionCore
{

	class PhysicsEngine
	{
	public:
		struct PhysicsEngineCreateInfo
		{
			ToolBox::Vector3f gravity = ToolBox::Vector3f(0.f, -9.81f, 0.f);
		};

		MOTION_CORE static void SetBox(const ToolBox::Vector3f& _extent);
		
		MOTION_CORE static void Initialize(const PhysicsEngineCreateInfo& _physicsEngineCreateInfo);

		MOTION_CORE static void Destroy();

		MOTION_CORE static void Update(float _deltatime);

		MOTION_CORE static uint32_t CreateCircleBody(ToolBox::Vector2f _position, float _radius, float _mass);

		MOTION_CORE static void AddForce(uint32_t _id, ToolBox::Vector2f _force);

		MOTION_CORE static void AddImpulse(uint32_t _id, ToolBox::Vector2f _impulse);

		MOTION_CORE static ToolBox::Vector2f GetCircleBodyPosition(uint32_t _id);

	private:
		static PhysicsEngine* m_Instance;

		MOTION_CORE static inline ToolBox::Vector3f m_BoxExtent;

		struct CollisionPoint
		{
			Body* b1 = nullptr;
			Body* b2 = nullptr;
			ToolBox::Vector2f normal;

			float depth = 1.0f;
			float penetrationb1 = 0.0f;
			float penetrationb2 = 0.0f;
		};

		std::vector<Particule> particles;
		std::queue<CollisionPoint> collisionPoint;

		ToolBox::Vector3f m_Gravity;


		static void Integrate(float _deltatime);

		static void NaiveCollisionFounder();

		static void ResolveCollision();

		static void AddForce(Body* _body, ToolBox::Vector2f _force);

		static void AddImpulse(Body* _body, ToolBox::Vector2f _impulse);
	};

}
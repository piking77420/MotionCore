#pragma once

#include "motion_core_typedef.h"
#include "core/motion_core_allocator.h"
#include <queue>

namespace MotionCore
{

	class PhysicsEngine
	{
	public:
		
		struct PhyscicsEngineInitilizationParameters
		{
			 float timeStep = 0.f;
		};
		
		
		MOTION_CORE void Initialize(const PhyscicsEngineInitilizationParameters& _physcicsEngineInitilizationParameters);

		MOTION_CORE void Destroy();

		MOTION_CORE void Update(float _deltaTime);

		MOTION_CORE static uint32_t CreateSphere(Tbx::Vector3f _position, float _radius, float _mass);

		MOTION_CORE static uint32_t DestroySphere(Tbx::Vector3f _position, float _radius, float _mass);

		MOTION_CORE static void AddForce(uint32_t _id, Tbx::Vector3f _force);

		MOTION_CORE static void AddImpulse(uint32_t _id, Tbx::Vector3f _impulse);

	private:
		static PhysicsEngine* m_Instance;
		
		struct CollisionPoint
		{
			Body* b1 = nullptr;
			Body* b2 = nullptr;
			Tbx::Vector2f normal;

			float depth = 1.0f;
			float penetrationb1 = 0.0f;
			float penetrationb2 = 0.0f;
		};

		float accumulateTime = 0.f;

		float timeStep = 0.f; 
		
		std::queue<CollisionPoint> collisionPoint;

		std::vector<Sphere> m_Sphere;

		Tbx::Vector3f m_Gravity = {0.f, -9.81f, 0.f};

		static void Step(float _deltatime);

		static void Integrate(float _deltatime);

		static void NaiveCollisionFounder();

		static void ResolveCollision();

		static void AddForce(Body* _body, Tbx::Vector3f _force);

		static void AddImpulse(Body* _body, Tbx::Vector3f _impulse);
	};

}
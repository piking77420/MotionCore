#include "Core/PhysicsEngine.h"

#include "core/PhysicsHelper.hpp"

#include "memory"

using namespace MotionCore;

PhysicsEngine* PhysicsEngine::m_Instance = nullptr;

void PhysicsEngine::SetBox(const ToolBox::Vector3f& _extent)
{
	m_BoxExtent = _extent;
}

void PhysicsEngine::Initialize(const PhysicsEngineCreateInfo& _physicsEngineCreateInfo)
{
	m_Instance = new PhysicsEngine();
	MotionCoreAllocator::Initialize();
	m_Instance->m_Gravity = _physicsEngineCreateInfo.gravity;
}

void PhysicsEngine::Destroy()
{
	MotionCoreAllocator::Destroy();
	delete m_Instance;
}

void MotionCore::PhysicsEngine::Update(float _deltatime)
{
	{
		Integrate(_deltatime);
	}

	{
		NaiveCollisionFounder();
	}

	{
		ResolveCollision();
	}


}

uint32_t PhysicsEngine::CreateCircleBody(ToolBox::Vector2f _position, float radius, float mass)
{
	Particule p;
	p.body.id = static_cast<uint32_t>(m_Instance->particles.size());
	p.body.position = _position;
	p.radius = radius;
	p.body.invMass = 1.f / mass;

	m_Instance->particles.emplace_back(p);

	return p.body.id;
}
void MotionCore::PhysicsEngine::AddForce(uint32_t _id, ToolBox::Vector2f _force)
{
	auto it = std::find_if(m_Instance->particles.begin(), m_Instance->particles.end(),
		[_id](const Particule& p) { return p.body.id == _id; });

	if (it == m_Instance->particles.end())
		return;

	AddForce(&(*it).body, _force);
}
MOTION_CORE void MotionCore::PhysicsEngine::AddImpulse(uint32_t _id, ToolBox::Vector2f _impulse)
{
	auto it = std::find_if(m_Instance->particles.begin(), m_Instance->particles.end(),
		[_id](const Particule& p) { return p.body.id == _id; });

	if (it == m_Instance->particles.end())
		return;

	AddImpulse(&(*it).body, _impulse);
}
ToolBox::Vector2f MotionCore::PhysicsEngine::GetCircleBodyPosition(uint32_t _id)
{
	auto it = std::find_if(m_Instance->particles.begin(), m_Instance->particles.end(),
		[_id](const Particule& p) { return p.body.id == _id; });

	if (it == m_Instance->particles.end())
		return {};

	return (*it).body.position;
}

void MotionCore::PhysicsEngine::Integrate(float _deltatime)
{
	for (Particule& p : m_Instance->particles)
	{
		Body& body = p.body;

		//p.force += { m_Instance->m_Gravity.x, m_Instance->m_Gravity.y};
		body.acceleration += body.force * body.invMass;
		body.velocity += body.acceleration * _deltatime;
		body.position += body.acceleration * 0.5f * _deltatime * _deltatime + body.velocity * _deltatime;
		body.velocity *= body.physicMaterial.drag;

		body.force = {};
	}
}

void MotionCore::PhysicsEngine::NaiveCollisionFounder()
{

	for (size_t i = 0; i < m_Instance->particles.size(); ++i)
	{
		Particule& p1 = m_Instance->particles[i];

		for (size_t j = i + 1; j < m_Instance->particles.size(); ++j)
		{
			Particule& p2 = m_Instance->particles[j];

			const float maxRadius = p1.radius + p2.radius; 
			ToolBox::Vector2f vec = p2.body.position - p1.body.position;
			const float distanceSquare = vec.MagnitudeSquare(); 

			if (distanceSquare > maxRadius * maxRadius)
				continue;

			float depth = distanceSquare - maxRadius;

			CollisionPoint coll =
			{
				.b1 = &p1.body,
				.b2 = &p2.body,
				.normal = vec,
				.depth = depth, 
				.penetrationb1 = (p1.body.invMass + p2.body.invMass) / p2.body.invMass * depth,
				.penetrationb2 = -(p1.body.invMass + p2.body.invMass) / p1.body.invMass * depth

			};

			m_Instance->collisionPoint.push(coll);
		}
	}
}

void MotionCore::PhysicsEngine::ResolveCollision()
{
	const ToolBox::Vector3f& boxExtend = m_BoxExtent;

	// BOX// 
	for (Particule& p : m_Instance->particles)
	{
		Body& body = p.body;

		bool isOutSide = body.position.x < -boxExtend.x || body.position.x > boxExtend.x ||
			body.position.y < -boxExtend.y || body.position.y > boxExtend.y;

		if (!isOutSide)
			continue;

		body.velocity = -body.velocity;
		body.acceleration = -body.acceleration;

	}

	while (!m_Instance->collisionPoint.empty())
	{
		CollisionPoint collisionPoint = m_Instance->collisionPoint.front();
		m_Instance->collisionPoint.pop();

		Body& b1 = *collisionPoint.b1;
		Body& b2 = *collisionPoint.b2;

		float sepVelocity = MotionCore::GetSeparatintVelocity(b1.position, b2.position,
			b1.velocity, b2.velocity);
		
		float sepVelocityB1 = sepVelocity * b1.physicMaterial.restitutionCoef;
		float sepVelocityB2 = sepVelocity * b2.physicMaterial.restitutionCoef;

		float totalInvertMass = b1.invMass + b2.invMass;

		if (totalInvertMass <= 0)
			continue;

		float deltaVelocityB1 = sepVelocityB1 - sepVelocity;

		float deltaVelocityB2 = sepVelocityB2 - sepVelocity;

		float impulseB1 = deltaVelocityB1 / totalInvertMass;
		float impulseB2 = deltaVelocityB2 / totalInvertMass;

		ToolBox::Vector2f impulseNormalB1 = collisionPoint.normal * impulseB2;
		ToolBox::Vector2f impulseNormalB2 = -collisionPoint.normal * impulseB2;

		AddImpulse(&b1, impulseNormalB1);
		AddImpulse(&b2, impulseNormalB2);

	}

}

void MotionCore::PhysicsEngine::AddForce(Body* _body, ToolBox::Vector2f _force)
{
	_body->force += _force;
}

void MotionCore::PhysicsEngine::AddImpulse(Body* _body, ToolBox::Vector2f _impulse)
{
	_body->velocity += _impulse * _body->invMass;
}



#include "core/physics_engine.h"

#include "core/physics_helper.hpp"

#include "memory"

using namespace MotionCore;

PhysicsEngine* PhysicsEngine::m_Instance = nullptr;


void PhysicsEngine::Initialize(const PhyscicsEngineInitilizationParameters& _physcicsEngineInitilizationParameters)
{
    m_Instance = this;
    MotionCoreAllocator::Initialize();
}

void PhysicsEngine::Destroy()
{
    MotionCoreAllocator::Destroy();
}

void MotionCore::PhysicsEngine::Update(float _deltaTime)
{
    accumulateTime += _deltaTime;

    while (accumulateTime >= timeStep)
    {
        Step(timeStep);
        accumulateTime -= timeStep;
    }
}

uint32_t PhysicsEngine::CreateSphere(Tbx::Vector3f _position, float radius, float mass)
{
    const uint32_t id = static_cast<uint32_t>(m_Instance->m_Sphere.size());

    Sphere s =
    {
        s.body =
        {
            .id = id,
            .invMass = 1.f / mass,
            .position = _position,
            .velocity = {},
            .acceleration = {},
            .force = {}
        },
        radius
    };
    m_Instance->m_Sphere.push_back(s);

    return m_Instance->m_Sphere.at(m_Instance->m_Sphere.size() - 1).body.id;
}

void MotionCore::PhysicsEngine::AddForce(uint32_t _id, Tbx::Vector3f _force)
{
    auto it = std::find_if(m_Instance->m_Sphere.begin(), m_Instance->m_Sphere.end(),
                           [_id](const Sphere& p) { return p.body.id == _id; });

    if (it == m_Instance->m_Sphere.end())
        return;

    AddForce(&(*it).body, _force);
}

void MotionCore::PhysicsEngine::AddImpulse(uint32_t _id, Tbx::Vector3f _impulse)
{
    auto it = std::find_if(m_Instance->m_Sphere.begin(), m_Instance->m_Sphere.end(),
                           [_id](const Sphere& p) { return p.body.id == _id; });

    if (it == m_Instance->m_Sphere.end())
        return;

    AddImpulse(&(*it).body, _impulse);
}

void PhysicsEngine::Step(float _deltatime)
{
    Integrate(_deltatime);
    NaiveCollisionFounder();
    ResolveCollision();
}

void MotionCore::PhysicsEngine::Integrate(float _deltatime)
{
    static constexpr float drag = 0.99f;

    for (Sphere& s : m_Instance->m_Sphere)
    {
        Body& body = s.body;

        body.force += m_Instance->m_Gravity;
        body.acceleration += body.force * body.invMass;
        body.velocity += body.acceleration * _deltatime;
        body.position += body.acceleration * 0.5f * _deltatime * _deltatime + body.velocity * _deltatime;
        body.velocity *= drag;

        body.force = {};
    }
}

void MotionCore::PhysicsEngine::NaiveCollisionFounder()
{
}

void MotionCore::PhysicsEngine::ResolveCollision()
{
}

void MotionCore::PhysicsEngine::AddForce(Body* _body, Tbx::Vector3f _force)
{
    _body->force += _force;
}

void MotionCore::PhysicsEngine::AddImpulse(Body* _body, Tbx::Vector3f _impulse)
{
    _body->velocity += _impulse * _body->invMass;
}

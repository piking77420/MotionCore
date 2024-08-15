#include "core/physics_engine.h"

#include "core/physics_helper.hpp"

#include "memory"

using namespace MotionCore;

void PhysicsEngine::Initialize(const PhyscicsEngineInitilizationParameters* _physcicsEngineInitilizationParameters)
{
    MotionCoreAllocator::Initialize();
    timeInfo.timeStep = _physcicsEngineInitilizationParameters->timeStep;
}

void PhysicsEngine::Destroy()
{
    MotionCoreAllocator::Destroy();
}

void MotionCore::PhysicsEngine::Update(numeric _deltaTime)
{
    timeInfo.accumulateTime += _deltaTime;

    while (timeInfo.accumulateTime >= timeInfo.timeStep)
    {
        Step(timeInfo.timeStep);
        timeInfo.accumulateTime -= timeInfo.timeStep;
    }
}

void PhysicsEngine::AddForce(uint32_t _id, const Vec3& _forces)
{
    /*
    Body* body = GetBodyFromId(_id);
    AddForce(body, _forces);*/
}

void PhysicsEngine::AddImpulse(uint32_t _id, const Vec3& _impluse)
{
    /*
    Body* body = GetBodyFromId(_id);
    AddImpulse(body, _impluse);*/
}

uint32_t PhysicsEngine::CreateBody(const CreateBodyInfo* _CreateBodyInfo)
{
    

    return 0;
}


void PhysicsEngine::Step(float _deltatime)
{
    Integrate(_deltatime);
    //NaiveCollisionFounder();
    //ResolveCollision();
}

void MotionCore::PhysicsEngine::Integrate(float _deltatime)
{
    for (Body& body : m_ObjectInfo.bodies)
    {
        body.force += m_Gravity;
        body.acceleration += body.force * body.invMass;
        body.velocity += body.acceleration * _deltatime;
        body.position += body.acceleration * 0.5f * _deltatime * _deltatime + body.velocity * _deltatime;
        body.velocity *= body.physcicalMaterial.drag;

        body.force = {};
    }
}



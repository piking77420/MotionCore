#include "core/physics_engine.h"

#include <iostream>

#include "core/physics_helper.hpp"

#include "memory"

using namespace MotionCore;

void PhysicsEngine::Initialize(const PhyscicsEngineInitilizationParameters* _physcicsEngineInitilizationParameters)
{
    MotionCoreAllocator::Initialize();
    timeInfo.timeStep = _physcicsEngineInitilizationParameters->timeStep;
    m_ObjectInfo.bodies.resize(MAX_BODIES);
    m_ObjectInfo.primitiveInfo.resize(MAX_BODIES); 

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
    Body* body = GetBodyFromId(m_ObjectInfo.bodies, _id);
    integrator.AddForce(body, _forces);
}

void PhysicsEngine::AddImpulse(uint32_t _id, const Vec3& _impluse)
{
    Body* body = GetBodyFromId(m_ObjectInfo.bodies, _id);
    integrator.AddImpulse(body, _impluse);
}

void PhysicsEngine::AddTorque(uint32_t _id, const Vec3& _torque)
{
    Body* body = GetBodyFromId(m_ObjectInfo.bodies, _id);
    integrator.AddTorque(body, _torque);
}

uint32_t PhysicsEngine::CreateBody(const BodyCreateInfo& _bodyCreateInfo)
{
    const uint32_t bodyId = GetValidBodyId();
    Body& bodyRef = m_ObjectInfo.bodies[bodyId];
    bodyRef.id = bodyId;
    InitBody(&bodyRef, &_bodyCreateInfo);

    return bodyId;
}

bool PhysicsEngine::DestroyBody(uint32_t _bodyID)
{   
    Body* body = GetBodyFromId(m_ObjectInfo.bodies, _bodyID);
    if (body == nullptr)
    {
        // Error
        return false;
    }
    *body = {};
    return true;
}

Vec3 PhysicsEngine::GetPosition(uint32_t _id)
{
    return m_ObjectInfo.bodies[_id].position;
}

Quat PhysicsEngine::GetRotation(uint32_t _id)
{
    return m_ObjectInfo.bodies[_id].rotation;
}


void PhysicsEngine::Step(numeric _deltatime)
{
    integrator.IntegrateBodies(&m_ObjectInfo, m_Gravity, _deltatime);
    m_CollisionDetector.FoundCollision(&m_ObjectInfo);
    m_CollisionSolver.SolveCollsion(&m_ObjectInfo);
}

uint32_t PhysicsEngine::GetValidBodyId() const
{
    size_t i = 0;
    for (; i < m_ObjectInfo.bodies.size(); i++)
    {
        if (m_ObjectInfo.bodies[i].id == NULLBODY)
            return static_cast<uint32_t>(i);
    }
    return NULLBODY;
}

void PhysicsEngine::InitBody(Body* _body, const BodyCreateInfo* _bodyCreateInfo)
{
    _body->invMass = static_cast<numeric>(1) / _bodyCreateInfo->mass;
    size_t i = 0;
    for (; i < m_ObjectInfo.primitiveInfo.size(); i++)
    {
        if (m_ObjectInfo.primitiveInfo[i].bodyType == NONE)
        {
            m_ObjectInfo.primitiveInfo[i].bodyType = _bodyCreateInfo->bodyTypeInfo.bodyType;
            m_ObjectInfo.primitiveInfo[i].data = _bodyCreateInfo->bodyTypeInfo.data;
            _body->primitiveIndex = static_cast<uint32_t>(i);
            break;
        }
    }
    
    _body->position = _bodyCreateInfo->position;
    _body->rotation = _bodyCreateInfo->rotation;
    
    _body->physcicalMaterial.damping = _bodyCreateInfo->physcicalMaterial.damping;
    _body->physcicalMaterial.restitutionCoeff = _bodyCreateInfo->physcicalMaterial.restitutionCoeff;
}





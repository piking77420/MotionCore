#include "core/physics_engine.h"

#include <iostream>

#include "core/physics_helper.hpp"

#include "memory"
#include "algo/primitive_test.h"
#include "algo/quick_hull.hpp"

using namespace MotionCore;

void PhysicsEngine::Initialize(const PhyscicsEngineInitilizationParameters* _physcicsEngineInitilizationParameters)
{
    MotionCoreAllocator::Initialize();
    timeInfo.timeStep = _physcicsEngineInitilizationParameters->timeStep;
    m_ObjectInfo.bodies.resize(MAX_BODIES);
    m_ObjectInfo.primitiveInfo.resize(MAX_BODIES); 

/*
    // test //

    Tbx::Vector3f array[4] =
 {
        {2, 3, 1},    // Vertex 0
        {7, -2, 4},   // Vertex 1
        {10, 10, 3},   // Vertex 2
        {5, 7, 2}    // Vertex 3
 };

    Tbx::Vector3f p1 = {4, -2, 8};  // Point 1 on the plane
    Tbx::Vector3f p2 = {1, 3, 5};   // Point 2 on the plane
    Tbx::Vector3f p3 = {6, 2, 0};   // Point 3 on the plane
        
    BeginHull hull;
    hull._verticiesData = array;
    hull._vertexSize = sizeof(p1);
    hull._positionOffSet = 0;
    hull._nbrOfVerticies = 4;
    
    int index = FarestVertexFromFacesAndOutSideTheOrigin(p1,p2,p3,&hull);
*/

    OBB obb;
    obb.extend = 0.5f;
    Vec3 center;
    Vec3 point = {0,2,0};
    Tbx::RotationMatrix3D(Deg2Rad * 70,Deg2Rad * 45,Deg2Rad * -30, &obb.orientationMatrix);
    point = ClosetPointToOOB(point,center,obb);
    
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
    const PrimitiveInfo& primitiveInfo = m_ObjectInfo.primitiveInfo.at( m_ObjectInfo.bodies.at(_id).primitiveIndex);
    
    return primitiveInfo.position;
}

Quat PhysicsEngine::GetRotation(uint32_t _id)
{
    return m_ObjectInfo.bodies[_id].rotation;
}

uint32_t PhysicsEngine::CreateMeshInfo(void* _verticiesData, uint32_t _nbrOfVerticies, uint32_t _vertexSize,
    uint32_t _vectorSize, uint32_t _vectorDataSize, uint32_t _positionOffSet)
{
    // TODO
    return 0;
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

    if (_bodyCreateInfo->bodyTypeInfo.bodyType == MESH && _bodyCreateInfo->bodyTypeInfo.data.physicsMeshId == static_cast<uint32_t>(-1))
    {
        // ERROR
        return;
    }
    
    for (; i < m_ObjectInfo.primitiveInfo.size(); i++)
    {
        if (m_ObjectInfo.primitiveInfo[i].bodyType == NONE)
        {
            m_ObjectInfo.primitiveInfo[i].bodyType = _bodyCreateInfo->bodyTypeInfo.bodyType;
            m_ObjectInfo.primitiveInfo[i].data = _bodyCreateInfo->bodyTypeInfo.data;
            m_ObjectInfo.primitiveInfo[i].position = _bodyCreateInfo->position;
            
            _body->primitiveIndex = static_cast<uint32_t>(i);
            break;
        }
    }
    
   
    _body->rotation = _bodyCreateInfo->rotation;
    
    _body->physcicalMaterial = _bodyCreateInfo->physcicalMaterial;
}

Vec3 PhysicsEngine::GetWorldCenterOfMass(const Body* _body) const
{
    if (_body->id == NULLBODY || _body->primitiveIndex == NULLPRIMITVE)
    {
        // error
        return {};
    }
    
    const PrimitiveInfo primitiveInfo = m_ObjectInfo.primitiveInfo.at(_body->primitiveIndex);
    
    switch (primitiveInfo.bodyType)
    {
    case NONE:
        break;
    case SPHERE:
        return {};
    case BOX:
        return {};
    case CAPSULE:
        return { static_cast<numeric>(0), static_cast<numeric>(0), m_ObjectInfo.primitiveInfo.at(_body->primitiveIndex).data.caspule.height * static_cast<numeric>(0.5) };
        break;
    case MESH:
        return m_ObjectInfo.meshDatas.at(primitiveInfo.data.physicsMeshId).worldCenterOfMass;
        break;
    }

    return {};
}





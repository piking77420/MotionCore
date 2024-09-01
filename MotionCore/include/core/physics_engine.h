#pragma once

#include "motion_core_typedef.h"
#include "core/motion_core_allocator.h"
#include <queue>

#include "collision_solver.h"
#include "collision_detector.hpp"
#include "integrator.hpp"

namespace MotionCore
{
    struct PhyscicsEngineInitilizationParameters
    {
        numeric timeStep = static_cast<numeric>(0);
    };

    class PhysicsEngine
    {
    public:
       
        MOTION_CORE void Initialize(const PhyscicsEngineInitilizationParameters* _physcicsEngineInitilizationParameters);

        MOTION_CORE void Destroy();

        MOTION_CORE void Update(numeric _deltaTime);

        MOTION_CORE FORCEINLINE void AddForce(uint32_t _id, const Vec3& _forces);

        MOTION_CORE FORCEINLINE void AddImpulse(uint32_t _id, const Vec3& _impluse);

        MOTION_CORE FORCEINLINE void AddTorque(uint32_t _id, const Vec3& _torque);

        MOTION_CORE uint32_t CreateBody(const BodyCreateInfo& _bodyCreateInfo);

        MOTION_CORE bool DestroyBody(uint32_t _bodyID);

        MOTION_CORE Vec3 GetPosition(uint32_t _id);

        MOTION_CORE Quat GetRotation(uint32_t _id);
        
        /**
         * \brief Create a convex Hull and compute worldCenter of mass of a mesh in backend from a set of verticies
         * \param _verticiesData ptr to the continous memory of verticies
         * \param _nbrOfVerticies number of Verticies in th mesh
         * \param _vertexSize size of one Vertex
         * \param _vectorSize size of one Point (usually Vector2 , vector3)
         * \param _vectorDataSize size of one element in the Vector
         * \param _positionOffSet the offset of position in verticies
         * \return 
         */
        MOTION_CORE uint32_t CreateMeshInfo(void* _verticiesData, uint32_t _nbrOfVerticies, uint32_t _vertexSize, uint32_t _vectorSize, uint32_t _vectorDataSize,  uint32_t _positionOffSet); 

    private:
        Vec3 m_Gravity = {0.f, -9.81f, 0.f};
        
        struct TimeInfo
        {
            numeric accumulateTime = static_cast<numeric>(0);
            numeric timeStep = static_cast<numeric>(0);
        };

        TimeInfo timeInfo;

        MotionCoreContext m_ObjectInfo;

        Integrator integrator; 

        CollisionSolver m_CollisionSolver;

        CollisionDetector m_CollisionDetector;
        
        void Step(numeric _deltatime);

        void Integrate(numeric _deltatime);
        
        uint32_t GetValidBodyId() const;

        void InitBody(Body* _body, const BodyCreateInfo* _bodyCreateInfo);

        Vec3 GetWorldCenterOfMass(const Body* _body) const;
        
    };
}

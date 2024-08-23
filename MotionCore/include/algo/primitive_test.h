#pragma once
#include <algorithm>

#include "primitive_type_def.h"
#include "math/simd_operation.h"

namespace MotionCore
{
    FORCEINLINE numeric DistanceToPlane(const Vec3& _vec, const Plane& _plane)
    {
        numeric t = static_cast<numeric>(0.f);

        if (IsEqualTo<numeric>(_plane.normal.Magnitude(), NUMERICAL_ONE))
        {
            t = (Vec3::Dot(_plane.normal, _vec) - _plane.distance);
        }
        else
        {
            t = (Vec3::Dot(_plane.normal, _vec) - _plane.distance) / Vec3::Dot(_plane.normal, _plane.normal);
        }

        return t;
    }

    FORCEINLINE Vec3 ClosetPointOnPlane(const Vec3& _vec, const Plane& _plane)
    {
        const numeric t = DistanceToPlane(_vec, _plane);
        return _vec - (_plane.normal * t);
    }

    FORCEINLINE Vec3 ClosetPointSegment(const Vec3& _pointC, const Vec3& _pointA, const Vec3& _pointB, numeric* _t)
    {
        const Vec3 ab = _pointB - _pointA;
        Vec3 outPoint;

        *_t = Vec3::Dot(_pointC - _pointA, ab) / Vec3::Dot(ab, ab);

        if (*_t <= NUMERICAL_ZERO)
        {
            *_t = NUMERICAL_ZERO;
            outPoint = ab;
        }
        else
        {
            const numeric denom = ab.MagnitudeSquare(); // dot self
            if (*_t >= denom)
            {
                *_t = NUMERICAL_ONE;
                outPoint = _pointB;
            }
            else
            {
                *_t = *_t / denom;
                outPoint = _pointA + (ab * *_t);
            }
        }

        return outPoint;
    }

    FORCEINLINE numeric SqDistancePointSegment(const Vec3& _pointA, const Vec3& _pointB, const Vec3& _pointC)
    {
        const Vec3 ab = _pointB - _pointA;
        const Vec3 ac = _pointC - _pointA;
        const Vec3 bc = _pointC - _pointB;

        const numeric e = Vec3::Dot(ac, ab);

        if (e <= NUMERICAL_ZERO) return ac.MagnitudeSquare();
        const numeric f = ab.MagnitudeSquare();
        if (e >= NUMERICAL_ONE) return bc.MagnitudeSquare();

        return ac.MagnitudeSquare() - e * e / f;
    }

    FORCEINLINE Vec3 ClosestPointOnAABB(Vec3 _point, const Vec3& _aabbCenter, const AABB& _aabb)
    {
        const Vec3 min = _aabbCenter - _aabb.extend;
        const Vec3 max = _aabbCenter + _aabb.extend;

        _point = Tbx::SIMD::min<numeric>(min, _point);
        _point = Tbx::SIMD::max<numeric>(max, _point);
        return _point;
    }

    FORCEINLINE numeric SqDistancePointAABB(const Vec3& _point, const Vec3& _aabbCenter, const AABB& _aabb)
    {
        const Vec3 min = _aabbCenter - _aabb.extend;
        const Vec3 max = _aabbCenter + _aabb.extend;
        numeric sqDistance = NUMERICAL_ZERO;

        for (size_t i = 0; i < 3; i++)
        {
            const numeric value = _point[i];
            if (value < min[i]) sqDistance += (min[i] - value) * (min[i] - value);
            if (value > max[i]) sqDistance += (value - max[i]) * (value - max[i]);
        }

        return sqDistance;
    }

    FORCEINLINE Vec3 ClosetPointToOOB(const Vec3& _point, const Vec3& _obbCenter, const OBB& _oBB)
    {
        const Vec3 d = _point - _obbCenter;
        Vec3 outPoint = _obbCenter;

        for (size_t i = 0; i < decltype(_oBB.orientationMatrix)::Size; i++)
        {
            Vec3 axis = _oBB.orientationMatrix[i];
            numeric dist = Vec3::Dot(d, _oBB.orientationMatrix[i]);
            dist = std::clamp(dist, -_oBB.extend[i], _oBB.extend[i]);
            outPoint += _oBB.orientationMatrix[i] * dist;
        }

        return outPoint;
    }

    FORCEINLINE Vec3 SqDistancePointOOBB(const Vec3& _point, const Vec3& _obbCenter, const OBB& _oBB)
    {
        return (ClosetPointToOOB(_point, _obbCenter, _oBB) - _point).MagnitudeSquare();
    }

    FORCEINLINE bool TestSpherePlane(const Vec3& _sphereCenter, const Sphere _sphere, const Plane& _plane)
    {
        const numeric dist = Vec3::Dot(_sphereCenter, _plane.normal) - _plane.distance;
        return std::abs(dist) <= _sphere.radius;
    }

    FORCEINLINE bool InsideSpherePlane(const Vec3& _sphereCenter, const Sphere _sphere, const Plane& _plane)
    {
        const numeric dist = Vec3::Dot(_sphereCenter, _plane.normal) - _plane.distance;
        return dist < -_sphere.radius;
    }

    FORCEINLINE bool TestSphereHalfSpace(const Vec3& _sphereCenter, const Sphere _sphere, const Plane& _plane)
    {
        const numeric dist = Vec3::Dot(_sphereCenter, _plane.normal) - _plane.distance;
        return dist <= _sphere.radius;
    }

    FORCEINLINE bool TestOOBPlane(const Vec3& _OBBCenter, const OBB& _Obb, const Plane& _plane)
    {
        const numeric r = _Obb.extend.x * std::abs(Vec3::Dot(_plane.normal, _Obb.orientationMatrix[0]))
            + _Obb.extend.y * std::abs(Vec3::Dot(_plane.normal, _Obb.orientationMatrix[1]))
            + _Obb.extend.z * std::abs(Vec3::Dot(_plane.normal, _Obb.orientationMatrix[2]));

        const numeric s = Vec3::Dot(_plane.normal, _OBBCenter) - _plane.distance;

        return std::abs(s) <= r;
    }

    FORCEINLINE bool TestAABBPlane(const Vec3& _aabbCenter, const AABB& _aabb, const Plane& _plane)
    {
        const numeric r = _aabb.extend.x * std::abs(_plane.normal.x) + _aabb.extend.y * std::abs(_plane.normal.y)
            + _aabb.extend.z * std::abs(_plane.normal.z);

        const numeric s = Vec3::Dot(_plane.normal, _aabbCenter) - _plane.distance;

        return std::abs(s) <= r;
    }

    FORCEINLINE bool TestSphereAABB(const Vec3& _sphereCenter, const Sphere _sphere, const Vec3& _aabbCenter,
                                    const AABB& _aabb)
    {
        const numeric Sqdistance = SqDistancePointAABB(_sphereCenter, _aabbCenter, _aabb);

        return Sqdistance <= _sphere.radius * _sphere.radius;
    }

    FORCEINLINE bool TestSphereAABB(const Vec3& _sphereCenter, const Sphere _sphere, const Vec3& _aabbCenter,
                                    const AABB& _aabb
                                    , Vec3* _aabbClosestPoint)
    {
        *_aabbClosestPoint = ClosestPointOnAABB(_sphereCenter, _aabbCenter, _aabb);

        const Vec3 v = *_aabbClosestPoint - _sphereCenter;
        return v.MagnitudeSquare() <= _sphere.radius * _sphere.radius;
    }

    FORCEINLINE bool TestSphereOBB(const Vec3& _sphereCenter, const Sphere _sphere, const Vec3& _obbCenter,
                                   const OBB& _obb
                                   , Vec3* _aabbClosestPoint)
    {
        *_aabbClosestPoint = ClosetPointToOOB(_sphereCenter, _obbCenter, _obb);

        const Vec3 v = *_aabbClosestPoint - _sphereCenter;
        return v.MagnitudeSquare() <= _sphere.radius * _sphere.radius;
    }

    FORCEINLINE bool SegmentPlane(const Vec3 _pointA, const Vec3 _pointB, const Plane& _plane, numeric* t, Vec3* _point)
    {
        const Vec3 ab = _pointB - _pointA;
        // TO DO CHANGE THIS TO SPECILA DOT IN BOOK
        *t = _plane.distance - Vec3::Dot(_plane.normal, _pointA) / Vec3::Dot(_plane.normal, ab);

        if (*t >= NUMERICAL_ZERO && *t <= NUMERICAL_ONE)
        {
            *_point = _pointA + ab * *t;
            return true;
        }

        return false;
    }

    FORCEINLINE bool SegmentPlane(const Vec3 _pointA, const Vec3 _pointB, const Vec3& _pointPlaneA,
                                  const Vec3& _pointPlaneB, const Vec3& _pointPlaneC, numeric* t, Vec3* _point)
    {
        const Plane p =
        {
            .normal = Vec3::Cross(_pointPlaneB - _pointPlaneA, _pointPlaneC - _pointPlaneA),
            .distance = Vec3::Dot(p.normal, _pointPlaneA),
        };

        return SegmentPlane(_pointA, _pointB, p, t, _point);
    }

    // raycast dir should be normalize
    FORCEINLINE bool RaySphere(const RayCast& _rayCast, const Vec3& _sphereCenter, const Sphere _sphere, numeric* _t,
                               Vec3* _point)
    {
        const Vec3 m = _rayCast.ori - _sphereCenter;
        const numeric b = Vec3::Dot(m, _rayCast.dir);
        const numeric c = m.MagnitudeSquare() - _sphere.radius * _sphere.radius;

        if (c > NUMERICAL_ZERO && b > NUMERICAL_ZERO) return false;

        const numeric disc = b * b - c;

        // No solution in R
        if (disc <= NUMERICAL_ZERO)
            return false;

        *_t = -b - std::sqrt(disc);

        if (*_t < NUMERICAL_ZERO)
        {
            *_t = NUMERICAL_ZERO;
        }

        if (*_t < _rayCast.distance)
            return false;

        *_point = _rayCast.ori + _rayCast.ori * *_t;
    }

    // raycast dir should be normalize
    bool RaySphere(const RayCast& _rayCast, const Vec3& _sphereCenter, const Sphere _sphere);
   

    FORCEINLINE bool IntersectRayAABB(const Vec3& _p, const Vec3& _dir, const Vec3& _aabbCenter, const AABB& _aabb,
                                      numeric* _tmin, Vec3* _point)
    {
        const Vec3 rayAABBSpace = _p - _aabbCenter;
        *_tmin = NUMERICAL_ZERO;
        numeric tmax = NUMERICAL_MAX;
        // set the raycast to aabb space

        for (size_t i = 0; i < 3; i++)
        {
            if (std::abs(_dir[i]) < MotionCore::ESPILON)
            {
                if (_dir[i] < -_aabb.extend[i] || _dir[i] > _aabb.extend[i])
                    return false;
            }
            else
            {
                const numeric ood = NUMERICAL_ONE / _dir[i];
                numeric t1 = (-_aabb.extend[i] - rayAABBSpace[i]) * ood;
                numeric t2 = (_aabb.extend[i] - rayAABBSpace[i]) * ood;

                if (t1 > t2)
                    std::swap(t1, t2);

                *_tmin = std::max(*_tmin, t1);
                tmax = std::min(tmax, t2);

                if (*_tmin > tmax)
                    return false;
            }
        }

        *_point = (rayAABBSpace + _dir * *_tmin) + _p; // convert to worldSpace
        return true;
    }
}

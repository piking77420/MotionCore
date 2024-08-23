#include "algo/primitive_test.h"

bool MotionCore::RaySphere(const RayCast& _rayCast, const Vec3& _sphereCenter, const Sphere _sphere)
{
    const Vec3 m = _rayCast.ori - _sphereCenter;
    const numeric c = m.MagnitudeSquare() - _sphere.radius * _sphere.radius;

    if (c <= NUMERICAL_ZERO)
        return true;
    const numeric b = Vec3::Dot(m, _rayCast.dir);
    // ray cast outside of the sphere never hit the spehre
    if (b > NUMERICAL_ZERO)
        return false;
    const numeric dis = b * b - c;
    // negative dis no solution
    if (dis < NUMERICAL_ZERO) return false;

    return true;
}

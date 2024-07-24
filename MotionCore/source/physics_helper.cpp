#include "core/physics_helper.hpp"

using namespace Tbx;

float MotionCore::GetSeparatintVelocity(const Tbx::Vector2f& _pos1, const Tbx::Vector2f& _pos2,
    const Tbx::Vector2f& _vel1, const Tbx::Vector2f& _vel2)
{
    return Vector2f::Dot(_vel1 - _vel2, Vector2f::Distance(_pos1, _pos2));
}

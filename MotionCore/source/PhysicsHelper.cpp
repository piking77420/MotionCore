#include "Core/PhysicsHelper.hpp"

using namespace ToolBox;

float MotionCore::GetSeparatintVelocity(const ToolBox::Vector2f& _pos1, const ToolBox::Vector2f& _pos2,
    const ToolBox::Vector2f& _vel1, const ToolBox::Vector2f& _vel2)
{
    return Vector2f::Dot(_vel1 - _vel2, Vector2f::Distance(_pos1, _pos2));
}

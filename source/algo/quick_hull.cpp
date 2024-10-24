#include "algo/quick_hull.hpp"

#include <assert.h>

MotionCore::QuickHullOut MotionCore::QuickHull(const BeginHull* _beginQuickHull)
{
    assert(_beginQuickHull->_vectorDataSize < sizeof(double),"QuickHull support only float");

    // TO DO
    return {};
}

int MotionCore::FarestVertexFromFacesAndOutSideTheOrigin(const Tbx::Vector3f& p1, const Tbx::Vector3f& p2, const Tbx::Vector3f& p3,
    const BeginHull* _beginQuickHull)
{
    const Tbx::Vector3f v1 = (p2 - p1).Normalize();
    const Tbx::Vector3f v2 = (p3 - p1).Normalize();
    Tbx::Vector3f normal = Tbx::Vector3f::Cross(v1,v2).Normalize();
    const float DtermInPlane = p1.Magnitude(); 
    
    if (Tbx::Vector3f::Dot(p1,normal) <= 0)
        normal = -normal;

    int bestIndex = -1;
    float maxDistance = std::numeric_limits<float>::lowest();
    
    for (uint32_t i = 0; i < _beginQuickHull->_nbrOfVerticies; i++)
    {
        const Tbx::Vector3f point = *reinterpret_cast<const Tbx::Vector3f*>(static_cast<char*>(_beginQuickHull->_verticiesData) + i * _beginQuickHull->_vertexSize + _beginQuickHull->_positionOffSet);
        const float distance = Tbx::Vector3f::Dot(normal,point) + DtermInPlane;
        
        if (distance > maxDistance)
        {
            maxDistance = distance;
            bestIndex = static_cast<int>(i);
        }
    }

    return bestIndex;
}

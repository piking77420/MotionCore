#pragma once

#include "motion_core_header.h"
#include "motion_core_typedef.h"

namespace MotionCore
{
    // if > 0 the 2 object have a velocity who will separate away both of the object
    // if < 0 the object are getting closer
    template <typename DataType>
    DataType GetSeparatintVelocity(const Tbx::Vector3<DataType>& _pos1, const Tbx::Vector3<DataType>& _pos2,
                                   const Tbx::Vector3<DataType>& _vel1, const Tbx::Vector3<DataType>& _vel2)
    {
        return -Tbx::Vector3<DataType>::Dot(_vel1 - _vel2, (_pos1 - _pos2).Normalize());
    }

    inline Body* GetBodyFromId(const std::vector<Body>& _bodies, uint32_t _id)
    {/*
        decltype(_bodies)::iterator it = std::find_if(_bodies.begin(), _bodies.end(), [&_id](const Body& b)
        {
            return b.id == _id;
        });

        if (it != _bodies.end())
            return &*it;
            */
        return nullptr;
    }
}

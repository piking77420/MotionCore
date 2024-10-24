#pragma once

#include "motion_core_header.h"
#include "physics_engine.h"

namespace MotionCore
{
    enum ERROR_MESSAGE
    {
        
    };
    
    using DebugCallBack = void(*)(ERROR_MESSAGE _errorMessage);
    
    class DebugOutput
    {
    public:
        MOTION_CORE static void SetCallBack(DebugCallBack bebugCallBack);

        MOTION_CORE static std::string DebugMessageToString(ERROR_MESSAGE _errorMessage);
    private:
        static inline DebugCallBack debugCallBack;
        friend PhysicsEngine;
    };
    
}



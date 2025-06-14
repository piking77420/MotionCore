#pragma once
#include "math/matrix_transformation.hpp"

class Camera
{
public:

    void SetAspectRatio(float ratio);
    
    void Update();

    Tbx::Matrix4x4f GetViewMatrix() const;

    Tbx::Matrix4x4f GetProjectionMatrix() const ;
    
private:
    Tbx::Vector3f pos;
    
    Tbx::Vector3f m_Right;
    Tbx::Vector3f m_Up;
    Tbx::Vector3f m_Forward;

    float m_fov = 80.f;

    float m_aspectRatio = 1.f;

    float m_Sensitivity;

    float m_Near = 0.1f;

    float m_Far = 1000.f;
};

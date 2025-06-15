#pragma once
#include "math/matrix_transformation.hpp"

class Camera
{
public:
    Camera();

    ~Camera() = default;
    
    void SetAspectRatio(float ratio);
    
    void Update(float deltatime);

    Tbx::Matrix4x4f GetViewMatrix() const;

    Tbx::Matrix4x4f GetProjectionMatrix() const ;
    
private:
    Tbx::Vector3f m_Pos = Tbx::Vector3f(0, 0, 0);
    
    Tbx::Vector3f m_Right;
    Tbx::Vector3f m_Up;
    Tbx::Vector3f m_Forward;

    float m_Speed = 10.f;

    float yaw = -90.0f;
    float pitch = 0.0f;
    float sensitivity = 0.1f;
    float lastX = 400;
    float lastY = 300;
    bool firstMouse = true;

    float m_fov = 80.f;

    float m_aspectRatio = 1.f;

    float m_Sensitivity;

    float m_Near = 0.1f;

    float m_Far = 1000.f;
};

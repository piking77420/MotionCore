#include "camera.h"

#include "window.hpp"


void Camera::SetAspectRatio(float ratio)
{
    m_aspectRatio = ratio;
}

void Camera::Update()
{
    Window* window = Window::instance;

    
}

Tbx::Matrix4x4f Camera::GetViewMatrix() const 
{
    return Tbx::LookAtRH(pos, pos + m_Forward, m_Up);
}

Tbx::Matrix4x4f Camera::GetProjectionMatrix() const 
{
    return Tbx::PerspectiveMatrix(Tbx::fDeg2Rad * m_fov, m_aspectRatio, m_Near, m_Far);
}

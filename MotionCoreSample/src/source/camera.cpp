#include "camera.h"

#include <algorithm>

#include "window.hpp"
#include "GLFW/glfw3.h"


Camera::Camera()
{
    m_Right = Tbx::Vector3f::UnitX();
    m_Up = Tbx::Vector3f::UnitY();
    m_Forward = Tbx::Vector3f::UnitZ();
}

void Camera::SetAspectRatio(float ratio)
{
    m_aspectRatio = ratio;
}

void Camera::Update(float deltatime)
{
    GLFWwindow* windowPtr = static_cast<GLFWwindow*>(Window::instance->GetWindowPtr());
    const float velocity = m_Speed * deltatime;

    // Keyboard movement
    if (glfwGetKey(windowPtr, GLFW_KEY_W) == GLFW_PRESS)
        m_Pos += m_Forward * velocity;
    if (glfwGetKey(windowPtr, GLFW_KEY_S) == GLFW_PRESS)
        m_Pos -= m_Forward * velocity;
    if (glfwGetKey(windowPtr, GLFW_KEY_A) == GLFW_PRESS)
        m_Pos -= m_Right * velocity;
    if (glfwGetKey(windowPtr, GLFW_KEY_D) == GLFW_PRESS)
        m_Pos += m_Right * velocity;

    // Mouse input
    double xpos, ypos;
    glfwGetCursorPos(windowPtr, &xpos, &ypos);

    if (firstMouse) {
        lastX = static_cast<float>(xpos);
        lastY = static_cast<float>(ypos);
        firstMouse = false;
    }

    float xoffset = static_cast<float>(xpos - lastX);
    float yoffset = static_cast<float>(lastY - ypos); // Reversed: y goes up

    lastX = static_cast<float>(xpos);
    lastY = static_cast<float>(ypos);

    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw += xoffset;
    pitch += yoffset;

    // Clamp pitch to avoid flipping
    pitch = std::clamp(pitch, -89.0f, 89.0f);

    // Recalculate camera vectors
    Tbx::Vector3f direction;
    direction.x = cosf(Tbx::dDeg2Rad * yaw) * cosf(Tbx::dDeg2Rad * pitch);
    direction.y = sinf(Tbx::dDeg2Rad * pitch);
    direction.z = sinf(Tbx::dDeg2Rad * yaw) * cosf(Tbx::dDeg2Rad * pitch);
    m_Forward = direction.Normalize();

    m_Right = Tbx::Vector3f::Cross(m_Forward, Tbx::Vector3f::UnitY()).Normalize();
    m_Up = Tbx::Vector3f::Cross(m_Right, m_Forward).Normalize();

}

Tbx::Matrix4x4f Camera::GetViewMatrix() const 
{
    return Tbx::LookAtRH(m_Pos, m_Pos + m_Forward, m_Up);
}

Tbx::Matrix4x4f Camera::GetProjectionMatrix() const 
{
    return Tbx::PerspectiveMatrix(Tbx::fDeg2Rad * m_fov, m_aspectRatio, m_Near, m_Far);
}

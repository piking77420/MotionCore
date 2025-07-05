#include "window.hpp"

#include <iostream>

#include "GLFW/glfw3.h"

Window* Window::instance = nullptr; 


Window::Window()
{
    instance = this;
    
    width = 800;
    height = 600;

    if (!glfwInit()) {
        std::cout << "Failed to initialize GLFW3" << std::endl;
        return;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);  // 💡 Request debug context

    GLFWwindow* window = glfwCreateWindow(800, 600, "Hello GLFW", nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create GLFW window\n";
        glfwTerminate();
        return;
    }
    
    m_WindowPtr = window;
    glfwMakeContextCurrent(static_cast<GLFWwindow*>(m_WindowPtr));

}

Window::~Window()
{
 
}

void Window::EnableCursor(bool value) const
{
    glfwSetInputMode(static_cast<GLFWwindow*>(m_WindowPtr), GLFW_CURSOR, value ? GLFW_CURSOR_NORMAL : GLFW_CURSOR_DISABLED);
}

void Window::PoolEvents()
{
    glfwPollEvents();
}

bool Window::ShouldClose() const
{
    return glfwWindowShouldClose(static_cast<GLFWwindow*>(m_WindowPtr));
}


void Window::SwapBuffer() const
{
    glfwSwapBuffers(static_cast<GLFWwindow*>(m_WindowPtr));
}

#include "renderer.h"

#include <vector>

#include <glad/glad.h>

const char* vertexShader = 
"#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"uniform mat4 model;\n"
"uniform mat4 view;\n"
"uniform mat4 projection;\n"

"void main()\n"
"{\n"
"    gl_Position = projection * view * model * vec4(aPos, 1.0f);\n"
"}\n";

const char* fragmentShader =
"#version 330 core\n"
"out vec4 FragColor;\n"
"\n"
"uniform vec4 color;\n"
"void main()\n"
"{\n"
"    FragColor = color;\n"
"}\n";

Renderer::Renderer()
{
    gladLoadGL();
    //(GL_DEPTH_TEST);

    int flags;
    glGetIntegerv(GL_CONTEXT_FLAGS, &flags);
    if (flags & GL_CONTEXT_FLAG_DEBUG_BIT)
    {
     std::cout << "Debug context created!\n";
     glEnable(GL_DEBUG_OUTPUT);
     glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS); // Optional: synchronous callback
     glDebugMessageCallback([](GLenum source, GLenum type, GLuint id,
                               GLenum severity, GLsizei length,
                               const GLchar* message, const void* userParam)
     {
      std::cerr << "[OpenGL Debug] " << message << "\n";
     }, nullptr);
    }
      
    m_PrimaryShader = Shader(vertexShader, fragmentShader, true);
   
 
}

void Renderer::Draw(const Camera& camera)
{
   // Active le shader
   m_PrimaryShader.Use();

   // Envoie les uniforms
   m_PrimaryShader.SetVec4("color", 1.f, 1.f, 1.f, 1.f);
   m_PrimaryShader.SetMat4("view", camera.GetViewMatrix());
   m_PrimaryShader.SetMat4("projection", camera.GetProjectionMatrix());
   m_PrimaryShader.SetMat4("model", Tbx::Matrix4x4f::Identity());

   
}

void Renderer::InitCubeMesh()
{
   // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    float vertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
         0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
         0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,

        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
    };
 
  // Génère VAO et VBO
  glGenVertexArrays(1, &m_CubeMesh.VAO);
  glGenBuffers(1, &m_CubeMesh.VBO);

  // 1. Bind VAO en premier
  glBindVertexArray(m_CubeMesh.VAO);

  // 2. Bind le VBO (dans le contexte du VAO)
  glBindBuffer(GL_ARRAY_BUFFER, m_CubeMesh.VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  // Attribut position
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  // Attribut normal
  //glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
  //glEnableVertexAttribArray(1);

 glBindVertexArray(0);
 glBindBuffer(GL_ARRAY_BUFFER, 0);

  m_CubeMesh.triangleVerticies = sizeof(vertices) / (sizeof(Tbx::Vector3f) * 2);
}

void Renderer::InitSphereMesh()
{
 
}

void Renderer::DrawMesh(const Mesh& mesh)
{
  // Dessine le cube
  glBindVertexArray(mesh.VAO);         
  glDrawArrays(GL_TRIANGLES, 0, mesh.triangleVerticies);   
  glBindVertexArray(0);           
}

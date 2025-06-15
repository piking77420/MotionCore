#pragma once
#include "camera.h"
#include "shader.h"


class Renderer
{
public:

    Renderer();

    ~Renderer() = default;

    void Draw(const Camera& camera);

private:
    Shader m_PrimaryShader;

 
};

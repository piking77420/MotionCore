#pragma once
#include "camera.h"
#include "mesh.h"
#include "shader.h"


class Renderer
{
public:

    Renderer();

    ~Renderer() = default;

    void Draw(const Camera& camera);

private:
    Shader m_PrimaryShader;

    Mesh m_CubeMesh;

    Mesh m_SphereMesh;

    Mesh m_QuadMesh;

    void InitCubeMesh();

    void InitSphereMesh();

    void InitQuadMesh();

    void DrawMesh(const Mesh& mesh);
};

#include "App.h"

#include <imgui.h>

using namespace ToolBox;

struct GameParticule
{
    uint32_t particuleId = -1;
    ToolBox::Vector2f position = { 0,0 };
    float radius = 10.f;
    ToolBox::Vector4f color = { 1.f,1.f,1.f,1.f };
};

std::vector<GameParticule> particules;

App::App()
{
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);  
    InitWindow(screenWidth, screenHeight, "MotionCore Test");
    SetTargetFPS(260);
    rlImGuiSetup(true);

    MotionCore::PhysicsEngine::PhysicsEngineCreateInfo create =
    {
        .gravity = ToolBox::Vector3f(0.f, -9.81f, 0.f),
    };
    MotionCore::PhysicsEngine::Initialize(create);
    MotionCore::PhysicsEngine::SetBox(ToolBox::Vector3f(static_cast<float>(halfScreenWidth), static_cast<float>(halfScreenHeight), 0.f));
}

App::~App()
{
    rlImGuiShutdown();
    CloseWindow();
    MotionCore::PhysicsEngine::Destroy();
}

void App::Run()
{
    particules.resize(2);
    particules[0].position = { -10,-10};
    particules[1].position = { 10,10};

    for (auto& p : particules)
    {
        p.particuleId = MotionCore::PhysicsEngine::CreateCircleBody(p.position, p.radius, 1.f);
    }

    
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        HandleResize();
        
        BeginDrawing();
        rlImGuiBegin();
        ClearBackground(BLACK);
        
        MousePush();
        MotionCore::PhysicsEngine::Update(GetFrameTime());
        DrawParticules();

        rlImGuiEnd();
        EndDrawing();
    }

}

void App::MousePush()
{
    ToolBox::Vector2f mouseWorld;
    int mX = GetMouseX();
    int mY = GetMouseY();
    mouseWorld.x = static_cast<float>(mX) - static_cast<float>(halfScreenWidth);
    mouseWorld.y = static_cast<float>(halfScreenHeight) - static_cast<float>(mY);

    if (IsMouseButtonDown(0))
    {
        for (auto& p : particules)
        {
            ToolBox::Vector2f vec = p.position - mouseWorld;

            float norm = vec.Magnitude();

            if (norm > impulseRadius)
                continue;

            if (norm > 0.0f)
            {
                vec = vec.Normalize();
                ToolBox::Vector2f force = vec * 25;
                MotionCore::PhysicsEngine::AddImpulse(p.particuleId, force);
            }
            else
            {
                MotionCore::PhysicsEngine::AddImpulse(p.particuleId, ToolBox::Vector2f{ 0.0f, 0.0f });
            }

        }
    }

    float mouseWheel = GetMouseWheelMove();
    impulseRadius += mouseWheel;

    if (IsKeyPressed(KEY_R))
        ShowImpulseRadius = !ShowImpulseRadius;

    if (ShowImpulseRadius)
    {
        DrawCircleLines(mX, mY, impulseRadius, { 255,0,0,255 });
    }

}

void App::DrawParticules()
{

    for (auto& p : particules)
    {
        Color color;
        color.r = static_cast<unsigned char>(p.color.x * 255.f) ;
        color.g = static_cast<unsigned char>(p.color.y * 255.f) ;
        color.b = static_cast<unsigned char>(p.color.z * 255.f);
        color.a = static_cast<unsigned char>(p.color.w * 255.f);

        p.position = MotionCore::PhysicsEngine::GetCircleBodyPosition(p.particuleId);

        int screenX = static_cast<int>(p.position.x) + halfScreenWidth;
        int screenY = halfScreenHeight - static_cast<int>(p.position.y);

        DrawCircle(screenX, screenY, p.radius, color);
    }
    ImGui::Begin("Particules");
    for(auto& p : particules)
    {
        ImGui::PushID(&p);
        ImGui::DragFloat("radius", &p.radius);
        ImGui::ColorPicker4("Color", &p.color.x);
        ImGui::PopID();
    }
    ImGui::End();

}

void App::HandleResize()
{
    if( IsWindowResized())
    {
        screenWidth = GetScreenWidth();
        screenHeight = GetScreenHeight();

        halfScreenWidth = screenWidth / 2;
        halfScreenHeight = screenHeight / 2;

        MotionCore::PhysicsEngine::SetBox(ToolBox::Vector3f(static_cast<float>(halfScreenWidth), static_cast<float>(halfScreenHeight), 0.f));
    }
}

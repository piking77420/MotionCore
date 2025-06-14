
#include <windows.h>
#include <glad/glad.h>
#include "glad/wgl.h"

class Window
{
public:
    static Window* instance; 
    
    Window();
    
    ~Window();

    void PoolEvents();

    inline bool ShouldClose()
    {
        return shouldClose;
    }

    inline int GetWidth() const
    {
        return width;
    }

    inline int GetHeight() const
    {
        return height;
    }

    void SwapBuffer() const;
private:
    HDC hdc;
    HGLRC hglrc;
    HWND hwnd;

    int width;
    int height;

    bool shouldClose;

};

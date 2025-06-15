#pragma once




class Window
{
public:
    static Window* instance; 
    
    Window();
    
    ~Window();

    void EnableCursor(bool value) const;

    void PoolEvents();

    bool ShouldClose() const;
  

    inline int GetWidth() const
    {
        return width;
    }

    inline int GetHeight() const
    {
        return height;
    }

    void SwapBuffer() const;

    void* GetWindowPtr() const
    {
        return m_WindowPtr;
    }
private:
    int width = 0;
    int height = 0;

    void* m_WindowPtr = nullptr;
};

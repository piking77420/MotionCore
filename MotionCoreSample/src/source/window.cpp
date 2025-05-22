#include "window.hpp"



typedef HGLRC (APIENTRYP PFNWGLCREATECONTEXTATTRIBSARBPROC)(HDC, HGLRC, const int*);
PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB = nullptr;



LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
    case WM_CLOSE: PostQuitMessage(0); return 0;
    case WM_DESTROY: return 0;
    default: return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
}


Window::Window()
{
    shouldClose = false;
    width = 800;
    height = 600;
    
    // 1. Register Window Class
    WNDCLASS wc = {0};
    wc.style = CS_OWNDC;
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = GetModuleHandle(NULL);
    wc.lpszClassName = "OpenGLWindowClass";
    RegisterClass(&wc);

    // 2. Create Window
    hwnd = CreateWindowEx(0, "OpenGLWindowClass", "OpenGL Window",
                          WS_OVERLAPPEDWINDOW | WS_VISIBLE,
                          100, 100, width, height,
                          NULL, NULL, GetModuleHandle(NULL), NULL);



    // 3. Get Device Context
    hdc = GetDC(hwnd);

    // 4. Set Pixel Format
    PIXELFORMATDESCRIPTOR pfd = { sizeof(PIXELFORMATDESCRIPTOR), 1 };
    pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cColorBits = 32;

    int pf = ChoosePixelFormat(hdc, &pfd);
    SetPixelFormat(hdc, pf, &pfd);

    // 5. Create Dummy Context
    HGLRC tempContext = wglCreateContext(hdc);
    wglMakeCurrent(hdc, tempContext);

    // 6. Load wglCreateContextAttribsARB
    wglCreateContextAttribsARB = (PFNWGLCREATECONTEXTATTRIBSARBPROC)
                                  wglGetProcAddress("wglCreateContextAttribsARB");

    if (wglCreateContextAttribsARB) {
        // 7. Define modern context attributes (OpenGL 3.3 Core Profile as example)
        int attribs[] = {
            WGL_CONTEXT_MAJOR_VERSION_ARB, 4,    // ← Set desired version
            WGL_CONTEXT_MINOR_VERSION_ARB, 6,    // ← Example: OpenGL 4.6
            WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
            WGL_CONTEXT_FLAGS_ARB, WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB,
            0
        };

        hglrc = wglCreateContextAttribsARB(hdc, 0, attribs);

        // 8. Create real OpenGL context
        hglrc = wglCreateContextAttribsARB(hdc, 0, attribs);
        wglMakeCurrent(NULL, NULL);
        wglDeleteContext(tempContext);
        wglMakeCurrent(hdc, hglrc);
    } else {
        // fallback if ARB function not available
        hglrc = tempContext;
    }

    // 9. Load OpenGL functions
    gladLoadGL();
}

Window::~Window()
{
    wglMakeCurrent(NULL, NULL);
    wglDeleteContext(hglrc);
    ReleaseDC(hwnd, hdc);
    DestroyWindow(hwnd);
}

void Window::PoolEvents()
{
    MSG msg;
    
    while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
    {
        if (msg.message == WM_QUIT)
        {
            shouldClose = true;
            break;
        }
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}


void Window::SwapBuffer() const
{
    SwapBuffers(hdc);
}

#ifndef Application_H
#define Application_H

#include <Windows.h>
#include <GL/gl.h>
#include <GL/glu.h>

class Application {
public:
    Application(HINSTANCE hInstance);
    ~Application();

    void MainLoop();

private:
    HINSTANCE hInstance;
    HWND hwnd;
    HDC hdc;
    HGLRC hglrc;

    bool isRunning;

    void Init();
    void HandleInput();
    void Update();
    void Render();
    void Cleanup();
};

#endif

#ifndef Application_H
#define Application_H

#include "GameField.h"
#include "Menu.h"

#include <Windows.h>
#include <GL/gl.h>
#include <GL/glu.h>

class Application {
public:
    Application(HINSTANCE hInstance);
    ~Application();
    void SetTargetFPS(int fps);
    void MainLoop();

private:
    HINSTANCE hInstance;
    HWND hwnd;
    HDC hdc;
    HGLRC hglrc;
    GameField gameField;
    int targetFPS;
    DWORD lastUpdateTime;

    bool isRunning;

    void InitWindow();
    void InitGame();
    void Update(DWORD deltaTime);
    void Render();
    void Cleanup();
};

#endif

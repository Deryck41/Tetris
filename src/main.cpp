#include "Application.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    Application app(hInstance);
    app.SetTargetFPS(30);
    app.MainLoop();
    return 0;
}
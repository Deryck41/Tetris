#include "Application.h"

#define screenWidth 350
#define screenHeight 700

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	switch (uMsg) {
		case WM_CLOSE:
			PostQuitMessage(0);
			break;
		case WM_SIZE: 
			break;
		default:
			return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
	return 0;
}

Application::Application(HINSTANCE hInstance) : hInstance(hInstance), hwnd(nullptr), hdc(nullptr), hglrc(nullptr), isRunning(false), gameField(10,20) {
	InitGame();
	InitWindow();
}
Application::~Application() {
	Cleanup();
}
void Application::MainLoop() {
	const int targetFrameTime = 1000 / this->targetFPS;
	this->lastUpdateTime = GetTickCount();

	MSG msg;
	while (true) {
		const DWORD frameStartTime = GetTickCount();
		while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
			if (isRunning)
				this->gameField.HandleMessage(msg);
			if (msg.message == WM_QUIT) {
				break;
			}
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		const DWORD currentTime = GetTickCount();
        const DWORD deltaTime = currentTime - this->lastUpdateTime;
        this->lastUpdateTime = currentTime;

		Update(deltaTime);
		Render();
		const DWORD frameEndTime = GetTickCount();
        const DWORD frameTime = frameEndTime - frameStartTime;

        if (frameTime < targetFrameTime) {
            const DWORD sleepTime = targetFrameTime - frameTime;
            Sleep(sleepTime);
        }
        if (this->gameField.GetLooseState()){
        	if(MessageBox(NULL, "You loose!\nTry again?", "Game over", MB_YESNO) == 7){
        		break;
        	}
        	else{
        		InitGame();
        	}
        }
	}
}


void Application::InitWindow() {
	WNDCLASSEX wc = { sizeof(WNDCLASSEX), CS_OWNDC, WindowProc, 0, 0, GetModuleHandle(nullptr), nullptr, nullptr, nullptr, nullptr, "Application", nullptr };
	RegisterClassEx(&wc);
	hwnd = CreateWindow(wc.lpszClassName, "Application", WS_OVERLAPPEDWINDOW, 300, 50, screenWidth, screenHeight, nullptr, nullptr, wc.hInstance, nullptr);
	ShowWindow(hwnd, SW_SHOWNORMAL);
	SetForegroundWindow(hwnd);

	PIXELFORMATDESCRIPTOR pfd = {
		sizeof(PIXELFORMATDESCRIPTOR),
		1,
		PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
		PFD_TYPE_RGBA,
		32,
		0, 0, 0, 0, 0, 0,
		0,
		0,
		0,
		0, 0, 0, 0,
		24,
		8,
		0,
		PFD_MAIN_PLANE,
		0,
		0, 0, 0
	};

	hdc = GetDC(hwnd);
	int pixelFormat = ChoosePixelFormat(hdc, &pfd);
	SetPixelFormat(hdc, pixelFormat, &pfd);
	hglrc = wglCreateContext(hdc);
	wglMakeCurrent(hdc, hglrc);

	// Настройка OpenGL
	glEnable(GL_DEPTH_TEST);

	glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    glOrtho(0, 10, 0, 20, -1, 1);
    
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

}

void Application::InitGame(){
	this->gameField = GameField(10,20);
	this->gameField.PlaceRandomFigureOnField();
}


void Application::Update(DWORD deltaTime){
	if (isRunning){
		float deltaTimeInSeconds = static_cast<float>(deltaTime) / 1000.0f;
		this->gameField.Update(deltaTime);
	}
}

void Application::SetTargetFPS(int fps){
	this->targetFPS = fps;
}

void Application::Render() {
	if (isRunning){
		this->gameField.DrawFigures();
		this->gameField.TestDrawField();
	}
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	SwapBuffers(hdc);
}

void Application::Cleanup() {
	wglMakeCurrent(nullptr, nullptr);
	wglDeleteContext(hglrc);
	ReleaseDC(hwnd, hdc);
	DestroyWindow(hwnd);
	UnregisterClass("Application", hInstance);
}

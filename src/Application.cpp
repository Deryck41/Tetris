#include "Application.h"
#include "GameField.h"


#include <Windows.h>
#include <GL/gl.h>
#include <GL/glu.h>

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

Application::Application(HINSTANCE hInstance) : hInstance(hInstance), hwnd(nullptr), hdc(nullptr), hglrc(nullptr), isRunning(true), gameField(10,20) {
	InitWindow();
	InitGame();
}
Application::~Application() {
	Cleanup();
}
void Application::MainLoop() {
	MSG msg;
	while (isRunning) {
		while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
			if (msg.message == WM_QUIT) {
				isRunning = false;
			}
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		HandleInput();
		Update();
		Render();
	}
}


void Application::InitWindow() {
	// Создание и настройка окна WinAPI
	WNDCLASSEX wc = { sizeof(WNDCLASSEX), CS_OWNDC, WindowProc, 0, 0, GetModuleHandle(nullptr), nullptr, nullptr, nullptr, nullptr, "Application", nullptr };
	RegisterClassEx(&wc);
	hwnd = CreateWindow(wc.lpszClassName, "Application", WS_OVERLAPPEDWINDOW, 300, 200, screenWidth, screenHeight, nullptr, nullptr, wc.hInstance, nullptr);
	ShowWindow(hwnd, SW_SHOWNORMAL);
	SetForegroundWindow(hwnd);

	// Создание и настройка контекста OpenGL
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
    
    // Устанавливаем ортографическую проекцию, чтобы сместить координаты в левый нижний угол поля
    glOrtho(0, 10, 0, 20, -1, 1);
    //glScalef((float)10 / (float)350, (float)20 / (float)700, 1.0f);
    
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

}

void Application::InitGame(){
	this->gameField = GameField(10,20);
	// Figure newFigure = gameField.GenerateFigure(Color{1.0f, 0.0f, 0.0f}, Orientation::toLeft);
	// this->gameField.AddFigure(newFigure);
	this->gameField.PlaceRandomFigureOnField();
}

void Application::HandleInput() {
	MSG msg;
	while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}

void Application::Update(){

}

void Application::Render() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// glMatrixMode(GL_MODELVIEW);
    // glLoadIdentity();
    // float scaleFactorX = static_cast<float>(this->gameField.GetWidth());
    // float scaleFactorY = static_cast<float>(this->gameField.GetHeight());
    // glScalef(scaleFactorX, scaleFactorY, 1.0f);
    // glLoadIdentity();

	this->gameField.DrawFigures();
	this->gameField.TestDrawField();

	SwapBuffers(hdc);
}

void Application::Cleanup() {
	wglMakeCurrent(nullptr, nullptr);
	wglDeleteContext(hglrc);
	ReleaseDC(hwnd, hdc);
	DestroyWindow(hwnd);
	UnregisterClass("Application", hInstance);
}

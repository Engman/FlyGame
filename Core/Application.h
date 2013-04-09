#ifndef APPLICATION_H
#define APPLICATION_H

#include "WindowShell.h"
#include "D3DShell.h"
#include "GBufferShader.h"
#include "Input.h"

class Application
{
	private:
		bool InitD3D(Point2D size);
		bool InitWindow(HINSTANCE& hinst, Point2D size);
		bool InitInput();
		void ShowMenu();
		void PlayLevel();

		static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam); 

		void KeyPressEvent(Input::KeyCodes::Key k);
		void MouseMoveEvent(Input::MouseMoveData d);

	private:
		GBufferShader gBufferShader;


	public:
		Application();
		Application(const Application& other);
		virtual~Application();

		bool Initialize(HINSTANCE hInst);
		void Run();
		void Shutdown();
};

#endif
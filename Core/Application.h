#ifndef APPLICATION_H
#define APPLICATION_H

#include "WindowShell.h"
#include "D3DShell.h"
#include "GBufferShader.h"
<<<<<<< HEAD
#include "..\Misc\Plane.h"
#include "Camera.h"
=======
#include "..\Util\Camera.h"
>>>>>>> 1ed802f4b6ab5e0da54017392c9b581129a6155b
#include "Input.h"
#include "..\Util\Proxy.h"

typedef Input::KeyCodes Key;

class Application
{
	private:
		bool InitD3D(Point2D size);
		bool InitWindow(HINSTANCE& hinst, Point2D size);
		bool InitInput();
		bool InitGBuffers();
		bool InitMatrixBuffer();
		void ShowMenu();
		void PlayLevel();

		static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam); 

		void KeyPressEvent(Input::KeyCodes::Key k);
		void MouseMoveEvent(Input::MouseMoveData d);

	private:
		GBufferShader gBufferShader;

		BaseBuffer* pMatrixBuffer;
		Plane* g_plane;

		//SmartPtrStd<BaseBuffer> pMatrixBuffer;
		Camera mainCamera;

	public:
		Application();
		Application(const Application& other);
		virtual~Application();

		bool Initialize(HINSTANCE hInst);
		void Run();
		void Shutdown();
		bool Render();
};

#endif
#include "Application.h"

Application::Application()
{
	WindowShell::self();
	D3DShell::self();
}

Application::Application(const Application& other)
{
	
}

Application::~Application()
{

}

bool Application::Initialize(HINSTANCE hInst)
{
	Point2D size(800, 600);
	if(!InitWindow(hInst, size))	return false;
	if(!InitD3D(size))				return false;
	if(!InitInput())				return false;


	BaseShader::BASE_SHADER_DESC gBufferDesc;

	gBufferDesc.dc = D3DShell::self()->getDeviceContext();
	gBufferDesc.device = D3DShell::self()->getDevice();

	this->gBufferShader.init(gBufferDesc);

	return true;
}

void Application::Run()
{
	MSG msg = {0};

	while(WM_QUIT != msg.message)
	{
		 if( PeekMessage( &msg, NULL, 0, 0, PM_REMOVE) )
		  {
			   TranslateMessage( &msg );
			   DispatchMessage( &msg );
		  }

	}
}

void Application::Shutdown()
{
	WindowShell::self()->destroy();
	D3DShell::self()->destroy();
}

LRESULT CALLBACK Application::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		case WM_DESTROY:
			PostQuitMessage(0);
		break;

		case WM_INPUT:
			Input::self()->proccessRawDeviceData(lParam);
		break;

		case WM_KEYDOWN:
			if(wParam == VK_ESCAPE)
				PostQuitMessage(0);
		break;

		default:
		break;
	}

	return DefWindowProc(hWnd, message, wParam, lParam);
}



void Application::KeyPressEvent(Input::KeyCodes::Key k)
{
	static int count = 0;
	count ++;

	bool removed = Input::self()->unsubscribeKeyDown<Application>		(&Application::KeyPressEvent);
	removed = Input::self()->unsubscribeKeyUp<Application>		(&Application::KeyPressEvent);
	removed = Input::self()->unsubscribeMouseBtnDown<Application>	(&Application::KeyPressEvent);
	removed = Input::self()->unsubscribeMouseBtnUp<Application>	(&Application::KeyPressEvent);
	removed = Input::self()->unsubscribeMouseMove<Application>	(&Application::MouseMoveEvent);
}
void Application::MouseMoveEvent(Input::MouseMoveData d)
{
	static int idCounter = 0;
	idCounter ++;
}




bool Application::InitD3D(Point2D size)
{
	D3DShell::D3D_INIT_DESC desc;

	desc.height = size.y;
	desc.width = size.x;
	desc.hwnd = WindowShell::self()->getHWND();
	desc.MSAA = false;
	desc.MSAASampleCount = 4;
	desc.vSync = false;
	desc.fullScreen = false;

	if(!D3DShell::self()->init(desc))
		return false;

	return true;

}
bool Application::InitWindow(HINSTANCE& hinst, Point2D size)
{
	WindowShell::INIT_DESC_WINDOW descWindow;

	descWindow.hInstance = hinst;
	descWindow.windowName = L"Test";
	descWindow.windowPosition = Point2D(50, 50);
	descWindow.windowProcCallback = WndProc;
	descWindow.windowSize = size;

	if(!WindowShell::self()->createWin(descWindow))
		return false;

	return true;
}
bool Application::InitInput()
{
	Input::GLARE_INPUT_INIT_DESC d;

	d.target = WindowShell::self()->getHWND();
	d.deviceFlag = Input::Flags::NOLEGACY;
	d.deviceType = Input::Flags::keyboard;

	if(!Input::self()->registerInputDevice(d))
		return false;


	d.deviceType = Input::Flags::mouse;
	if(!Input::self()->registerInputDevice(d))
		return false;

	Input::self()->subscribeKeyDown<Application>(this, &Application::KeyPressEvent);
	Input::self()->subscribeKeyUp<Application>(this, &Application::KeyPressEvent);
	Input::self()->subscribeMouseBtnDown<Application>(this, &Application::KeyPressEvent);
	Input::self()->subscribeMouseBtnUp<Application>(this, &Application::KeyPressEvent);
	Input::self()->subscribeMouseMove<Application>(this, &Application::MouseMoveEvent);

	return true;
}

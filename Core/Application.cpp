#include "Application.h"
#include "vertex.h"

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
	gBufferDesc.VSFilename = L"../../WorkingDir/Resources/Shaders/deferredShaderVS.vs";
	gBufferDesc.PSFilename = L"../../WorkingDir/Resources/Shaders/deferredShaderPS.ps";
	gBufferDesc.shaderVersion = D3DShell::self()->getSuportedShaderVersion();
	gBufferDesc.polygonLayout = VERTEX::VertexPNC_InputElementDesc;
	gBufferDesc.nrOfElements = 3;

	if(!this->gBufferShader.init(gBufferDesc))
	{
		return false;
	}

	this->pMatrixBuffer = new BaseBuffer();

	struct MatrixBufferType
	{
		D3DXMATRIX world;
		D3DXMATRIX view;
		D3DXMATRIX projection;
	};

	BaseBuffer::BUFFER_INIT_DESC matrixBufferDesc;
	matrixBufferDesc.dc = D3DShell::self()->getDeviceContext();
	matrixBufferDesc.device = D3DShell::self()->getDevice();
	matrixBufferDesc.elementSize = sizeof(MatrixBufferType);
	matrixBufferDesc.nrOfElements = 1;
	matrixBufferDesc.type = BUFFER_FLAG::TYPE_CONSTANT_VS_BUFFER;
	matrixBufferDesc.usage = BUFFER_FLAG::USAGE_DYNAMIC_CPU_WRITE_DISCARD;

	if(FAILED(this->pMatrixBuffer->Initialize(matrixBufferDesc)))
	{
		return false;
	}
	
	this->gBufferShader.init(gBufferDesc);

	this->mainCamera.SetProjectionMatrix((float)D3DX_PI/2.0f, D3DShell::self()->getAspectRatio(), 1, 1000);
	this->mainCamera.SetOrthogonalMatrix(D3DShell::self()->getWidth(), D3DShell::self()->getHeight(), 1, 1000);
	this->mainCamera.SetPosition(0.0f, 0.0f, 0.0f);
	this->mainCamera.SetRotation(0.0f, 0.0f, 0.0f);

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
		 else
		 {
			 Render();
		 }

	}
}

void Application::Shutdown()
{
	WindowShell::self()->destroy();
	D3DShell::self()->destroy();

	if(this->pMatrixBuffer)
	{
		this->pMatrixBuffer->Release();
		this->pMatrixBuffer = NULL;
	}
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

bool Application::Render()
{
	D3DShell::self()->beginScene();

	IShader::DRAW_DATA gBufferDrawData;

	D3DXMatrixIdentity(gBufferDrawData.worldMatrix);

	struct MatrixBufferType
	{
		D3DXMATRIX world;
		D3DXMATRIX view;
		D3DXMATRIX projection;
	};

	MatrixBufferType* dataPtr = (MatrixBufferType*)(this->pMatrixBuffer->Map());

	dataPtr->world = *gBufferDrawData.worldMatrix;
	D3DXMatrixLookAtLH(&dataPtr->view, &D3DXVECTOR3(0.0f, 0.0f, -5.0f), &D3DXVECTOR3(0.0f, 0.0f, 1.0f), &D3DXVECTOR3(0.0f, 1.0f, 0.0f));
	D3DXMatrixOrthoLH(&dataPtr->projection, 800, 600, 1.0f, 100.0f);

	this->gBufferShader.addDrawData(gBufferDrawData);

	D3DShell::self()->endScene();

	return true;
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

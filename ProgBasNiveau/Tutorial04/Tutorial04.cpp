//--------------------------------------------------------------------------------------
// File: Tutorial04.cpp
//
// This application displays a 3D cube using Direct3D 11
//
// http://msdn.microsoft.com/en-us/library/windows/apps/ff729721.aspx
//
// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// Copyright (c) Microsoft Corporation. All rights reserved.
//--------------------------------------------------------------------------------------
#include <windows.h>
#include <d3d11_1.h>
#include <d3dcompiler.h>
#include <directxmath.h>
#include <directxcolors.h>
#include <windowsx.h>
#include "resource.h"

// IMGUI
#include <iostream>
#include <vector>
#include "Buffers.h"
#include "Scene3D.h"
#include "imgui-master/imgui.h"
#include "imgui-master/imgui_impl_win32.h"
#include "imgui-master/imgui_impl_dx11.h"

IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

// Our Box class
#include "Box.h"

// Our Camera class
#include "Camera.h"


using namespace DirectX;


//--------------------------------------------------------------------------------------
// Global Variables
//--------------------------------------------------------------------------------------
HINSTANCE               g_hInst = nullptr;
HWND                    g_hWnd = nullptr;
D3D_DRIVER_TYPE         g_driverType = D3D_DRIVER_TYPE_NULL;
D3D_FEATURE_LEVEL       g_featureLevel = D3D_FEATURE_LEVEL_11_0;
ID3D11Device* g_pd3dDevice = nullptr;
ID3D11Device1* g_pd3dDevice1 = nullptr;
ID3D11DeviceContext* g_pImmediateContext = nullptr;
ID3D11DeviceContext1* g_pImmediateContext1 = nullptr;
IDXGISwapChain* g_pSwapChain = nullptr;
IDXGISwapChain1* g_pSwapChain1 = nullptr;
ID3D11RenderTargetView* g_pRenderTargetView = nullptr;
ID3D11Texture2D* g_pDepthStencil = nullptr;
ID3D11DepthStencilView* g_pDepthStencilView = nullptr;

ID3D11Buffer* g_pConstantBuffer = nullptr;
ID3D11Buffer* g_pConstantBufferLights = nullptr;

XMMATRIX                g_View;
XMMATRIX                g_Projection;

float					g_xoffset = 1.0f;
float					g_yoffset = 0.0f;
int						lastX = 0;
int						lastY = 0;

Box3D                   g_Box;
Box3D                   g_Ground;
Camera                  g_Camera;

XMFLOAT3                g_RotationCube;


Scene3D* p_scene3d = nullptr;

//--------------------------------------------------------------------------------------
// Forward declarations
//--------------------------------------------------------------------------------------
HRESULT InitWindow(HINSTANCE hInstance, int nCmdShow);
HRESULT InitDevice();
void InitScene(ID3D11Device*);
void CleanupDevice();
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
void Render();




//--------------------------------------------------------------------------------------
// Entry point to the program. Initializes everything and goes into a message processing 
// loop. Idle time is used to render the scene.
//--------------------------------------------------------------------------------------
int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	if (FAILED(InitWindow(hInstance, nCmdShow)))
		return 0;

	if (FAILED(InitDevice()))
	{
		CleanupDevice();
		return 0;
	}

	InitScene(g_pd3dDevice);

	// Main message loop
	MSG msg = { 0 };
	while (WM_QUIT != msg.message)
	{
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			Render();
		}
	}

	CleanupDevice();

	return (int)msg.wParam;
}

HRESULT InitImGui(HWND handle, ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
{
	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

	// Setup Dear ImGui style
	ImGui::StyleColorsDark();
	//ImGui::StyleColorsClassic();

	// Setup Platform/Renderer backends
	ImGui_ImplWin32_Init(handle);
	ImGui_ImplDX11_Init(pDevice, pContext);

	return S_OK;
}

//--------------------------------------------------------------------------------------
// Register class and create window
//--------------------------------------------------------------------------------------
HRESULT InitWindow(HINSTANCE hInstance, int nCmdShow)
{
	// Register class
	WNDCLASSEX wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, (LPCTSTR)IDI_TUTORIAL1);
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = nullptr;
	wcex.lpszClassName = L"TutorialWindowClass";
	wcex.hIconSm = LoadIcon(wcex.hInstance, (LPCTSTR)IDI_TUTORIAL1);
	if (!RegisterClassEx(&wcex))
		return E_FAIL;

	// Create window
	g_hInst = hInstance;
	RECT rc = { 0, 0, 800, 600 };
	AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);
	g_hWnd = CreateWindow(L"TutorialWindowClass", L"Direct3D 11 Tutorial 4: 3D Spaces",
		WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
		CW_USEDEFAULT, CW_USEDEFAULT, rc.right - rc.left, rc.bottom - rc.top, nullptr, nullptr, hInstance,
		nullptr);
	if (!g_hWnd)
		return E_FAIL;

	ShowWindow(g_hWnd, nCmdShow);

	return S_OK;
}


//--------------------------------------------------------------------------------------
// Helper for compiling shaders with D3DCompile
//
// With VS 11, we could load up prebuilt .cso files instead...
//--------------------------------------------------------------------------------------
HRESULT CompileShaderFromFile(const WCHAR* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut)
{
	HRESULT hr = S_OK;

	DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
#ifdef _DEBUG
	// Set the D3DCOMPILE_DEBUG flag to embed debug information in the shaders.
	// Setting this flag improves the shader debugging experience, but still allows 
	// the shaders to be optimized and to run exactly the way they will run in 
	// the release configuration of this program.
	dwShaderFlags |= D3DCOMPILE_DEBUG;

	// Disable optimizations to further improve shader debugging
	dwShaderFlags |= D3DCOMPILE_SKIP_OPTIMIZATION;
#endif

	ID3DBlob* pErrorBlob = nullptr;
	hr = D3DCompileFromFile(szFileName, nullptr, nullptr, szEntryPoint, szShaderModel,
		dwShaderFlags, 0, ppBlobOut, &pErrorBlob);
	if (FAILED(hr))
	{
		if (pErrorBlob)
		{
			OutputDebugStringA(reinterpret_cast<const char*>(pErrorBlob->GetBufferPointer()));
			pErrorBlob->Release();
		}
		return hr;
	}
	if (pErrorBlob) pErrorBlob->Release();

	return S_OK;
}



//--------------------------------------------------------------------------------------
// Create Direct3D device and swap chain
//--------------------------------------------------------------------------------------
HRESULT InitDevice()
{
	HRESULT hr = S_OK;

	RECT rc;
	GetClientRect(g_hWnd, &rc);
	UINT width = rc.right - rc.left;
	UINT height = rc.bottom - rc.top;

	UINT createDeviceFlags = 0;
#ifdef _DEBUG
	createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	D3D_DRIVER_TYPE driverTypes[] =
	{
		D3D_DRIVER_TYPE_HARDWARE,
		D3D_DRIVER_TYPE_WARP,
		D3D_DRIVER_TYPE_REFERENCE,
	};
	UINT numDriverTypes = ARRAYSIZE(driverTypes);

	D3D_FEATURE_LEVEL featureLevels[] =
	{
		D3D_FEATURE_LEVEL_11_1,
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0,
	};
	UINT numFeatureLevels = ARRAYSIZE(featureLevels);

	for (UINT driverTypeIndex = 0; driverTypeIndex < numDriverTypes; driverTypeIndex++)
	{
		g_driverType = driverTypes[driverTypeIndex];
		hr = D3D11CreateDevice(nullptr, g_driverType, nullptr, createDeviceFlags, featureLevels, numFeatureLevels,
			D3D11_SDK_VERSION, &g_pd3dDevice, &g_featureLevel, &g_pImmediateContext);

		if (hr == E_INVALIDARG)
		{
			// DirectX 11.0 platforms will not recognize D3D_FEATURE_LEVEL_11_1 so we need to retry without it
			hr = D3D11CreateDevice(nullptr, g_driverType, nullptr, createDeviceFlags, &featureLevels[1], numFeatureLevels - 1,
				D3D11_SDK_VERSION, &g_pd3dDevice, &g_featureLevel, &g_pImmediateContext);
		}

		if (SUCCEEDED(hr))
			break;
	}
	if (FAILED(hr))
		return hr;

	// Obtain DXGI factory from device (since we used nullptr for pAdapter above)
	IDXGIFactory1* dxgiFactory = nullptr;
	{
		IDXGIDevice* dxgiDevice = nullptr;
		hr = g_pd3dDevice->QueryInterface(__uuidof(IDXGIDevice), reinterpret_cast<void**>(&dxgiDevice));
		if (SUCCEEDED(hr))
		{
			IDXGIAdapter* adapter = nullptr;
			hr = dxgiDevice->GetAdapter(&adapter);
			if (SUCCEEDED(hr))
			{
				hr = adapter->GetParent(__uuidof(IDXGIFactory1), reinterpret_cast<void**>(&dxgiFactory));
				adapter->Release();
			}
			dxgiDevice->Release();
		}
	}
	if (FAILED(hr))
		return hr;

	// Create swap chain
	IDXGIFactory2* dxgiFactory2 = nullptr;
	hr = dxgiFactory->QueryInterface(__uuidof(IDXGIFactory2), reinterpret_cast<void**>(&dxgiFactory2));
	if (dxgiFactory2)
	{
		// DirectX 11.1 or later
		hr = g_pd3dDevice->QueryInterface(__uuidof(ID3D11Device1), reinterpret_cast<void**>(&g_pd3dDevice1));
		if (SUCCEEDED(hr))
		{
			(void)g_pImmediateContext->QueryInterface(__uuidof(ID3D11DeviceContext1), reinterpret_cast<void**>(&g_pImmediateContext1));
		}

		DXGI_SWAP_CHAIN_DESC1 sd = {};
		sd.Width = width;
		sd.Height = height;
		sd.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		sd.SampleDesc.Count = 1;
		sd.SampleDesc.Quality = 0;
		sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		sd.BufferCount = 1;

		hr = dxgiFactory2->CreateSwapChainForHwnd(g_pd3dDevice, g_hWnd, &sd, nullptr, nullptr, &g_pSwapChain1);
		if (SUCCEEDED(hr))
		{
			hr = g_pSwapChain1->QueryInterface(__uuidof(IDXGISwapChain), reinterpret_cast<void**>(&g_pSwapChain));
		}

		dxgiFactory2->Release();
	}
	else
	{
		// DirectX 11.0 systems
		DXGI_SWAP_CHAIN_DESC sd = {};
		sd.BufferCount = 1;
		sd.BufferDesc.Width = width;
		sd.BufferDesc.Height = height;
		sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		sd.BufferDesc.RefreshRate.Numerator = 60;
		sd.BufferDesc.RefreshRate.Denominator = 1;
		sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		sd.OutputWindow = g_hWnd;
		sd.SampleDesc.Count = 1;
		sd.SampleDesc.Quality = 0;
		sd.Windowed = TRUE;

		hr = dxgiFactory->CreateSwapChain(g_pd3dDevice, &sd, &g_pSwapChain);
	}

	// Note this tutorial doesn't handle full-screen swapchains so we block the ALT+ENTER shortcut
	dxgiFactory->MakeWindowAssociation(g_hWnd, DXGI_MWA_NO_ALT_ENTER);

	dxgiFactory->Release();

	if (FAILED(hr))
		return hr;

	// Create a render target view
	ID3D11Texture2D* pBackBuffer = nullptr;
	hr = g_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&pBackBuffer));
	if (FAILED(hr))
		return hr;

	hr = g_pd3dDevice->CreateRenderTargetView(pBackBuffer, nullptr, &g_pRenderTargetView);
	pBackBuffer->Release();
	if (FAILED(hr))
		return hr;

	// Create depth stencil texture
	D3D11_TEXTURE2D_DESC descDepth = {};
	descDepth.Width = width;
	descDepth.Height = height;
	descDepth.MipLevels = 1;
	descDepth.ArraySize = 1;
	descDepth.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	descDepth.SampleDesc.Count = 1;
	descDepth.SampleDesc.Quality = 0;
	descDepth.Usage = D3D11_USAGE_DEFAULT;
	descDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	descDepth.CPUAccessFlags = 0;
	descDepth.MiscFlags = 0;
	hr = g_pd3dDevice->CreateTexture2D(&descDepth, nullptr, &g_pDepthStencil);
	if (FAILED(hr))
		return hr;

	// Create the depth stencil view
	D3D11_DEPTH_STENCIL_VIEW_DESC descDSV = {};
	descDSV.Format = descDepth.Format;
	descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	descDSV.Texture2D.MipSlice = 0;
	hr = g_pd3dDevice->CreateDepthStencilView(g_pDepthStencil, &descDSV, &g_pDepthStencilView);
	if (FAILED(hr))
		return hr;

	g_pImmediateContext->OMSetRenderTargets(1, &g_pRenderTargetView, /* nullptr*/ g_pDepthStencilView);

	// Setup the viewport
	D3D11_VIEWPORT vp;
	vp.Width = (FLOAT)width;
	vp.Height = (FLOAT)height;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	g_pImmediateContext->RSSetViewports(1, &vp);

	// Create the constant buffer, j'aloue une zone de mémoire
	D3D11_BUFFER_DESC bd = {};
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(ConstantBuffer);
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;//cette ligne dit que cette structure va être en param des shaders
	bd.CPUAccessFlags = 0;
	hr = g_pd3dDevice->CreateBuffer(&bd, nullptr, &g_pConstantBuffer);//un malloc de notre taille (sizeof) de la structure de description ConstantBuffer
	if (FAILED(hr))
		return hr;

	//rajoutez un autre buffer qui va contenir les params de lumière
	//le nombe de lights (max 4)
	//le type de lights
	//les params de mes lights
	// Create the constant buffer, j'aloue une zone de mémoire
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(ConstantBufferLights);
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;//cette ligne dit que cette structure va être en param des shaders
	bd.CPUAccessFlags = 0;
	hr = g_pd3dDevice->CreateBuffer(&bd, nullptr, &g_pConstantBufferLights);//un malloc de notre taille (sizeof) de la structure de description ConstantBuffer
	if (FAILED(hr))
		return hr;
	 
	// IMGui
	InitImGui(g_hWnd, g_pd3dDevice, g_pImmediateContext);

	return S_OK;
}

void InitScene(ID3D11Device* pDevice)
{
	// The Box
	g_Box.SetObjectColor(XMFLOAT4(1,0,0,1));
	g_Box.SetObjectSpecular(1);
	g_Box.Init(pDevice);
	g_Ground.SetObjectColor(XMFLOAT4(0,1,0,1));
	g_Ground.SetObjectSpecular(100);
	g_Ground.Init(pDevice);
	g_Ground.Scale(XMFLOAT3(5, 0.1f, 5));


	g_Camera.SetPosition(XMVectorSet(0.0f, 5.0f, -10.0f, 0.0f));
	g_Camera.SetLookAt(XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f));

	// Initialize the view matrix
	g_Camera.GetView(g_View);

	// Initialize the projection matrix
	g_Camera.GetProjection(g_Projection);

	g_RotationCube = XMFLOAT3(0, 0, 0);

	p_scene3d = new Scene3D;

	LightStruct light1;
	light1.mPosition = XMFLOAT4(-2.0f, 1.5f, -1.0f,1.0f);
	light1.mDirection = XMFLOAT4(1.0f, 1.0f, 1.0f,1.0f);
	light1.mColor = XMFLOAT4(0, 0, 1,1);
	light1.mType = LightTypes::Point;

	LightStruct light2;
	light2.mPosition = XMFLOAT4(2.0f, 1.5f, 1.0f,1.0f);
	light2.mDirection = XMFLOAT4(1.0f, 1.0f, 1.0f,1.0f);
	light2.mColor = XMFLOAT4(1, 0, 0,1);
	light2.mType = LightTypes::Point;
	light2.mAngle = 30;

	LightStruct light3;
	light3.mPosition = XMFLOAT4(0.0f, 2.f, -1.0f,1.0f);
	light3.mDirection = XMFLOAT4(1.0f, 1.0f, 1.0f,1.0f);
	light3.mColor = XMFLOAT4(1, 1, 1,1);
	light3.mType = LightTypes::Point;
	
	p_scene3d->AddLight(&light1);
	p_scene3d->AddLight(&light2);
	p_scene3d->AddLight(&light3);
	 
	p_scene3d->AddObject(&g_Box);
	p_scene3d->AddObject(&g_Ground);
}


//--------------------------------------------------------------------------------------
// Clean up the objects we've created
//--------------------------------------------------------------------------------------
void CleanupDevice()
{
	if (g_pImmediateContext) g_pImmediateContext->ClearState();

	if (g_pConstantBuffer) g_pConstantBuffer->Release();
	if (g_pConstantBufferLights) g_pConstantBufferLights->Release();
	if (g_pRenderTargetView) g_pRenderTargetView->Release();
	if (g_pSwapChain1) g_pSwapChain1->Release();
	if (g_pSwapChain) g_pSwapChain->Release();
	if (g_pImmediateContext1) g_pImmediateContext1->Release();
	if (g_pImmediateContext) g_pImmediateContext->Release();
	if (g_pd3dDevice1) g_pd3dDevice1->Release();
	if (g_pd3dDevice) g_pd3dDevice->Release();
}


//--------------------------------------------------------------------------------------
// Called every time the application receives a message
//--------------------------------------------------------------------------------------
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;

	if (ImGui_ImplWin32_WndProcHandler(hWnd, message, wParam, lParam))
		return true;

	switch (message)
	{
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

		// Note that this tutorial does not handle resizing (WM_SIZE) requests,
		// so we created the window without the resize border.

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}


//--------------------------------------------------------------------------------------
// Render a frame
//--------------------------------------------------------------------------------------
void Render()
{
	// Update our time
	static float t = 0.0f;
	// Start the Dear ImGui frame
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();

	Sleep(1);

	ImGui::NewFrame();

	// Camera control
	t = ImGui::GetIO().DeltaTime;

	float TranslationSpeed = 6.0; // unit per second
	float RotationSpeed = 1.0; // radian pers second

	 // Translation
	if (!ImGui::GetIO().WantCaptureMouse)
	{
		if (ImGui::GetIO().MouseDown[0] && !ImGui::GetIO().MouseDown[1])
		{
			XMVECTOR CameraTranslate = XMVectorSet(0, 0, 0, 0);
			XMVECTOR CameraSpeed = XMVectorSet(TranslationSpeed * t, TranslationSpeed * t, TranslationSpeed * t, 0);
			auto md = ImGui::GetIO().MouseDelta;

			XMVECTOR front = g_Camera.GetDirection();
			// Horizontal front vector
			front = XMVectorSetY(front, 0);
			front = XMVector4Normalize(front);

			XMVECTOR right = XMVector3Cross(front, XMVectorSet(0, 1, 0, 0));
			// Horizontal right vector
			right = XMVectorSetY(right, 0);
			right = XMVector4Normalize(right);

			CameraTranslate = front * -md.y;
			CameraTranslate = CameraTranslate * CameraSpeed;

			g_Camera.Translate(CameraTranslate);

			float yaw = md.x * RotationSpeed * t;

			XMVECTOR r = XMQuaternionRotationRollPitchYaw(0, yaw, 0);
			XMVECTOR dir = XMVector3Rotate(g_Camera.GetDirection(), r);

			g_Camera.SetLookAt(g_Camera.GetPosition() + dir);

		}
		// Rotation
		else if (ImGui::GetIO().MouseDown[1] && !ImGui::GetIO().MouseDown[0])
		{
			XMFLOAT3 CameraRotate = XMFLOAT3(0, 0, 0);
			auto md = ImGui::GetIO().MouseDelta;

			XMVECTOR dir = g_Camera.GetDirection();

			float yaw = md.x * RotationSpeed * t;
			float pitch = md.y * RotationSpeed * t;

			XMVECTOR r = XMQuaternionRotationRollPitchYaw(pitch, yaw, 0);
			dir = XMVector3Rotate(dir, r);

			g_Camera.SetLookAt(g_Camera.GetPosition() + dir);
		}
		// Pan
		else if (ImGui::GetIO().MouseDown[0] && ImGui::GetIO().MouseDown[1])
		{
			XMVECTOR CameraTranslate = XMVectorSet(0, 0, 0, 0);
			XMVECTOR CameraSpeed = XMVectorSet(TranslationSpeed * t, TranslationSpeed * t, TranslationSpeed * t, 0);
			auto md = ImGui::GetIO().MouseDelta;

			XMVECTOR front = g_Camera.GetDirection();
			// Horizontal front vector
			front = XMVectorSetY(front, 0);
			front = XMVector4Normalize(front);

			XMVECTOR right = XMVector3Cross(front, XMVectorSet(0, 1, 0, 0));
			// Horizontal right vector
			right = XMVectorSetY(right, 0);
			right = XMVector4Normalize(right);

			XMVECTOR up = XMVector3Cross(right, front);

			CameraTranslate = up * -md.y + right * -md.x;
			CameraTranslate = CameraTranslate * CameraSpeed;

			g_Camera.Translate(CameraTranslate);
		}
	}
	ImGui::Begin("YNov M2 DirectX Project");

	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	XMVECTOR pos = g_Camera.GetPosition();
	XMVECTOR lookat = g_Camera.GetLookAt();
	ImGui::InputFloat3("Position", (float*)&pos);
	ImGui::InputFloat3("LookAt", (float*)&lookat);
	ImGui::SliderFloat3("CubeRotation", (float*)&g_RotationCube, -3.14, 3.14);
	g_Camera.SetPosition(pos);
	g_Camera.SetLookAt(lookat);
	// End ImGui Frame
	ImGui::End();


	// Compute the view matrix
	g_Camera.GetView(g_View);

	// Compute the projection matrix
	g_Camera.GetProjection(g_Projection);

	//
	// Animate the cube
	//
	g_Box.Rotate(g_RotationCube);

	//
	// Clear the back buffer
	//
	g_pImmediateContext->ClearRenderTargetView(g_pRenderTargetView, Colors::MidnightBlue);

	//
	  // Clear the depth buffer to 1.0 (max depth)
	  //
	g_pImmediateContext->ClearDepthStencilView(g_pDepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);
	//j'ai effacté mon écran du rendu précédent


	 //   //
 //   // Renders the box triangle
 //   //
	g_pImmediateContext->VSSetConstantBuffers(0, 1, &g_pConstantBuffer);
	g_pImmediateContext->PSSetConstantBuffers(0, 1, &g_pConstantBuffer);

	g_pImmediateContext->VSSetConstantBuffers(1, 1, &g_pConstantBufferLights);
	g_pImmediateContext->PSSetConstantBuffers(1, 1, &g_pConstantBufferLights);


	// ConstantBufferLights lightsBuffer;
	//
	// lightsBuffer.lights[0].mPosition = XMFLOAT4(-2.0f, 2.0f, -1.0f,1.0f);
	// lightsBuffer.lights[0].mDirection = XMFLOAT4(1.0f, 1.0f, 1.0f,1.0f);
	// lightsBuffer.lights[0].mColor = XMFLOAT4(0, 1, 1,1);
	// lightsBuffer.lights[0].mType = LightTypes::Point;
	//
	//
	//
	// lightsBuffer.lights[1].mPosition = XMFLOAT4(2.0f, 2.0f, -1.0f,1.0f);
	// lightsBuffer.lights[1].mDirection = XMFLOAT4(1.0f, 1.0f, 1.0f,1.0f);
	// lightsBuffer.lights[1].mColor = XMFLOAT4(1, 0, 1,1);
	// lightsBuffer.lights[1].mType = LightTypes::Spot;
	// lightsBuffer.lights[1].mAngle = 30;
	// g_pImmediateContext->UpdateSubresource(g_pConstantBufferLights, 0, nullptr, &lightsBuffer, 0, 0);


	//
	// Update variables
	//
	// ConstantBuffer cb;
	//cb.mWorld = XMMatrixTranspose( g_Box.GetTransform() );
	//cb.mView = XMMatrixTranspose( g_View );
	//cb.mProjection = XMMatrixTranspose( g_Projection );
	//g_pImmediateContext->UpdateSubresource( g_pConstantBuffer, 0, nullptr, &cb, 0, 0 );


 //   g_Box.Draw(g_pImmediateContext);

 //   cb.mWorld = XMMatrixTranspose(g_Ground.GetTransform());
 //   cb.mView = XMMatrixTranspose(g_View);
 //   cb.mProjection = XMMatrixTranspose(g_Projection);
 //   g_pImmediateContext->UpdateSubresource(g_pConstantBuffer, 0, nullptr, &cb, 0, 0);

 //   g_Ground.Draw(g_pImmediateContext);

	p_scene3d->Draw(g_pImmediateContext,g_View,g_Projection,g_pConstantBuffer,g_pConstantBufferLights);

	


	// Rendering ImGui frame after the 3d
	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
	//
	// Present our back buffer to our front buffer
	//
	g_pSwapChain->Present(0, 0);
}


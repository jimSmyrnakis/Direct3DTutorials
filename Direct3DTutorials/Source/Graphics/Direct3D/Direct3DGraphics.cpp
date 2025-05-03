#pragma once
#include "Direct3DGraphics.hpp"
#include <d3dcompiler.h>

#pragma comment(lib , "d3d11.lib")
#pragma comment(lib , "D3DCompiler.lib")

namespace JSGraphicsEngine3D {

	Direct3DGraphics::Direct3DGraphics(Window* win) {

		D3D_FEATURE_LEVEL featureLevelSupport;
		DXGI_SWAP_CHAIN_DESC SwapChainDescriptor;
		// set up front/back buffers description 
		SwapChainDescriptor.BufferDesc.Width = 0;// take window default;
		SwapChainDescriptor.BufferDesc.Height = 0;
		SwapChainDescriptor.BufferDesc.RefreshRate.Denominator = 0;
		SwapChainDescriptor.BufferDesc.RefreshRate.Numerator = 0; // let system define that based on our monitor and settings on Windows
		SwapChainDescriptor.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED; // ? dont know yet
		SwapChainDescriptor.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED; // ? dont know yet
		SwapChainDescriptor.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		SwapChainDescriptor.BufferCount = 1; // means double buffering , 2 is triple buffering and so on
		SwapChainDescriptor.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT; // front buffer for rendering target output
		
		// no multisampling yet
		SwapChainDescriptor.SampleDesc.Count = 1;
		SwapChainDescriptor.SampleDesc.Quality = 0;

		// specify windowed output
		SwapChainDescriptor.OutputWindow = win->GetId();
		SwapChainDescriptor.Windowed = TRUE; // yes is windowed

		// swap effect and flags (still dont know exacly what is )
		SwapChainDescriptor.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
		SwapChainDescriptor.Flags = 0;

		
		DIRECT3D_ASSERT( D3D11CreateDeviceAndSwapChain(
			nullptr, // choose the default gpu of the system
			D3D_DRIVER_TYPE_HARDWARE, // driver type i chosen to be the hardware implemented one
			// plus any fueture that is not available in hardware (gpu) it runs on software (cpu) 
			nullptr, // if we have our own software rasterizer implementation of direct3D 11 then we 
			// can give here a handle to the dll of the implementation -- we are in hardware type driver 
			// so this is not needed
			D3D11_CREATE_DEVICE_DEBUG,
			// D3D11_CREATE_DEVICE_DISABLE_GPU_TIMEOUT this flag probaply is good for offline rendering ,
			nullptr, // support from Direct9.1 - Direct11 
			0, // we haven't specify it because is the default (9.1-11.0)
			D3D11_SDK_VERSION,
			&SwapChainDescriptor,
			&m_SwapChain,
			&m_DevicePtr,
			&featureLevelSupport,
			&m_Context
		));
		
#if defined(__JSDEBUG__)
		switch (featureLevelSupport) {
			case D3D_FEATURE_LEVEL_11_0: JS_CORE_INFO("Direct3D 11.0"); break;
			default: JS_CORE_INFO("Direct3D not 11.0 :(");
		}

#endif

		ID3D11Resource* BackBuffer = nullptr;
		DIRECT3D_ASSERT(m_SwapChain->GetBuffer(0, __uuidof(ID3D11Resource), (void**) & BackBuffer));
		DIRECT3D_ASSERT(m_DevicePtr->CreateRenderTargetView(BackBuffer, nullptr, &m_RenderTargetView));
		BackBuffer->Release();
	}

	void Direct3DGraphics::ClearBuffer(float rgba[4]) {
		
		m_Context->ClearRenderTargetView(m_RenderTargetView, rgba);

	}

	void Direct3DGraphics::SwapBuffers(void) const {
		DIRECT3D_ASSERT(m_SwapChain->Present(1, 0));
	}

	Direct3DGraphics::~Direct3DGraphics(void) {

		if (m_SwapChain) {
			m_SwapChain->Release();
		}

		if (m_Context) {
			m_Context->Release();
		}

		if (m_DevicePtr) {
			m_DevicePtr->Release();
		}
	}


	Direct3DGraphics* Direct3DGraphics::Create(Window* win) {
		Direct3DGraphics* obj = new Direct3DGraphics(win);
		JS_CORE_ASSERT(obj, JS_ERROR_NO_MEMORY, "No memory , can't allocate Graphics class !!!");
		return obj;
	}
	void Direct3DGraphics::Destroy(Direct3DGraphics* ptr) {
		if (ptr) {
			delete ptr;
		}
	}

	static float vertices[] = {
		+0.0 , +0.5 , 1.0 ,
		-0.5 , -0.5 , 1.0 ,
		+0.5 , -0.5 , 1.0
	};

	void Direct3DGraphics::DrawTriangle(void) {

		//Create and Bind Vertex Buffer
		ID3D11Buffer* bufObject;
		D3D11_BUFFER_DESC bufferDescriptor;
		bufferDescriptor.ByteWidth = sizeof(vertices);
		bufferDescriptor.Usage = D3D11_USAGE_IMMUTABLE;
		bufferDescriptor.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bufferDescriptor.CPUAccessFlags = 0; // is immutable any way
		bufferDescriptor.MiscFlags = 0; // don't know for sure
		bufferDescriptor.StructureByteStride = 3 * sizeof(float); // size of a vertex 
		D3D11_SUBRESOURCE_DATA data;
		data.pSysMem = vertices;
		data.SysMemPitch = 0; // only for 2D or 2D array textures 
		data.SysMemSlicePitch = 0; // only for 3D textures depth values
		DIRECT3D_ASSERT(m_DevicePtr->CreateBuffer(&bufferDescriptor, &data, &bufObject));
		UINT Strides[] = { 3 * sizeof(float) };
		UINT Offsets[] = { 0 };
		m_Context->IASetVertexBuffers(
			0,
			1,
			&bufObject,
			Strides,
			Offsets 
			);

		

		// create and bind vertex shader
		ID3D11VertexShader* VertexShader = nullptr;
		ID3DBlob* Blob = nullptr;
		DIRECT3D_ASSERT(D3DReadFileToBlob(L"./VertexShader.cso", &Blob)) ;
		DIRECT3D_ASSERT(m_DevicePtr->CreateVertexShader(Blob->GetBufferPointer(), Blob->GetBufferSize(), nullptr, &VertexShader));
		m_Context->VSSetShader(VertexShader, nullptr, 0);
		

		// define and bind vertex layout
		ID3D11InputLayout* Layout = nullptr;
		D3D11_INPUT_ELEMENT_DESC LayoutDescriptor;
		LayoutDescriptor.SemanticName = "POSITION";
		LayoutDescriptor.SemanticIndex = 1; // because is POSITION1 => POSITION , 1
		LayoutDescriptor.Format = DXGI_FORMAT::DXGI_FORMAT_R32G32B32_FLOAT;
		LayoutDescriptor.InstanceDataStepRate = 0;
		LayoutDescriptor.InputSlot = 0;
		LayoutDescriptor.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA; // not yet per instance
		LayoutDescriptor.AlignedByteOffset = 0;
		DIRECT3D_ASSERT(m_DevicePtr->CreateInputLayout(
			&LayoutDescriptor, 1, Blob->GetBufferPointer(), Blob->GetBufferSize(), &Layout));
		m_Context->IASetInputLayout(Layout);
			
		Blob->Release();
		// create and bind pixel shader
		ID3D11PixelShader* PixelShader = nullptr;
		DIRECT3D_ASSERT(D3DReadFileToBlob(L"PixelShader.cso", &Blob));
		DIRECT3D_ASSERT(m_DevicePtr->CreatePixelShader(Blob->GetBufferPointer(), Blob->GetBufferSize(), nullptr, &PixelShader));
		m_Context->PSSetShader(PixelShader, nullptr, 0);
		Blob->Release();

		// bind render target 
		m_Context->OMSetRenderTargets(1, &m_RenderTargetView, nullptr);

		//bind viewport
		D3D11_VIEWPORT viewport;
		viewport.Height = 600;
		viewport.Width = 800;
		viewport.MinDepth = 0;
		viewport.MaxDepth = 1;
		viewport.TopLeftX = 0;
		viewport.TopLeftY = 0;
		m_Context->RSSetViewports(1, &viewport);

		//configure primitives types
		D3D11_PRIMITIVE_TOPOLOGY PrimitiveType;
		PrimitiveType = D3D11_PRIMITIVE_TOPOLOGY::D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
		m_Context->IASetPrimitiveTopology(PrimitiveType);



		m_Context->Draw(sizeof(vertices) / (3 * sizeof(float)), 0);

		VertexShader->Release();
		PixelShader->Release();
		bufObject->Release();
	}

}
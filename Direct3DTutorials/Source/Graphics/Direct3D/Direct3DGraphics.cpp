#pragma once
#include "Direct3DGraphics.hpp"
#include "ErrorInfo.hpp"
#include <cmath>
#include <DirectXMath.h>


namespace JSGraphicsEngine3D {

	Direct3DGraphics::Direct3DGraphics(std::shared_ptr<Window>& win) {

		D3D_FEATURE_LEVEL featureLevelSupport;
		DXGI_SWAP_CHAIN_DESC SwapChainDescriptor;
		// set up front/back buffers description 
		SwapChainDescriptor.BufferDesc.Width = 0;// take window default;
		SwapChainDescriptor.BufferDesc.Height = 0;
		SwapChainDescriptor.BufferDesc.RefreshRate.Denominator = 0;
		SwapChainDescriptor.BufferDesc.RefreshRate.Numerator = 0; // let system define that based on our monitor and settings on Windows
		SwapChainDescriptor.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED; // ? dont know yet
		SwapChainDescriptor.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED; // ? dont know yet
		SwapChainDescriptor.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
		SwapChainDescriptor.BufferCount = 1; // means double buffering , 2 is triple buffering and so on
		SwapChainDescriptor.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT; // back buffer for rendering target output
		
		// no multisampling yet
		SwapChainDescriptor.SampleDesc.Count = 1;
		SwapChainDescriptor.SampleDesc.Quality = 0;

		// specify windowed output
		SwapChainDescriptor.OutputWindow = win->GetId();
		SwapChainDescriptor.Windowed = TRUE; // yes is windowed

		// swap effect and flags (still dont know exacly what is )
		SwapChainDescriptor.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
		SwapChainDescriptor.Flags = 0;

		
		HRESULT hres = D3D11CreateDeviceAndSwapChain(
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
		);
		JSGraphicsEngine3D::InitD3DDebug(m_DevicePtr);
		
#if defined(__JSDEBUG__)
		switch (featureLevelSupport) {
			case D3D_FEATURE_LEVEL_11_0: JS_CORE_INFO("Direct3D 11.0"); break;
			default: JS_CORE_INFO("Direct3D not 11.0 :(");
		}

#endif

		ID3D11Resource* BackBuffer = nullptr;
		JS_CHECKD3D(m_SwapChain->GetBuffer(0, __uuidof(ID3D11Resource), (void**) & BackBuffer));
		JS_CHECKD3D(m_DevicePtr->CreateRenderTargetView(BackBuffer, nullptr, &m_RenderTargetView));
		BackBuffer->Release();
	}

	void Direct3DGraphics::ClearBuffer(float rgba[4]) {
		
		m_Context->ClearRenderTargetView(m_RenderTargetView, rgba);

	}

	void Direct3DGraphics::SwapBuffers(void) const {
		JS_CHECKD3D(m_SwapChain->Present(1, 0));
	}

	Direct3DGraphics::~Direct3DGraphics(void) {

		if (m_SwapChain) {
			m_SwapChain->Release();
		}

		if (m_Context) {
			m_Context->Release();
		}

		if (m_RenderTargetView) {
			m_RenderTargetView->Release();
		}

		if (m_DevicePtr) {
			m_DevicePtr->Release();
		}
	}


	Direct3DGraphics* Direct3DGraphics::Create(std::shared_ptr<Window>& win) {
		Direct3DGraphics* obj = new Direct3DGraphics(win);
		JS_CORE_ASSERT(obj, JS_ERROR_NO_MEMORY, "No memory , can't allocate Graphics class !!!");
		return obj;
	}
	void Direct3DGraphics::Destroy(Direct3DGraphics* ptr) {
		if (ptr) 
			delete ptr;
		
	}

	static float vertices[] = {
		-0.5 , +0.5 , 1.0f , 0.0f , 0.0f ,
		+0.5 , +0.5 , 0.0f , 1.0f , 0.0f ,
		-0.5 , -0.5 , 0.0f , 0.0f , 1.0f ,
		+0.5 , -0.5 , 1.0f , 1.0f , 1.0f 
	};

	static uint16_t indices[] = {
		0 , 1 , 2 ,
		1 , 3 , 2
	};

	

	void Direct3DGraphics::DrawTriangle(float angle) {
		float MVP_Matrix[4][4] = {
		{std::cos(angle) , std::sin(angle) , 0 , 0} ,
		{-std::sin(angle) , std::cos(angle) , 0 , 0} ,
		{0 , 0 , 1 , 0} ,
		{0 , 0 , 0 , 1}
		};

		DirectX::XMMATRIX transform =  DirectX::XMMatrixRotationZ(angle) ;
		DirectX::XMFLOAT4X4 floatMat;
		XMStoreFloat4x4(&floatMat, transform);
		//Create and Bind Vertex Buffer
		ID3D11Buffer* bufObject;
		D3D11_BUFFER_DESC bufferDescriptor;
		bufferDescriptor.ByteWidth = sizeof(vertices);
		bufferDescriptor.StructureByteStride = 5 * sizeof(float); // size of a vertex 
		bufferDescriptor.Usage = D3D11_USAGE_DEFAULT;
		bufferDescriptor.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bufferDescriptor.CPUAccessFlags = 0; // is immutable any way
		bufferDescriptor.MiscFlags = 0; // don't know for sure
		D3D11_SUBRESOURCE_DATA data;
		data.pSysMem = vertices;
		data.SysMemPitch = 0; // only for 2D or 2D array textures 
		data.SysMemSlicePitch = 0; // only for 3D textures depth values
		JS_CHECKD3D(m_DevicePtr->CreateBuffer(&bufferDescriptor, &data, &bufObject));
		UINT Strides[] = { 5 * sizeof(float) };
		UINT Offsets[] = { 0 };
		JS_CHECKD3D(m_Context->IASetVertexBuffers(
			0,
			1,
			&bufObject,
			Strides,
			Offsets 
		));
		
		//Create and Bind Index Buffer
		ID3D11Buffer* IndexBufferObj;
		D3D11_BUFFER_DESC IndexDescriptor;
		IndexDescriptor.ByteWidth = sizeof(indices);
		IndexDescriptor.StructureByteStride = sizeof(uint16_t); // size of a vertex 
		IndexDescriptor.Usage = D3D11_USAGE_DEFAULT;
		IndexDescriptor.BindFlags = D3D11_BIND_INDEX_BUFFER;
		IndexDescriptor.CPUAccessFlags = 0; // is immutable any way
		IndexDescriptor.MiscFlags = 0; // don't know for sure
		D3D11_SUBRESOURCE_DATA IndexData;
		IndexData.pSysMem = indices;
		IndexData.SysMemPitch = 0; // only for 2D or 2D array textures 
		IndexData.SysMemSlicePitch = 0; // only for 3D textures depth values
		JS_CHECKD3D(m_DevicePtr->CreateBuffer(&IndexDescriptor, &IndexData, &IndexBufferObj));
		JS_CHECKD3D(m_Context->IASetIndexBuffer(IndexBufferObj, DXGI_FORMAT_R16_UINT, 0));

		// Create Constant Buffer
		ID3D11Buffer* ConstBufferObj;
		D3D11_BUFFER_DESC ConstantDescriptor;
		ConstantDescriptor.ByteWidth = sizeof(MVP_Matrix);
		ConstantDescriptor.StructureByteStride = 0; 
		ConstantDescriptor.Usage = D3D11_USAGE_DYNAMIC;
		ConstantDescriptor.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		ConstantDescriptor.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE; 
		ConstantDescriptor.MiscFlags = 0; 
		D3D11_SUBRESOURCE_DATA ConstantData;
		ConstantData.pSysMem = MVP_Matrix;
		ConstantData.SysMemPitch = 0; // only for 2D or 2D array textures 
		ConstantData.SysMemSlicePitch = 0; // only for 3D textures depth values
		JS_CHECKD3D(m_DevicePtr->CreateBuffer(&ConstantDescriptor, &ConstantData, &ConstBufferObj));
		JS_CHECKD3D(m_Context->VSSetConstantBuffers(0, 1, &ConstBufferObj));

		// create and bind pixel shader
		ID3D11PixelShader* PixelShader = nullptr;
		ID3DBlob* Blob = nullptr;
		JS_CHECKD3D(D3DReadFileToBlob(L"PixelShader.cso", &Blob));
		JS_CHECKD3D(m_DevicePtr->CreatePixelShader(Blob->GetBufferPointer(), Blob->GetBufferSize(), nullptr, &PixelShader));
		m_Context->PSSetShader(PixelShader, nullptr, 0);
		Blob->Release();

		

		// create and bind vertex shader
		ID3D11VertexShader* VertexShader = nullptr;
		JS_WINCHECK( D3DReadFileToBlob(L"VertexShader.cso", &Blob) );
		JS_CHECKD3D(m_DevicePtr->CreateVertexShader(Blob->GetBufferPointer(), Blob->GetBufferSize(), nullptr, &VertexShader));
		JS_CHECKD3D(m_Context->VSSetShader(VertexShader, nullptr, 0));

		// define and bind vertex layout
		ID3D11InputLayout* Layout = nullptr;
		D3D11_INPUT_ELEMENT_DESC LayoutDescriptor[] = { 
			{
			.SemanticName = "POSITION",
			.SemanticIndex = 0, // because is POSITION0 => POSITION , 0
			.Format = DXGI_FORMAT::DXGI_FORMAT_R32G32_FLOAT,
			.InputSlot = 0,
			.AlignedByteOffset = 0 ,
			.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA,
			.InstanceDataStepRate = 0
			} , 

			{
			.SemanticName = "COLOR",
			.SemanticIndex = 0, // because is POSITION0 => POSITION , 0
			.Format = DXGI_FORMAT::DXGI_FORMAT_R32G32B32_FLOAT,
			.InputSlot = 0,
			.AlignedByteOffset = 2 * sizeof(float) ,
			.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA,
			.InstanceDataStepRate = 0
			}
		};

		JS_CHECKD3D(m_DevicePtr->CreateInputLayout(
			LayoutDescriptor, sizeof(LayoutDescriptor) / sizeof(D3D11_INPUT_ELEMENT_DESC),
			Blob->GetBufferPointer(), Blob->GetBufferSize(), &Layout));
		JS_CHECKD3D(m_Context->IASetInputLayout(Layout));
		Blob->Release();

		

		// bind render target 
		JS_CHECKD3D(m_Context->OMSetRenderTargets(1, &m_RenderTargetView, nullptr));

		//bind viewport
		D3D11_VIEWPORT viewport;
		viewport.Height = 100;
		viewport.Width = 100;
		viewport.MinDepth = 0;
		viewport.MaxDepth = 1;
		viewport.TopLeftX = 0;
		viewport.TopLeftY = 0;
		JS_CHECKD3D(m_Context->RSSetViewports(1, &viewport));

		//configure primitives types
		D3D11_PRIMITIVE_TOPOLOGY PrimitiveType;
		PrimitiveType = D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
		JS_CHECKD3D(m_Context->IASetPrimitiveTopology(PrimitiveType));

		
		JS_CHECKD3D(m_Context->DrawIndexed(sizeof(indices) / sizeof(uint16_t), 0, 0));
		//JS_CHECKD3D(m_Context->Draw(4, 0));

		IndexBufferObj->Release();
		VertexShader->Release();
		PixelShader->Release();
		bufObject->Release();
		Layout->Release();
	}

}
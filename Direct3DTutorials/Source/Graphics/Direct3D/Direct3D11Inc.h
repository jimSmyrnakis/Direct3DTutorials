#pragma once
#include <d3dcompiler.h>
#include <d3d11.h>             // ��� ������ D3D11 API
#include <dxgi.h>              // ��� DXGI interfaces (�.�. IDXGISwapChain)
#include <d3d11sdklayers.h>    // ��� ID3D11InfoQueue (debug info)
#include <wrl/client.h>        // ��� Microsoft::WRL::ComPtr
#pragma comment(lib , "d3d11.lib")
#pragma comment(lib , "D3DCompiler.lib")
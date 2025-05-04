#pragma once
#include <d3dcompiler.h>
#include <d3d11.h>             // Για βασικό D3D11 API
#include <dxgi.h>              // Για DXGI interfaces (π.χ. IDXGISwapChain)
#include <d3d11sdklayers.h>    // Για ID3D11InfoQueue (debug info)
#include <wrl/client.h>        // Για Microsoft::WRL::ComPtr
#pragma comment(lib , "d3d11.lib")
#pragma comment(lib , "D3DCompiler.lib")
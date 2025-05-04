#define _CRT_SECURE_NO_WARNINGS
#include "ErrorInfo.hpp"
#include "../../Error/Error.hpp"
#include <vector>

namespace JSGraphicsEngine3D {
    static ID3D11InfoQueue* g_InfoQueue = NULL;

    void InitD3DDebug(ID3D11Device* device) {

        HRESULT hr = device->QueryInterface(__uuidof(ID3D11InfoQueue), (void**)&g_InfoQueue);
        if (FAILED(hr)) {
            JS_CORE_ASSERT_FATAL(0, 15, "Can't initiallize the direct3D debug layer !!!" , "LOL" , "Lol2");
        }
        //
    }

    void FiniD3DDebug(void) {

        if (g_InfoQueue) {
            g_InfoQueue->Release();
        }
    }

    void ClearD3DErrors() {

        if (g_InfoQueue) {
            g_InfoQueue->ClearStoredMessages();
        }
    }

    bool D3DHasNewError() {
        if (!g_InfoQueue) return false;

        SIZE_T count = g_InfoQueue->GetNumStoredMessagesAllowedByRetrievalFilter();
        for (SIZE_T i = 0; i < count; ++i) {
            SIZE_T len = 0;
            g_InfoQueue->GetMessage(i, nullptr, &len);
            std::vector<char> buffer(len);
            D3D11_MESSAGE* msg = reinterpret_cast<D3D11_MESSAGE*>(buffer.data());
            if (SUCCEEDED(g_InfoQueue->GetMessage(i, msg, &len))) {
                if (msg->Severity == D3D11_MESSAGE_SEVERITY_ERROR ||
                    msg->Severity == D3D11_MESSAGE_SEVERITY_CORRUPTION ||
                    msg->Severity == D3D11_MESSAGE_SEVERITY_WARNING)
                    return true;  // error exist 
            }
        }
        return false;
    }

    char* GetLastD3DErrorMessageA(void) {
        if (!g_InfoQueue) return NULL;

        SIZE_T count = g_InfoQueue->GetNumStoredMessagesAllowedByRetrievalFilter();
        for (SIZE_T i = count; i-- > 0;) {
            SIZE_T len = 0;
            g_InfoQueue->GetMessage(i, NULL, &len);
            if (len == 0) continue;

            std::vector<char> buffer(len);
            D3D11_MESSAGE* msg = reinterpret_cast<D3D11_MESSAGE*>(buffer.data());

            if (SUCCEEDED(g_InfoQueue->GetMessage(i, msg, &len))) {
                if (msg->Severity == D3D11_MESSAGE_SEVERITY_ERROR ||
                    msg->Severity == D3D11_MESSAGE_SEVERITY_CORRUPTION || 
                    msg->Severity == D3D11_MESSAGE_SEVERITY_WARNING) {

                    const char* desc = msg->pDescription;
                    size_t descLen = strlen(desc);
                    char* out = (char*)malloc(descLen + 1);
                    if (out) {
                        strcpy(out, desc);
                        return out;
                    }
                }
            }
        }

        return NULL;
    }

}
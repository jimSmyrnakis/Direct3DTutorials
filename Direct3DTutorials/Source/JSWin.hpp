#pragma once

// ��������� �� ����� include ������ �����
#ifndef WINDOWS_HELPER_HEADER
#define WINDOWS_HELPER_HEADER

// ��������� ������� �������� headers (���� GDI, DDE, RPC, �.��.)
#define WIN32_LEAN_AND_MEAN

// ��������� �� macro-������ ��� min/max (conflict �� std::min/max)
#define NOMINMAX

// Optional excludes (���������� ����� ���������):
// #define NOGDI
//#define NOCRYPT
// #define NOSERVICE
 //#define NOKERNEL
 //#define NOUSER

// �� ����� header ��� Windows API
#include <windows.h>

#endif // WINDOWS_HELPER_HEADER

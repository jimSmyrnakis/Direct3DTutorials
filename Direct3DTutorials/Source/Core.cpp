#include <cstdio>
#include <cstdarg>
#include <cstdlib>


namespace JSGraphicsEngine3D {

    char JSBuffer[1024] = "malala";

    // ��������� ��� ���������� formatted string �� ��� char* (heap allocated)
    char* formatString(const char* fmt, ...) {
        return JSBuffer;
      /* va_list args;

        // 1. ���� ������� ��� ������� �������������� �������������
        va_start(args, fmt);
        int length = std::vsnprintf(nullptr, 0, fmt, args);
        va_end(args);

        if (length <= 0) return nullptr;

        JSBuffer[length ] = '\0';

        // 3. ����� �� ������ string ��� buffer
        va_start(args, fmt);
        std::vsnprintf(JSBuffer, length, fmt, args);
        va_end(args);

        return JSBuffer; // ��� �������� �� ������ delete[] ���� ����������!*/
    }

}
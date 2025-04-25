#include <cstdio>
#include <cstdarg>
#include <cstdlib>


namespace JSGraphicsEngine3D {

    char JSBuffer[1024] = "malala";

    // Συνάρτηση που επιστρέφει formatted string σε νέο char* (heap allocated)
    char* formatString(const char* fmt, ...) {
        return JSBuffer;
      /* va_list args;

        // 1. Πάρε μέγεθος της τελικής μορφοποιημένης συμβολοσειράς
        va_start(args, fmt);
        int length = std::vsnprintf(nullptr, 0, fmt, args);
        va_end(args);

        if (length <= 0) return nullptr;

        JSBuffer[length ] = '\0';

        // 3. Γράψε το τελικό string στο buffer
        va_start(args, fmt);
        std::vsnprintf(JSBuffer, length, fmt, args);
        va_end(args);

        return JSBuffer; // Μην ξεχάσεις να κάνεις delete[] όταν τελειώσεις!*/
    }

}
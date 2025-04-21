#pragma once

// Αποφεύγει να γίνει include πολλές φορές
#ifndef WINDOWS_HELPER_HEADER
#define WINDOWS_HELPER_HEADER

// Αποτρέπει φόρτωμα περιττών headers (όπως GDI, DDE, RPC, κ.λπ.)
#define WIN32_LEAN_AND_MEAN

// Αποτρέπει τη macro-ποίηση των min/max (conflict με std::min/max)
#define NOMINMAX

// Optional excludes (ξεκλείδωσε όποιο χρειαστεί):
// #define NOGDI
//#define NOCRYPT
// #define NOSERVICE
 //#define NOKERNEL
 //#define NOUSER

// Το κύριο header του Windows API
#include <windows.h>

#endif // WINDOWS_HELPER_HEADER

#pragma once

#ifdef _DYNAMIC
#define DLL_EXPORT __declspec(dllexport)
#else
#define DLL_EXPORT 
#endif
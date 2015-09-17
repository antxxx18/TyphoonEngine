#pragma once

#define TYPHOON_ENGINE_VERSION 0_0_1

#ifdef _WIN32
#define PLATFORM_WINDOWS
#elif __linux__
#define PLATFORM_LINUX
#endif

#include <ctime>
#include <sstream>
#include <string>
#include <list>
#include <vector>
#include <map>

#ifdef PLATFORM_WINDOWS
#define WIN32_LEAN_AND_LEAN
#include <Windows.h>
#include <d3d11.h>
#include <d3dx11.h>
#include <d3dcompiler.h>
#include <xnamath.h>
#pragma comment(lib, "d3d11.lib")
#ifdef _DEBUG
#	pragma comment(lib, "d3dx11d.lib")
#else
#	pragma comment(lib, "d3dx11.lib")
#endif // _DEBUG
#elif PLATFORM_LINUX
// linux 
#else
#error Platform not supported!
#endif // PLATFORM_WINDOWS

#include "CommonSystem/Common.h"
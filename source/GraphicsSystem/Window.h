#pragma once

#include "stdafx.h"

#ifdef PLATFORM_WINDOWS
#include "PlatformSystem/Windows/WinWindow.h"
typedef TE::WinWindow Window;
#elif PLATFORM_LINUX
#endif
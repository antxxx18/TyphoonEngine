#pragma once

#ifdef PLATFORM_WINDOWS
#include "PlatformSystem/Windows/WinInputManager.h"
typedef TE::WinInputManager InputManager;
#elif PLATFORM_LINUX
#include "LinuxInputManager.h"
#endif
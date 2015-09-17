cmake_minimum_required(VERSION 3.2)
project(TyphoonEngine)

#include_directories($ENV{DXSDK_DIR}/Include)
#link_directories("$ENV{DXSDK_DIR}/Lib/x86")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -msse -msse2 -msse3")

#set(SOURCE_FILES Game/main.cpp)
add_executable(TyphoonEngine ${SOURCE_FILES} UtilSystem/Log.cpp UtilSystem/Log.h
CommonSystem/Common.h
CoreSystem/Core.cpp CoreSystem/Core.h
InputSystem/InputListener.h InputSystem/InputManager.h
PlatformSystem/Windows/WinInputCodes.h PlatformSystem/Windows/WinInputManager.cpp PlatformSystem/Windows/WinInputManager.h PlatformSystem/Windows/WinWindow.cpp PlatformSystem/Windows/WinWindow.h
RenderSystem/Render.cpp RenderSystem/Render.h RenderSystem/Window.h
TEngine.h stdafx.h)


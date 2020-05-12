#pragma once
#if defined _WIN64 || _Win32
#include "x64\UserManager_x64.h"
	using UserManager = UserManager_x64;

#elif defined _ORBIS
#include "PS4\UserManager_PS4.h"
	using UserManager = UserManager_PS4;
#endif
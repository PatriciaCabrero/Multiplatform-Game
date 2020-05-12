#if defined _WIN64 || _Win32
#include "x64\Platform_x64.h"
using Platform = Platform_x64;

#elif defined _ORBIS
#include "PS4\Platform_PS4.h"
using Platform = Platform_PS4;
#endif
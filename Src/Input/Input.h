#if defined _WIN64 || _Win32
#include "x64\Input_x64.h"
using Input = Input_x64;

#elif defined _ORBIS
#include "PS4/Input_PS4.h"
using Input = Input_PS4;
#endif
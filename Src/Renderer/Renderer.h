#if defined _WIN64 || _Win32
#include "x64\Renderer_x64.h"
using Renderer = Renderer_x64;

#elif defined _ORBIS
#include "PS4\Renderer_PS4.h"
using Renderer = Renderer_PS4;
#endif



#pragma once
#ifndef M_PI
    #define M_PI 3.14159265358979323846
#endif

#if defined _WIN32 || defined __CYGWIN__
#define CUMT_MULP_MAIN WinMain
#else
#define CUMT_MULP_MAIN main
#endif

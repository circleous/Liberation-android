#pragma once



#ifdef __i386__
#  define PATCHSIZE 6
#elif defined(__arm__)
#  define PATCHSIZE 6
#elif defined(__aarch64__)
#  define PATCHSIZE 6
#endif
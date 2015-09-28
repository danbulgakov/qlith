#ifndef QLITH
#define QLITH

#include "pth.h"

namespace QLith
{
    static void init()
    {
        pth_init();
    }

    static void free()
    {
        pth_kill();
    }
}
#endif // QLITH


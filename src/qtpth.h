#ifndef QTPTH
#define QTPTH

#include "pth.h"

namespace QtPth
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
#endif // QTPTH


#include <stdarg.h>
#include <stdio.h>

#include "theori/theori.h"

void THEORI_FUNC
theori_log(const char* format, ...)
{
    va_list p;
    va_start(p, format);
    int r = vfprintf(stderr, format, p);
    va_end(p);
}

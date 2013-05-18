#ifndef SEARCH_H
#define SEARCH_H

#include "osdetect.h"

#if OS != WINDOWS
#include "slinux.h"
#else
#include "swindows.h"
#endif

#endif
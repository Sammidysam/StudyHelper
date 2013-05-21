#ifndef SEARCH_H
#define SEARCH_H

#include "osdetect.h"

#if OS == WINDOWS
#include "searchwindows.h"
#else
#include "searchlinux.h"
#endif

#endif
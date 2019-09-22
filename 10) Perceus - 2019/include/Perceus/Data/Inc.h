#pragma once

#if defined(_WIN32) || defined(WIN32) && !defined(PERC_STATIC)
#   ifdef _PERCEUS_BUILD
#       define PERC_API __declspec(dllexport)
#   else
#       define PERC_API __declspec(dllimport)
#   endif
#endif

#ifdef _PERCEUS_64
#   define PCS_BITS 64
#else
#   define PCS_BITS 32
#endif

#include <vector>
#include <stack>

#include <string>
#include <math.h>
#include "Perceus/Util/Memory/Mem.h"
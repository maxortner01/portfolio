#pragma once

#include "Perceus/Data/Singleton.h"

#include <stdio.h>
#include <cstring>
#include <stdlib.h>

#ifndef WIN32
#include "sys/times.h"
#include "sys/vtimes.h"
#else
#include <windows.h>
#endif

namespace pcs
{
    class Profiler : public Data::Singleton<Profiler>
    {
#if defined(WIN32) or defined(_WIN32)
        static ULARGE_INTEGER lastCPU, lastSysCPU, lastUserCPU;
        static int numProcessors;
        static HANDLE self;
#else
        static clock_t lastCPU, lastSysCPU, lastUserCPU;
        static int numProcessors;
		
        int getValue() const;
#endif
        void init() const;
        double getCurrentValue() const;
        int parseLine(char* line) const;

    public:
        /**
         * @brief Gets the current memory usage in kilobytes.
         * 
         * @return unsigned int Amount of virtual memory used in kilobytes.
         */
#if !defined(WIN32) or !defined(_WIN32)
        unsigned int getMemoryUsage() const
        {
            return getValue();
        }
#else
		unsigned int getMemoryUsage() const
		{
			return 0;
		}
#endif

        double getCPUPercent() const
        {
            return getCurrentValue();
        }
    };
}
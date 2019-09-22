#pragma once

#ifndef __ANSEL_EXPORTING
#	 define ANSEL_API __declspec(dllimport)
#else
#	 define ANSEL_API __declspec(dllexport)
#endif
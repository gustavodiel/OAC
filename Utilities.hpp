//
//  Utilities.hpp
//  OAC App 2
//
//  Created by Gustavo Diel on 27/03/17.
//  Copyright © 2017 Gustavo Diel. All rights reserved.
//

#pragma once

#include <glm/glm.hpp>

//! gerenciador da aplicacao IDS
extern class Application * ptrApp;

namespace Utilities {
	typedef struct f
	{
		glm::vec3 forca;
		double time;
	} TimeForce;

	inline double map(double n, double start1, double stop1, double start2, double stop2) {
		return ((n - start1) / (stop1 - start1))*(stop2 - start2) + start2;
	}

	inline void printVec3(glm::vec3 vec, const char* nome = "") {
		printf("%s = [x: %.3lf y: %.3lf z: %.3lf]\n", nome, vec.x, vec.y, vec.z);
	}

	inline glm::vec3 limit(glm::vec3 vec, float max) {
		auto l = glm::length(vec);
		if (l > max) {
			return glm::normalize(vec) * max;
		}
		return vec;

	}
}

#ifndef _WIN32

#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>
#include <errno.h>

#if HAVE_NANOSLEEP || HAVE_CLOCK_GETTIME
#include <time.h>
#endif
#ifdef __APPLE__
#include <mach/mach_time.h>
#endif


namespace Utilities{
    void startTicks();
    unsigned long getTicks();
    void delay(unsigned long);

    /* The first ticks value of the application */
#if HAVE_CLOCK_GETTIME
    static struct timespec start_ts;
#elif defined(__APPLE__)
    static uint64_t start_mach;
    static mach_timebase_info_data_t mach_base_info;
#endif
    extern bool has_monotonic_time;
    extern timeval start_tv;
	inline double map(double n, double start1, double stop1, double start2, double stop2) {
		return ((n - start1) / (stop1 - start1))*(stop2 - start2) + start2;
	}
}

#else
#include <glm/glm.hpp>
#include <ctime>
namespace Utilities {
	void startTicks();
	unsigned long getTicks();
}
#endif
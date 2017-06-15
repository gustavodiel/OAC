//
//  Utilities.cpp
//  OAC App 2
//
//  Created by Gustavo Diel on 27/03/17.
//  Copyright © 2017 Gustavo Diel. All rights reserved.
//
#include "stdafx.h"
#include "Utilities.hpp"

#ifdef __linux__ || __APPLE__
timeval Utilities::start_tv;
bool Utilities::has_monotonic_time = false;

void Utilities::startTicks()
{
    /* Set first ticks value */
#if HAVE_CLOCK_GETTIME
    if (clock_gettime(CLOCK_MONOTONIC, &start_ts) == 0) {
        has_monotonic_time = SDL_TRUE;
    } else
#elif defined(__APPLE__)
        start_mach = mach_absolute_time();
    kern_return_t ret = mach_timebase_info(&mach_base_info);
    if (ret == 0) {
        has_monotonic_time = true;
    } else
#endif
    {
        gettimeofday(&start_tv, NULL);
    }
}

unsigned long Utilities::getTicks(){
    unsigned long ticks;
    if (has_monotonic_time) {
#if HAVE_CLOCK_GETTIME
        struct timespec now;
        clock_gettime(CLOCK_MONOTONIC, &now);
        ticks =
        (now.tv_sec - start_ts.tv_sec) * 1000 + (now.tv_nsec -
                                                 start_ts.tv_nsec) / 1000000;
#elif defined(__APPLE__)
        uint64_t now = mach_absolute_time();
        ticks = (now - start_mach) * mach_base_info.numer / mach_base_info.denom / 1000000;
#endif
    } else {
        struct timeval now;
        
        gettimeofday(&now, NULL);
        ticks =
        (now.tv_sec - start_tv.tv_sec) * 1000 + (now.tv_usec -
                                                 start_tv.tv_usec) / 1000;
    }
    return (ticks);
    
}

void Utilities::delay(unsigned long ms){
    int was_error;
    
#if HAVE_NANOSLEEP
    struct timespec elapsed, tv;
#else
    struct timeval tv;
    unsigned long then, now, elapsed;
#endif
    
    /* Set the timeout interval */
#if HAVE_NANOSLEEP
    elapsed.tv_sec = ms / 1000;
    elapsed.tv_nsec = (ms % 1000) * 1000000;
#else
    then = getTicks();
#endif
    do {
        errno = 0;
        
#if HAVE_NANOSLEEP
        tv.tv_sec = elapsed.tv_sec;
        tv.tv_nsec = elapsed.tv_nsec;
        was_error = nanosleep(&tv, &elapsed);
#else
        /* Calculate the time interval left (in case of interrupt) */
        now = getTicks();
        elapsed = (now - then);
        then = now;
        if (elapsed >= ms) {
            break;
        }
        ms -= elapsed;
        tv.tv_sec = ms / 1000;
        tv.tv_usec = (ms % 1000) * 1000;
        
        was_error = select(0, NULL, NULL, NULL, &tv);
#endif /* HAVE_NANOSLEEP */
    } while (was_error && (errno == EINTR));
}

#else

void Utilities::startTicks() {

}
unsigned long Utilities::getTicks() {
	return clock();
}


#endif
#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <signal.h>
#include <sys/time.h>
#include "simple_timer.h"

/*  Returns the whole seconds part of a number of seconds  */

static long get_whole_seconds(const double seconds)
{
    return (long) seconds;
}

/*  Returns the fractional part of a number of seconds, in microseconds  */

static long get_fractional_microseconds(const double seconds)
{
    const double whole_secs = get_whole_seconds(seconds);
    const double fractional_part = seconds - whole_secs;
    return (long) (fractional_part * 1000000);
}

/*  Dummy signal handler  */

static void handler(int signum)
{
    (void) signum;      //  Suppress warning about unused variable
}

/*  Starts a timer after 'start' seconds,
 *  to repeat every 'interval' seconds    */

void timer_start(const double start, const double interval)
{
    struct sigaction sa;

    /*  Fill in sigaction struct  */

    sa.sa_handler = handler;
    sa.sa_flags = 0;
    sigemptyset(&sa.sa_mask);

    /*  Set signal handler for SIGLARM  */

    if ( sigaction(SIGALRM, &sa, NULL) == -1 ) {
        perror("couldn't set SIGALRM handler");
        exit(EXIT_FAILURE);
    }

    /*  Fill in itimerval struct and start timer  */

    struct itimerval itv;
    itv.it_interval.tv_sec = get_whole_seconds(interval);
    itv.it_interval.tv_usec = get_fractional_microseconds(interval);
    itv.it_value.tv_sec = get_whole_seconds(start);
    itv.it_value.tv_usec = get_fractional_microseconds(start);

    if ( setitimer(ITIMER_REAL, &itv, NULL) == -1 ) {
        perror("couldn't start timer");
        exit(EXIT_FAILURE);
    }
}

/*  Stops a currently running timer  */

void timer_stop(void)
{
    struct itimerval itv;
    itv.it_interval.tv_sec = 0;
    itv.it_interval.tv_usec = 0;
    itv.it_value.tv_sec = 0;
    itv.it_value.tv_usec = 0;

    if ( setitimer(ITIMER_REAL, &itv, NULL) == -1 ) {
        perror("couldn't stop timer");
        exit(EXIT_FAILURE);
    }
}

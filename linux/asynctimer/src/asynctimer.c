/*
 ============================================================================
 Name        : asynctimer.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>
#include <sys/time.h>
#include <signal.h>
#include "asynctimer.h"

void TimerHandleSignal(timerhandle_t* handle) { sem_post(handle); };
int32_t TimerHandleWait(timerhandle_t* handle) { return sem_wait(handle); };

void TimerCallback(union sigval si) {
    TimerHandleSignal((timerhandle_t*)(si.sival_ptr));
    printf("Timer\n");
}

int32_t TimerSet(timer_t* timerfd, void* handle, TimerConfig_t timerconfig) {
    struct itimerspec ts;
    struct sigevent se;

    se.sigev_notify = SIGEV_THREAD;
    se.sigev_value.sival_ptr = handle;
    se.sigev_notify_function = TimerCallback;
    se.sigev_notify_attributes = NULL;

    if (ETIMERSUCCESS != timer_create(CLOCK_REALTIME, &se, timerfd)) {
        return ETIMERFAILCREATE;
    }

    ts.it_value.tv_sec = timerconfig.delaysec;
    ts.it_value.tv_nsec = timerconfig.delaynsec;
    ts.it_interval.tv_sec = timerconfig.intervalsec;
    ts.it_interval.tv_nsec = timerconfig.intervalnsec;

    if (ETIMERSUCCESS != timer_settime(*timerfd, 0, &ts, NULL)) {
        return ETIMERFAILSTART;
    }

    return ETIMERSUCCESS;
}

int32_t TimerWait(timerhandle_t* value) {
    return TimerHandleWait(value);
}



int32_t TimerStop(timer_t* timerfd) {
    if (timer_delete(timerfd) < 0) {
        return ETIMERFAILSTOP;
    }
    return ETIMERSUCCESS;
}







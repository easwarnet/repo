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

int main() {
    timerhandle_t heartbeattimerhandle;
    timer_t timerfd_;
    TimerConfig_t TimerConfig = {0, 100000000, 1, 0};
    TimerSet(&timerfd_, (void *)(&heartbeattimerhandle), TimerConfig);
    for (;;) {
        if (TimerWait(&heartbeattimerhandle) < 0) {
            /*Error*/
            break;
        }
    }
}




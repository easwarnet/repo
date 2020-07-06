
#ifndef ASYNCTIMER
#define ASYNCTIMER

#define ETIMERSUCCESS 0
#define ETIMERFAILCREATE (-1)
#define ETIMERFAILSTART (-2)
#define ETIMERFAILSTOP (-3)

typedef sem_t timerhandle_t;

typedef struct TIMER_CONFIG {
    uint32_t delaysec;
    uint32_t delaynsec;
    uint32_t intervalsec;
    uint32_t intervalnsec;
} TimerConfig_t;


void TimerHandleSignal(timerhandle_t* handle);
int32_t TimerHandleWait(timerhandle_t* handle);
void TimerCallback(union sigval si);
int32_t TimerSet(timer_t* timerfd, void* handle, TimerConfig_t timerconfig);
int32_t TimerWait(timerhandle_t* value);
int32_t TimerStop(timer_t* timerfd);

#endif


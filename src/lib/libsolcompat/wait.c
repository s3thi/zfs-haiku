#include <kernel/OS.h>
#include <time.h>
#include <pthread.h>

struct timespec __ts_add(struct timespec, struct timespec);

int pthread_cond_reltimedwait_np(pthread_cond_t *cv,  pthread_mutex_t *mp,
    const struct timespec *reltime)
{
	struct timespec curtime;
	bigtime_t microSeconds = real_time_clock_usecs();
    curtime.tv_sec = microSeconds / 1000000;
    curtime.tv_nsec = (microSeconds % 1000000) * 1000;
	struct timespec abstime = __ts_add(curtime, *reltime);
	
	pthread_cond_timedwait(cv, mp, &abstime);
}

struct timespec __ts_add(struct timespec time1, struct timespec time2)
{
	#define BILLION 1000000000L
	struct timespec result;
    
    result.tv_nsec = time1.tv_nsec + time2.tv_nsec;
    if (result.tv_nsec >= BILLION) {
        result.tv_sec++;
        result.tv_nsec -= BILLION;
    }

    return (result);
}

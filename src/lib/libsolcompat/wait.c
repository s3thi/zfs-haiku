#include <kernel/OS.h>
#include <time.h>
#include <pthread.h>

struct timespec __ts_add(struct timespec, struct timespec);

int pthread_cond_reltimedwait_np(pthread_cond_t *cv,  pthread_mutex_t *mp,
    const struct timespec *reltime)
{
	uint32 current_time = real_time_clock();

	struct timespec abstime;
	memset(&abstime, 0, sizeof abstime);
	abstime.tv_sec = current_time + reltime->tv_sec;
	abstime.tv_nsec = reltime->tv_nsec;

	return pthread_cond_timedwait(cv, mp, &abstime);
}

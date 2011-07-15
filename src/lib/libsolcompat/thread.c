#include <kernel/OS.h>
#include <thread.h>

int
thr_create(void *stack_base, size_t stack_size,
		   void *(*start_func) (void*), void *arg, long flags,
		   thread_t *new_thread_ID)
{
    pthread_t id;
    if (!new_thread_ID)
	new_thread_ID = &id;
	assert(stack_base == NULL);
	assert(stack_size == 0);
	assert((flags & ~THR_BOUND & ~THR_DETACHED) == 0);

	pthread_attr_t attr;
	pthread_attr_init(&attr);

	if(flags & THR_DETACHED)
		pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

	if (flags & THR_BOUND)
	    pthread_attr_setscope(&attr,PTHREAD_SCOPE_PROCESS);

	int ret = pthread_create(new_thread_ID, &attr, start_func, arg);

	pthread_attr_destroy(&attr);

	return ret;
}


int
thr_main(void)
{
	thread_id curThreadID = find_thread(NULL);
	
	if (curThreadID != B_OK)
		return -1;
	
	thread_info curThreadInfo;
	if (get_thread_info(curThreadID, &curThreadInfo) != B_OK)
		return -1;

	return curThreadInfo.team == curThreadID;
}

#ifndef _SOL_SYS_PTHREAD_RWLOCK_TRACKING_H
#define _SOL_SYS_PTHREAD_RWLOCK_TRACKING_H

#include <pthread.h>
#include <sys/list.h>
#include <kernel/OS.h>

typedef struct {
	thread_id id;
	list_node_t thread_id_node;
} thread_id_list_node_t;


typedef struct {
	pthread_rwlock_t rwlock;
	list_t rd_lock_list;
	pthread_mutex_t rd_lock_list_mtx;
} pthread_rwlock_tracking_t;


int pthread_rwlock_tracking_destroy(pthread_rwlock_tracking_t *lock);
int pthread_rwlock_tracking_init(pthread_rwlock_tracking_t *lock,
	const pthread_rwlockattr_t *attr);
int pthread_rwlock_tracking_rdlock(pthread_rwlock_tracking_t *lock);
int pthread_rwlock_tracking_tryrdlock(pthread_rwlock_tracking_t *lock);
int pthread_rwlock_tracking_wrlock(pthread_rwlock_tracking_t *lock);
int pthread_rwlock_tracking_trywrlock(pthread_rwlock_tracking_t *lock);
int pthread_rwlock_tracking_unlock(pthread_rwlock_tracking_t *lock);

int pthread_rwlock_tracking_rdlock_held(pthread_rwlock_tracking_t* lock);
int pthread_rwlock_tracking_wrlock_held(pthread_rwlock_tracking_t* lock);
int pthread_rwlock_tracking_rwlock_held(pthread_rwlock_tracking_t* lock);

void __pthread_rwlock_tracking_rdlock_common(pthread_rwlock_tracking_t *lock);




#endif /* _SOL_SYS_PTHREAD_RWLOCK_TRACKING_H */

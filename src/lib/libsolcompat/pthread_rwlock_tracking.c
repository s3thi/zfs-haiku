#include <pthread_rwlock_tracking.h>
#include <stdlib.h>


int
pthread_rwlock_tracking_destroy(pthread_rwlock_tracking_t *lock)
{
	pthread_mutex_lock(&(lock->rd_lock_list_mtx));
	list_destroy(&(lock->rd_lock_list));
	pthread_mutex_unlock(&(lock->rd_lock_list_mtx));
	
	pthread_mutex_destroy(&(lock->rd_lock_list_mtx));
	
	return pthread_rwlock_destroy(&(lock->rwlock));
}


int
pthread_rwlock_tracking_init(pthread_rwlock_tracking_t *lock,
	const pthread_rwlockattr_t *attr)
{
	list_create(&(lock->rd_lock_list), sizeof(thread_id_list_node_t),
		offsetof(thread_id_list_node_t, thread_id_node));

	pthread_mutex_init(&(lock->rd_lock_list_mtx), NULL);
	
	return pthread_rwlock_init(&(lock->rwlock), attr);
}


int
pthread_rwlock_tracking_rdlock(pthread_rwlock_tracking_t *lock)
{
	int retval = pthread_rwlock_rdlock(&(lock->rwlock));

	if (retval == 0)
		__pthread_rwlock_tracking_rdlock_common(lock);
	
	return retval;
}


int
pthread_rwlock_tracking_tryrdlock(pthread_rwlock_tracking_t *lock)
{
	int retval = pthread_rwlock_tryrdlock(&(lock->rwlock));

	if (retval == 0)
		__pthread_rwlock_tracking_rdlock_common(lock);

	return retval;
}


void
__pthread_rwlock_tracking_rdlock_common(pthread_rwlock_tracking_t *lock)
{
	thread_id_list_node_t *node = malloc(sizeof(thread_id_list_node_t));
	node->id = find_thread(NULL);

	pthread_mutex_lock(&(lock->rd_lock_list_mtx));
	list_insert_tail(&(lock->rd_lock_list), (void*)node);
	pthread_mutex_unlock(&(lock->rd_lock_list_mtx));
}


int pthread_rwlock_tracking_wrlock(pthread_rwlock_tracking_t *lock)
{
	return pthread_rwlock_wrlock(&(lock->rwlock));
}


int pthread_rwlock_tracking_trywrlock(pthread_rwlock_tracking_t *lock)
{
	return pthread_rwlock_trywrlock(&(lock->rwlock));
}


int
pthread_rwlock_tracking_unlock(pthread_rwlock_tracking_t *lock)
{
	thread_id curThreadID = find_thread(NULL);
	thread_id_list_node_t *node, *next_node;
	
	pthread_mutex_lock(&(lock->rd_lock_list_mtx));
		for (node = list_head(&(lock->rd_lock_list)); node; node = next_node) {
			next_node = list_next(&(lock->rd_lock_list), node);
			if (curThreadID == node->id) {
				list_remove(&(lock->rd_lock_list), node);
				break;
			}
		}
	pthread_mutex_unlock(&(lock->rd_lock_list_mtx));
	
	return pthread_rwlock_unlock(&(lock->rwlock));
}


int
pthread_rwlock_tracking_rdlock_held(pthread_rwlock_tracking_t* lock)
{
	if (list_is_empty(&(lock->rd_lock_list)))
		return 0;

	int ret = 0;
	thread_id curThreadID = find_thread(NULL);
	thread_id_list_node_t *node, *next_node;
	
	pthread_mutex_lock(&(lock->rd_lock_list_mtx));
		for (node = list_head(&(lock->rd_lock_list)); node; node = next_node) {
			next_node = list_next(&(lock->rd_lock_list), node);
			if (curThreadID == node->id)
				ret = 1;
		}
	pthread_mutex_unlock(&(lock->rd_lock_list_mtx));
	
	return ret;
}


int
pthread_rwlock_tracking_wrlock_held(pthread_rwlock_tracking_t* lock)
{
	// WARNING: uses private API, may break in future.
	// should i keep track of the write lock myself?
	return find_thread(NULL) == lock->rwlock.owner;
}


int
pthread_rwlock_tracking_rwlock_held(pthread_rwlock_tracking_t* lock)
{
	return pthread_rwlock_tracking_rdlock_held(lock) &&
		pthread_rwlock_tracking_wrlock_held(lock);
}

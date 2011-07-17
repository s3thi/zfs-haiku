#include <sys/zfs_context.h>
#include <pthread_rwlock_tracking.h>

int
__rw_read_held(krwlock_t *lock)
{
	return pthread_rwlock_tracking_rdlock_held(&(lock->rw_lock));
}

int
__rw_write_held(krwlock_t *lock)
{
	return pthread_rwlock_tracking_wrlock_held(&(lock->rw_lock));
}

int
__rw_lock_held(krwlock_t *lock)
{
	return pthread_rwlock_tracking_rwlock_held(&(lock->rw_lock));
}

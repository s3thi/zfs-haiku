#include <atomic.h>
#include <pthread.h>

static pthread_mutex_t atomic_cas_ptr_mtx;
 
static __attribute__((constructor)) void
atomic_cas_ptr_mtx_init(void)
{
    pthread_mutex_init(&atomic_cas_ptr_mtx, NULL);
}


void
atomic_add_32(volatile uint32_t *target, int32_t delta)
{
	atomic_add(target, delta);
}


void
atomic_add_64(volatile uint64_t *target, int64_t delta)
{
	atomic_add64(target, delta);
}


uint64_t
atomic_add_64_nv(volatile uint64_t *target, int64_t delta)
{
	atomic_add64(target, delta);
	return *target;
}


uint32_t
atomic_inc_32_nv(volatile uint32_t *target)
{
	atomic_add(target, 1);
	return *target;
}


void atomic_inc_64(volatile uint64_t *target)
{
	atomic_add64(target, 1);
}


uint32_t
atomic_dec_32_nv(volatile uint32_t *target)
{
	atomic_add(target, -1);
	return *target;
}


void
atomic_dec_64(volatile uint64_t *target)
{
	atomic_add64(target, -1);
}


uint32_t
atomic_cas_32(volatile uint32_t *target, uint32_t cmp, uint32_t newval)
{
	return atomic_test_and_set(target, newval, cmp);
}


uint64_t
atomic_cas_64(volatile uint64_t *target, uint64_t cmp, uint64_t newval)
{
	return atomic_test_and_set64(target, newval, cmp);
}


void *
atomic_cas_ptr(volatile void *target, void *cmp,  void *newval)
{
    void *oldval, **trg;

	pthread_mutex_lock(&atomic_cas_ptr_mtx);
	trg = ((void **)(uintptr_t)(volatile void *)(target));
	oldval = *trg;
	if (oldval == cmp)
		*trg = newval;	
	pthread_mutex_unlock(&atomic_cas_ptr_mtx);
	
	return (oldval);
}

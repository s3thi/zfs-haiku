#ifndef _SOL_SYS_ATOMIC_H
#define _SOL_SYS_ATOMIC_H

#include <sys/types.h>

/*
 * zfs-haiku: is it safe to just use #defines for these? In that case, we lose
 * some type information. None of the ZFS code _should_ be using the value
 * returned from, say, atomic_add_32 or, atomic_add_64, so it doesn't really
 * matter in practice. But the pedant in me can't let this slide. Better safe
 * than sorry.
 */

// Atomic add operations.
void atomic_add_32(volatile uint32_t *, int32_t);
void atomic_add_64(volatile uint64_t *, int64_t);
uint64_t atomic_add_64_nv(volatile uint64_t *, int64_t);

// Atomic increment operations.
uint32_t atomic_inc_32_nv(volatile uint32_t *);
void atomic_inc_64(volatile uint64_t *);

// Atomic decrement operations.
uint32_t atomic_dec_32_nv(volatile uint32_t *);
void atomic_dec_64(volatile uint64_t *);

/*
 * Atomic compare and swap operations.
 * If *arg1 == arg2, set *arg1 = arg3; return old value
 */
uint32_t atomic_cas_32(volatile uint32_t *, uint32_t, uint32_t);
uint64_t atomic_cas_64(volatile uint64_t *, uint64_t, uint64_t);
void *atomic_cas_ptr(volatile void *, void *, void *);

#endif /* _SOL_SYS_ATOMIC_H */

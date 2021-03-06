/*
 * CDDL HEADER START
 *
 * The contents of this file are subject to the terms of the
 * Common Development and Distribution License, Version 1.0 only
 * (the "License").  You may not use this file except in compliance
 * with the License.
 *
 * You can obtain a copy of the license at usr/src/OPENSOLARIS.LICENSE
 * or http://www.opensolaris.org/os/licensing.
 * See the License for the specific language governing permissions
 * and limitations under the License.
 *
 * When distributing Covered Code, include this CDDL HEADER in each
 * file and include the License file at usr/src/OPENSOLARIS.LICENSE.
 * If applicable, add the following below this CDDL HEADER, with the
 * fields enclosed by brackets "[]" replaced with your own identifying
 * information: Portions Copyright [yyyy] [name of copyright owner]
 *
 * CDDL HEADER END
 */
/*
 * Copyright 2006 Sun Microsystems, Inc.  All rights reserved.
 * Copyright 2006 Ricardo Correia.
 * Use is subject to license terms.
 */

#ifndef _SOL_THREAD_H
#define _SOL_THREAD_H

#include <pthread.h>
#include <pthread_rwlock_tracking.h>
#include <assert.h>

/*
 * Compatibility thread stuff needed for Solaris -> Haiku port
 */

typedef pthread_t thread_t;
typedef pthread_mutex_t mutex_t;
typedef pthread_cond_t cond_t;
typedef pthread_rwlock_tracking_t rwlock_t;

#define USYNC_THREAD 0

#define thr_self()               pthread_self()
#define thr_equal(a,b)           pthread_equal(a,b)
#define thr_join(t,d,s)          pthread_join(t,s)
#define thr_exit(r)              pthread_exit(r)
#define _mutex_init(l,f,a)       pthread_mutex_init(l,NULL)
#define _mutex_destroy(l)        pthread_mutex_destroy(l)
#define mutex_lock(l)            pthread_mutex_lock(l)
#define mutex_trylock(l)         pthread_mutex_trylock(l)
#define mutex_unlock(l)          pthread_mutex_unlock(l)
#define rwlock_init(l,f,a)       pthread_rwlock_tracking_init(l,NULL)
#define rwlock_destroy(l)        pthread_rwlock_tracking_destroy(l)
#define rw_rdlock(l)             pthread_rwlock_tracking_rdlock(l)
#define rw_wrlock(l)             pthread_rwlock_tracking_wrlock(l)
#define rw_tryrdlock(l)          pthread_rwlock_tracking_tryrdlock(l)
#define rw_trywrlock(l)          pthread_rwlock_tracking_trywrlock(l)
#define rw_unlock(l)             pthread_rwlock_tracking_unlock(l)
#define rw_read_held(l)          pthread_rwlock_tracking_rdlock_held(l)
#define rw_write_held(l)         pthread_rwlock_tracking_wrlock_held(l)
#define rw_lock_held(l)          pthread_rwlock_tracking_rwrlock_held(l)
#define cond_init(l,f,a)         pthread_cond_init(l,NULL)
#define cond_destroy(l)          pthread_cond_destroy(l)
#define cond_wait(l,m)           pthread_cond_wait(l,m)
#define cond_signal(l)           pthread_cond_signal(l)
#define cond_broadcast(l)        pthread_cond_broadcast(l)
#define cond_reltimedwait(c,m,r) pthread_cond_reltimedwait_np(c,m,r)

// Haiku's pthread_t is an opaque type. We need to call get_pthread_thread_id
// to get Haiku to give us an integral ID as opposed to a struct.
#define thr_id_integral(t)       get_pthread_thread_id(t)

// zfs-haiku: these constants might need some changes. TODO.
#define THR_BOUND     0x00000001  /* = PTHREAD_SCOPE_SYSTEM */
#define THR_NEW_LWP   0x00000002
#define THR_DETACHED  0x00000040  /* = PTHREAD_CREATE_DETACHED */
#define THR_SUSPENDED 0x00000080
#define THR_DAEMON    0x00000100

int thr_create(void *stack_base, size_t stack_size,
			   void *(*start_func) (void*), void *arg, long flags,
			   thread_t *new_thread_ID);

/*
 * The  thr_main() function  returns one of the following:
 *
 *		 1	if the calling thread is the main thread
 *		 0	if the calling thread is not the main thread
 *		-1	if libthread is not linked in or thread initialization has not
 *			completed
 */
int thr_main(void);

#endif

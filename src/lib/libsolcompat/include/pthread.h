#ifndef _SOL_PTHREAD_H
#define _SOL_PTHREAD_H

#include_next <pthread.h>

// zfs-haiku: uh, this is non portable. if things break,
// look here.
#define PTHREAD_ONCE_KEY_NP (pthread_key_t)(-1)

#endif /* _SOL_PTHREAD_H */

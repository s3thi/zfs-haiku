#ifndef _SOL_SYS_ASSERT_H
#define _SOL_SYS_ASSERT_H

#include_next <assert.h>

// zfs-haiku: this is bad, bad, bad.
#define __assert_c99 __assert_fail
#define __assert(a, b, c) __assert_fail(a, b, c, NULL)

#endif /* _SOL_SYS_ASSERT_H */


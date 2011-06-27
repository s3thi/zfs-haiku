#ifndef _SOL_SYS_UIO_H
#define _SOL_SYS_UIO_H

#include <sys/types.h>
#include <sys/feature_tests.h>
#include_next <sys/uio.h>

#define UIO_SYSSPACE 1

typedef struct iovec iovec_t;
typedef enum uio_rw { UIO_READ, UIO_WRITE } uio_rw_t;

#endif /* _SOL_SYS_UIO_H */


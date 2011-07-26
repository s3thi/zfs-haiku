#ifndef _SYS_ERRNO_H
#define	_SYS_ERRNO_H

#include_next <errno.h>

#define ERESTART B_TO_POSIX_ERROR(B_ERRORS_END + 1)
#define EBADE    B_TO_POSIX_ERROR(B_ERRORS_END + 2)
#define ENOTBLK  B_TO_POSIX_ERROR(B_ERRORS_END + 3)

#endif	/* _SYS_ERRNO_H */

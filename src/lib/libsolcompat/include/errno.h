#ifndef _SOL_ERRNO_H
#define _SOL_ERRNO_H

#include <sys/errno.h>

#ifdef __cplusplus
extern "C"
{
#endif

extern int *_errnop(void);
#define errno (*(_errnop()))

#ifdef __cplusplus
} /* "C" */
#endif 

#endif /* _SOL_ERRNO_H */


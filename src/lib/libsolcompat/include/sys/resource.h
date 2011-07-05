#ifndef _SOL_SYS_RESOURCE_H
#define _SOL_SYS_RESOURCE_H

#include_next <sys/resource.h>

typedef u_longlong_t    rlim64_t;

#define RLIM64_INFINITY     ((rlim64_t)-3)

#endif /* _SOL_SYS_RESOURCE_H */


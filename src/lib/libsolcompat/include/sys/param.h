#ifndef _SOLARIS_SYS_PARAM_H_
#define _SOLARIS_SYS_PARAM_H_

#include_next <sys/param.h>

#define MAXNAMELEN 256

// Number of bits per byte.
// TODO: is this defined in a system header somewhere?
#define NBBY 8

#endif /* _SOLARIS_SYS_PARAM_H_ */


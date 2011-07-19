#ifndef _SOLARIS_SYS_PARAM_H_
#define _SOLARIS_SYS_PARAM_H_

#include_next <sys/param.h>

#define MAXNAMELEN 256

// Number of bits per byte.
// zfs-haiku: is this defined in a system header somewhere?
#define NBBY 8
#define DEV_BSHIFT 9

/* 
 * The blocked devices are assumed to have DEV_BSIZE "sectors" 
 * and fragments must be some multiple of this size.
 */
#define DEV_BSIZE 512

#endif /* _SOLARIS_SYS_PARAM_H_ */


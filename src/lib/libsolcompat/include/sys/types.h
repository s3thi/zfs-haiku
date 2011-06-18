#ifndef _SOLARIS_SYS_TYPES_H_
#define _SOLARIS_SYS_TYPES_H_

#include_next <sys/types.h>
#include_next <stdint.h>

typedef	unsigned char	uchar_t;
typedef	unsigned short	ushort_t;
typedef	unsigned int	uint_t;
typedef	unsigned long	ulong_t;

#if defined(__XOPEN_OR_POSIX)
typedef enum { _B_FALSE, _B_TRUE } boolean_t;
#else
typedef enum { B_FALSE, B_TRUE } boolean_t;
#ifdef _KERNEL
#define	VALID_BOOLEAN(x)	(((x) == B_FALSE) || ((x) == B_TRUE))
#define	VOID2BOOLEAN(x)		(((uintptr_t)(x) == 0) ? B_FALSE : B_TRUE)
#endif /* _KERNEL */
#endif /* defined(__XOPEN_OR_POSIX) */

#ifdef _KERNEL
#define	BOOLEAN2VOID(x)		((x) ? 1 : 0)
#endif /* _KERNEL */

#endif /* _SOLARIS_SYS_TYPES_H_ */


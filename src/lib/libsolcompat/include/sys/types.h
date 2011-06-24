#ifndef _SOLARIS_SYS_TYPES_H_
#define _SOLARIS_SYS_TYPES_H_

#include_next <sys/types.h>
#include_next <stdint.h>
#include <sys/feature_tests.h>
#include <sys/param.h>

#ifndef _INT64_TYPE
#define _INT64_TYPE
#endif

/* POSIX extensions. */
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

typedef	long long		longlong_t;
typedef	unsigned long long	u_longlong_t;

/*
 * These types (t_{u}scalar_t) exist because the XTI/TPI/DLPI standards had
 * to use them instead of int32_t and uint32_t because DEC had
 * shipped 64-bit wide.
 */
#if defined(_LP64) || defined(_I32LPx)
typedef int32_t		t_scalar_t;
typedef uint32_t	t_uscalar_t;
#else
typedef long		t_scalar_t;	/* historical versions */
typedef unsigned long	t_uscalar_t;
#endif	/* defined(_LP64) || defined(_I32LPx) */

typedef short           pri_t;
typedef longlong_t      offset_t;
typedef u_longlong_t    u_offset_t;
typedef id_t            zoneid_t;

/*
 * Typedefs for dev_t components.
 */
#if defined(_LP64) || defined(_I32LPx)
typedef uint_t  major_t;    /* major part of device number */
typedef uint_t  minor_t;    /* minor part of device number */
#else
typedef ulong_t major_t;    /* (historical version) */
typedef ulong_t minor_t;    /* (historical version) */
#endif

#endif /* _SOLARIS_SYS_TYPES_H_ */


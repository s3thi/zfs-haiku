#ifndef _SOL_SYS_BYTEORDER_H
#define _SOL_SYS_BYTEORDER_H

#include <endian.h>

uint64_t htonll(uint64_t in);
uint64_t ntohll(uint64_t in);
uint32_t htonl(uint32_t in);
uint32_t ntohl(uint32_t in);
uint16_t htons(uint16_t in);
uint16_t ntohs(uint16_t in);

/*
 * Macros to reverse byte order
 */
#define	BSWAP_8(x)	((x) & 0xff)
#if !defined(__i386) && !defined(__amd64)
#define	BSWAP_16(x)	((BSWAP_8(x) << 8) | BSWAP_8((x) >> 8))
#define	BSWAP_32(x)	(((uint32_t)(x) << 24) | \
			(((uint32_t)(x) << 8) & 0xff0000) | \
			(((uint32_t)(x) >> 8) & 0xff00) | \
			((uint32_t)(x)  >> 24))
#else /* x86 */
#define	BSWAP_16(x)	htons(x)
#define	BSWAP_32(x)	htonl(x)
#endif	/* !__i386 && !__amd64 */

#if defined(_LP64) || defined(_LONGLONG_TYPE)
#if (!defined(__i386) && !defined(__amd64))
#define	BSWAP_64(x)	(((uint64_t)(x) << 56) | \
			(((uint64_t)(x) << 40) & 0xff000000000000ULL) | \
			(((uint64_t)(x) << 24) & 0xff0000000000ULL) | \
			(((uint64_t)(x) << 8)  & 0xff00000000ULL) | \
			(((uint64_t)(x) >> 8)  & 0xff000000ULL) | \
			(((uint64_t)(x) >> 24) & 0xff0000ULL) | \
			(((uint64_t)(x) >> 40) & 0xff00ULL) | \
			((uint64_t)(x)  >> 56))
#else /* x86 */
#define	BSWAP_64(x)	htonll(x)
#endif	/* !__i386 && !__amd64 */
#else /* no uint64_t */
#define	BSWAP_64(x)	((BSWAP_32(x) << 32) | BSWAP_32((x) >> 32))
#endif	/* _LP64 || _LONGLONG_TYPE  */

#endif /* _SOL_SYS_BYTEORDER_H */

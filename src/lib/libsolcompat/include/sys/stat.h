#ifndef _SOL_SYS_STAT_H
#define _SOL_SYS_STAT_H

#include_next <sys/stat.h>

// zfs-haiku: theoretically, this should work since haiku never needed
// a separate stat64 struct. The FS is already 64 bits.
#define stat64 stat
#define fstat64 fstat

// the Solaris stat.h says "XENIX definitions are not relevant to Solaris"
// right before the section containing these defines. Why?
#define S_IFDOOR 0xD000 /* door */
#define S_IFPORT 0xE000 /* event port */

#endif /* _SOL_SYS_STAT_H */


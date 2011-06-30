#ifndef _SOL_SYS_STAT_H
#define _SOL_SYS_STAT_H

#include_next <sys/stat.h>

// zfs-haiku: theoretically, this should work since haiku never needed
// a separate stat64 struct. The FS is already 64 bits.
#define stat64 stat;

#endif /* _SOL_SYS_STAT_H */


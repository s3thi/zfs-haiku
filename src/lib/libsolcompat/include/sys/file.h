#ifndef _SOL_SYS_FILE_H
#define _SOL_SYS_FILE_H

#include_next <sys/file.h>

// zfs-haiku: magic numbers are bad!
#define FREAD   1
#define FWRITE  2
#define FAPPEND 8

#define FCREAT  O_CREAT
#define FTRUNC  O_TRUNC
#define FOFFMAX O_LARGEFILE
#define FSYNC   O_SYNC
#define FDSYNC  O_DSYNC
#define FRSYNC  O_RSYNC
#define FEXCL   O_EXCL

#endif /* _SOL_SYS_FILE_H */


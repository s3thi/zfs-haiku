#ifndef _SOL_SYS_FILE_H
#define _SOL_SYS_FILE_H

#include_next <sys/file.h>

#define FREAD   O_RDONLY
#define FWRITE  O_WRONLY
#define FAPPEND  O_APPEND

#define FCREAT  O_CREAT
#define FTRUNC  O_TRUNC
#define FOFFMAX O_LARGEFILE
#define FSYNC   O_SYNC
#define FDSYNC  O_DSYNC
#define FRSYNC  O_RSYNC
#define FEXCL   O_EXCL

#endif /* _SOL_SYS_FILE_H */


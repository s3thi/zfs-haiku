#ifndef _SOL_SYS_ZONEID_H
#define _SOL_SYS_ZONEID_H

#include <sys/types.h>

#define GLOBAL_ZONEID 0
#define GLOBAL_ZONEID_NAME "global"

zoneid_t getzoneid();
zoneid_t getzoneidbyname(const char *name);
ssize_t getzonenamebyid(zoneid_t id, char *buf, size_t buflen);

#endif /* _SOL_SYS_ZONEID_H */

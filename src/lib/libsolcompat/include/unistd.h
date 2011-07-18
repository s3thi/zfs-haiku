#ifndef _SOL_UNISTD_H
#define _SOL_UNISTD_H

#ifdef __cplusplus
extern "C" {
#endif

#include_next <unistd.h>

int32_t gethostid();

#ifdef __cplusplus
}
#endif

#endif /* _SOL_UNISTD_H */

#include <sys/time.h>

/* zfs-haiku: we don't have nanosecond resolution, so this
 * will have to do for now. We need to multiply by 1000 because
 * a lot of code is dividing the value returned by this routine
 * by the NANOSEC constant.
 */
hrtime_t
gethrtime()
{
	return (hrtime_t)(system_time() * 1000);
}

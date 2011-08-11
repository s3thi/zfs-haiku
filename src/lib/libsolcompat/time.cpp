#include <sys/time.h>
#include <OS.h>

/* zfs-haiku: we don't have nanosecond resolution, so this
 * will have to do for now. We need to multiply by 1000 because
 * a lot of code is dividing the value returned by this routine
 * by the NANOSEC constant.
 */
extern "C" hrtime_t
gethrtime()
{
	hrtime_t time = (hrtime_t) system_time();
	time *= 1000;
	return time;
}

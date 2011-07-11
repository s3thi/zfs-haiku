#include <sys/time.h>

// zfs-haiku: we don't have nanosecond resolution, so this
// will have to do for now.
hrtime_t
gethrtime()
{
	return (hrtime_t)real_time_clock_usecs();
}

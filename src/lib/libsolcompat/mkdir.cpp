#include <storage/Directory.h>
#include <errno.h>


extern "C" int
mkdirp(const char *path, mode_t mode)
{
	status_t err = create_directory(path, mode);
	
	if (err = B_OK)
		return 0;
	else if (err == B_BAD_VALUE)
		errno = ENOENT;
	else if (err == B_NOT_ALLOWED)
		errno = EACCES;
	else if (err == B_NO_MEMORY)
		errno = ENOSPC;
	else if (err == B_NOT_A_DIRECTORY)
		errno = ENOTDIR;
	
	return -1;
}

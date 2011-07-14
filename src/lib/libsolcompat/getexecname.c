#include <kernel/image.h>
#include <string.h>
#include <stdlib.h>

const char*
getexecname(void)
{
	int32 cookie = 0;
	image_info info;
	get_next_image_info(0, &cookie, &info);
	
	char* execname = malloc(sizeof(char) * MAXPATHLEN);
	memcpy(execname, &info.name, sizeof(char) * MAXPATHLEN);
	
	return execname;
}

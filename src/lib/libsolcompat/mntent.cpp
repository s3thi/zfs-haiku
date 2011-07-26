#include <storage/VolumeRoster.h>
#include <storage/Directory.h>
#include <storage/StorageDefs.h>
#include <storage/Path.h>
#include <stdio.h>
#include <sys/mnttab.h>
#include <sys/types.h>
#include <string.h>
#include <stdlib.h>

#define MNTENT_MP_DEFAULT_OPTS "devices,exec,nonbmand,setuid,suid"
#define MNTENT_MP_UNKNOWN "unknown"
#define MNTENT_ALLOC_MP (char*)malloc(sizeof(char) * (buflen + 1))

extern "C" {

int
getmntent(FILE *fp, struct mnttab *mp)
{
	static BVolumeRoster roster;
	
	char buf[B_PATH_NAME_LENGTH];
	int buflen = 0;
	BVolume volume;
	BDirectory rootDir;
	BEntry rootDirEntry;
	BPath rootDirPath;
	
	if (roster.GetNextVolume(&volume) != B_NO_ERROR)
		return -1;
	
	// volume name
	volume.GetName(buf);
	buflen = strlen(buf);
	
	if (buflen == 0) {
		buflen = strlen(MNTENT_MP_UNKNOWN);
		strlcpy(buf, MNTENT_MP_UNKNOWN, buflen + 1);
	}
	
	mp->mnt_special = MNTENT_ALLOC_MP;
	strlcpy(mp->mnt_special, buf, buflen+1);
	
	// mount point
	if (volume.GetRootDirectory(&rootDir) != B_OK)
		return -1;
	if (rootDir.GetEntry(&rootDirEntry) != B_OK)
		return -1;
	if (rootDirEntry.GetPath(&rootDirPath) != B_OK)
		return -1;
	
	buflen = strlen(rootDirPath.Path());
	mp->mnt_mountp = MNTENT_ALLOC_MP;
	strlcpy(mp->mnt_mountp, rootDirPath.Path(), buflen + 1);
	
	// partition type.
	fs_info info;
	if (fs_stat_dev(volume.Device(), &info) != B_OK)
		return -1;
	
	buflen = strlen(info.fsh_name);
	mp->mnt_fstype = MNTENT_ALLOC_MP;
	strlcpy(mp->mnt_fstype, info.fsh_name, buflen+1);
	
	// fs options. set default options for all file systems for now.
	buflen = strlen(MNTENT_MP_DEFAULT_OPTS);
	// malloc extra space for ro/rw
	mp->mnt_mntopts = (char*)malloc(sizeof(char) * buflen+2+1);
	strlcpy(mp->mnt_mntopts, MNTENT_MP_DEFAULT_OPTS, buflen + 2 + 1);
	strcat(mp->mnt_mntopts, volume.IsReadOnly() ? ",ro":",rw");
	
	// mount time. no idea how i can get this. set it to 0 for now.
	buflen = 1;
	mp->mnt_time = MNTENT_ALLOC_MP;
	strlcpy(mp->mnt_time, "0", buflen + 1);
	
	return 0;
}

} /* "C" */

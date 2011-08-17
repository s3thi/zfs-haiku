typedef unsigned int uint_t;

#include <storage/VolumeRoster.h>
#include <storage/Directory.h>
#include <storage/StorageDefs.h>
#include <storage/Path.h>
#include <cstdio>
#include <sys/mnttab.h>
#include <sys/mntent.h>
#include <sys/types.h>
#include <string.h>
#include <cstdlib>
#include <ctype.h>

#define MNTENT_MP_DEFAULT_OPTS "devices,exec,nonbmand,setuid,suid"
#define MNTENT_MP_UNKNOWN "unknown"

extern "C" {

int
getmntent_haiku(int* cookie, struct mnttab* mp)
{
	BVolumeRoster roster;
	
	char buf[B_PATH_NAME_LENGTH];
	int buflen = 0;
	BVolume volume;
	BDirectory rootDir;
	BEntry rootDirEntry;
	BPath rootDirPath;
	
	roster.Rewind();
	for (int i = 0; i <= *cookie; i++)
		if (roster.GetNextVolume(&volume) != B_NO_ERROR)
			return -1;
	
	// volume name
	volume.GetName(buf);
	buflen = strlen(buf);
	
	if (buflen == 0) {
		buflen = strlen(MNTENT_MP_UNKNOWN);
		strlcpy(buf, MNTENT_MP_UNKNOWN, buflen + 1);
	}
	
	mp->mnt_special = (char* )malloc(sizeof(char) * (buflen+1));
	strlcpy(mp->mnt_special, buf, buflen+1);
	
	// mount point
	if (volume.GetRootDirectory(&rootDir) != B_OK)
		return -1;
	if (rootDir.GetEntry(&rootDirEntry) != B_OK)
		return -1;
	if (rootDirEntry.GetPath(&rootDirPath) != B_OK)
		return -1;
	
	buflen = strlen(rootDirPath.Path());
	mp->mnt_mountp = (char* )malloc(sizeof(char) * (buflen+1));
	strlcpy(mp->mnt_mountp, rootDirPath.Path(), buflen + 1);
	
	// partition type.
	fs_info info;
	if (fs_stat_dev(volume.Device(), &info) != B_OK)
		return -1;
	
	buflen = strlen(info.fsh_name);
	mp->mnt_fstype = (char* )malloc(sizeof(char) * (buflen+1));
	strlcpy(mp->mnt_fstype, info.fsh_name, buflen+1);
	
	// fs options. set default options for all file systems for now.
	buflen = strlen(MNTENT_MP_DEFAULT_OPTS);
	mp->mnt_mntopts = (char* )malloc(sizeof(char) * (buflen+2+1)); // extra space for ro/rw
	strlcpy(mp->mnt_mntopts, MNTENT_MP_DEFAULT_OPTS, buflen + 2 + 1);
	strcat(mp->mnt_mntopts, volume.IsReadOnly() ? ",ro":",rw");
	
	// mount time. no idea how i can get this. set it to 0 for now.
	buflen = 1;
	mp->mnt_time = (char* )malloc(sizeof(char) * (buflen+1));
	strlcpy(mp->mnt_time, "0", buflen + 1);
	
	(*cookie)++;
	
	return 0;
}


char*
hasmntopt(struct mnttab *mnt, char *opt)
{
	char tmpopts[MNT_LINE_MAX];
	char *f, *opts = tmpopts;
	size_t	len;

	if (mnt->mnt_mntopts == NULL)
		return (NULL);
	(void) strcpy(opts, mnt->mnt_mntopts);
	len = strlen(opt);
	f = mntopt(&opts);
	for (; *f; f = mntopt(&opts)) {
		/*
		 * Match only complete substrings. For options
		 * which use a delimiter (such as 'retry=3'),
		 * treat the delimiter as the end of the substring.
		 */
		if (strncmp(opt, f, len) == 0 &&
		    (f[len] == '\0' || !isalnum(f[len])))
			return (f - tmpopts + mnt->mnt_mntopts);
	}
	return (NULL);
}

char*
mntopt(char **p)
{
	char *cp = *p;
	char *retstr;

	while (*cp && isspace(*cp))
		cp++;

	retstr = cp;
	while (*cp && *cp != ',')
		cp++;

	if (*cp) {
		*cp = '\0';
		cp++;
	}

	*p = cp;
	return (retstr);
}

} /* extern "C" */

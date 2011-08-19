typedef unsigned int uint_t;

#include <storage/VolumeRoster.h>
#include <storage/Directory.h>
#include <storage/StorageDefs.h>
#include <storage/Path.h>
#include <support/Locker.h>
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
	static BLocker mntent_locker;
	mntent_locker.Lock();
	
	int ret = -1;
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
			goto bail;
	
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
	if (volume.GetRootDirectory(&rootDir) != B_OK ||
		rootDir.GetEntry(&rootDirEntry) != B_OK   ||
		rootDirEntry.GetPath(&rootDirPath) != B_OK)
		goto bail;
	
	buflen = strlen(rootDirPath.Path());
	mp->mnt_mountp = (char* )malloc(sizeof(char) * (buflen+1));
	strlcpy(mp->mnt_mountp, rootDirPath.Path(), buflen + 1);
	
	// partition type.
	fs_info info;
	if (fs_stat_dev(volume.Device(), &info) != B_OK)
		goto bail;
	
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
	ret = 0; /* success! */

bail:
	mntent_locker.Unlock();
	return ret;
}


int
getmntany_haiku(int* cookie, struct mnttab *mgetp, struct mnttab *mrefp)
{
	struct mnttab current;
	while (getmntent_haiku(cookie, &current) != -1) {
		/* remember, strcmp() returns 0 on match */
		if (mrefp->mnt_special && strcmp(mrefp->mnt_special, current.mnt_special))
			continue;
		if (mrefp->mnt_mountp && strcmp(mrefp->mnt_mountp, current.mnt_mountp))
			continue;
		if (mrefp->mnt_fstype && strcmp(mrefp->mnt_fstype, current.mnt_fstype))
			continue;
		if (mrefp->mnt_mntopts && strcmp(mrefp->mnt_mntopts, current.mnt_mntopts))
			continue;
		if (mrefp->mnt_time && strcmp(mrefp->mnt_time, current.mnt_time))
			continue;
		
		/* if we've reached here, it's a match. fill up the struct. */
		memcpy(mgetp, &current, sizeof(struct mnttab));
		return 0;
	}
	
	return -1;
}


int
getextmntent_haiku(int* cookie, struct extmnttab *mp, int len)
{
	static BLocker extmntent_locker;
	extmntent_locker.Lock();
	
	BVolumeRoster roster;
	BVolume volume;
	int ret = -1;

	roster.Rewind();
	for (int i = 0; i <= *cookie; i++)
		if (roster.GetNextVolume(&volume) != B_NO_ERROR)
			return -1;

	if (getmntent_haiku(cookie, (struct mnttab*)mp) == 0) {
		mp->mnt_major = volume.Device();
		mp->mnt_minor = volume.Device();
		
		ret = 0;
	}
	
	extmntent_locker.Unlock();
	return ret;
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

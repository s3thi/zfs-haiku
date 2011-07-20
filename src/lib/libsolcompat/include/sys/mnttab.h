#ifndef _SOL_SYS_MNTTAB_H
#define _SOL_SYS_MNTTAB_H

#define	MNT_LINE_MAX 1024

struct mnttab {
	char	*mnt_special;
	char	*mnt_mountp;
	char	*mnt_fstype;
	char	*mnt_mntopts;
	char	*mnt_time;
};

/*
 * NOTE: fields in extmnttab should match struct mnttab till new fields
 * are encountered, this allows hasmntopt to work properly when its arg is
 * a pointer to an extmnttab struct cast to a mnttab struct pointer.
 */

struct extmnttab {
	char *mnt_special;
	char *mnt_mountp;
	char *mnt_fstype;
	char *mnt_mntopts;
	uint_t mnt_major;
	uint_t mnt_minor;
};

#endif /* _SOL_SYS_MNTTAB_H */

#ifndef _SOL_SYS_MNTTAB_H
#define _SOL_SYS_MNTTAB_H

struct mnttab {
	char	*mnt_special;
	char	*mnt_mountp;
	char	*mnt_fstype;
	char	*mnt_mntopts;
	char	*mnt_time;
};

#endif /* _SOL_SYS_MNTTAB_H */

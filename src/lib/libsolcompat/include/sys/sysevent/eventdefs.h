#ifndef _SYS_EVENTDEFS_H
#define _SYS_EVENTDEFS_H

/*
* ZFS subclass definitions.  supporting attributes (name/value paris) are found
* in sys/fs/zfs.h
*/
#define ESC_ZFS_RESILVER_START  "ESC_ZFS_resilver_start"
#define ESC_ZFS_RESILVER_FINISH "ESC_ZFS_resilver_finish"
#define ESC_ZFS_VDEV_REMOVE "ESC_ZFS_vdev_remove"
#define ESC_ZFS_POOL_DESTROY    "ESC_ZFS_pool_destroy"
#define ESC_ZFS_VDEV_CLEAR  "ESC_ZFS_vdev_clear"
#define ESC_ZFS_VDEV_CHECK  "ESC_ZFS_vdev_check"
#define ESC_ZFS_CONFIG_SYNC "ESC_ZFS_config_sync"
#define ESC_ZFS_SCRUB_START "ESC_ZFS_scrub_start"
#define ESC_ZFS_SCRUB_FINISH    "ESC_ZFS_scrub_finish"
#define ESC_ZFS_VDEV_SPARE  "ESC_ZFS_vdev_spare"
#define ESC_ZFS_BOOTFS_VDEV_ATTACH  "ESC_ZFS_bootfs_vdev_attach"

#endif /* _SYS_EVENTDEFS_H */


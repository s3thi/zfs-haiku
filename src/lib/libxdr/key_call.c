#include <mt.h>
#include <rpc_mt.h>
#include <sys/stat.h>

static pthread_key_t key_call_key = PTHREAD_ONCE_KEY_NP;

struct key_call_private {
	CLIENT	*client;	/* Client handle */
	pid_t	pid;		/* process-id at moment of creation */
	int		fd;			/* client handle fd */
	dev_t	rdev;		/* device client handle is using */
};

static int check_rdev(struct key_call_private *);


static void
key_call_destroy(void *vp)
{
    struct key_call_private *kcp = (struct key_call_private *)vp;
    
    if (kcp != NULL && kcp->client != NULL) {
        (void) check_rdev(kcp);
        clnt_destroy(kcp->client);
        free(kcp);
    }   
}   


void
_key_call_fini(void)
{
    struct key_call_private *kcp;

    if ((kcp = pthread_getspecific(key_call_key)) != NULL) {
        key_call_destroy(kcp);
        (void) pthread_setspecific(key_call_key, NULL);
    }
}


static int
check_rdev(struct key_call_private *kcp)
{
	struct stat stbuf;

	if (kcp->fd == -1)
		return (1);    /* can't check it, assume it is okay */

	if (fstat(kcp->fd, &stbuf) == -1) {
		// zfs-haiku: TODO: enable this later
		// syslog(LOG_DEBUG, "keyserv_client:  can't stat %d", kcp->fd);
		/* could be because file descriptor was closed */
		/* it's not our file descriptor, so don't try to close it */
		clnt_control(kcp->client, CLSET_FD_NCLOSE, NULL);

		return (0);
	}
	if (kcp->rdev != stbuf.st_rdev) {
		//syslog(LOG_DEBUG,
		//    "keyserv_client:  fd %d changed, old=0x%x, new=0x%x",
		//    kcp->fd, kcp->rdev, stbuf.st_rdev);
		/* it's not our file descriptor, so don't try to close it */
		clnt_control(kcp->client, CLSET_FD_NCLOSE, NULL);
		return (0);
	}
	return (1);    /* fd is okay */
}

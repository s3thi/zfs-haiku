#ifndef _SOL_RPC_CLNT_H
#define _SOL_RPC_CLNT_H

#include <rpc/clnt_stat.h>
#include <rpc/auth.h>

struct rpc_err {
	enum clnt_stat re_status;
	union {
		struct {
			int RE_errno;	/* related system error */
			int RE_t_errno;	/* related tli error number */
		} RE_err;
		enum auth_stat RE_why;	/* why the auth error occurred */
		struct {
			rpcvers_t low;	/* lowest verion supported */
			rpcvers_t high;	/* highest verion supported */
		} RE_vers;
		struct {		/* maybe meaningful if RPC_FAILED */
			int32_t s1;
			int32_t s2;
		} RE_lb;		/* life boot & debugging only */
	} ru;
#define	re_errno	ru.RE_err.RE_errno
#define	re_terrno	ru.RE_err.RE_t_errno
#define	re_why		ru.RE_why
#define	re_vers		ru.RE_vers
#define	re_lb		ru.RE_lb
};

struct rpc_createerr {
	enum clnt_stat cf_stat;
	struct rpc_err cf_error; /* useful when cf_stat == RPC_PMAPFAILURE */
};


/*
 * Client rpc handle.
 * Created by individual implementations, see e.g. rpc_udp.c.
 * Client is responsible for initializing auth, see e.g. auth_none.c.
 */
typedef struct {
	AUTH	*cl_auth;			/* authenticator */
	struct clnt_ops {
		enum clnt_stat	(*cl_call)();	/* call remote procedure */
		void		(*cl_abort)();	/* abort a call */
		void		(*cl_geterr)();	/* get specific error code */
		bool_t		(*cl_freeres)(); /* frees results */
		void		(*cl_destroy)(); /* destroy this structure */
		bool_t		(*cl_control)(); /* the ioctl() of rpc */
	} *cl_ops;
	caddr_t			cl_private;	/* private stuff */
} CLIENT;

#define CLSET_FD_NCLOSE 9
#define	CLNT_DESTROY(rh)	((*(rh)->cl_ops->cl_destroy)(rh))
#define	clnt_destroy(rh)	((*(rh)->cl_ops->cl_destroy)(rh))

/*
 * bool_t
 * CLNT_CONTROL(cl, request, info)
 *	CLIENT *cl;
 *	u_int request;
 *	char *info;
 */
#define	CLNT_CONTROL(cl, rq, in) ((*(cl)->cl_ops->cl_control)(cl, rq, in))
#define	clnt_control(cl, rq, in) ((*(cl)->cl_ops->cl_control)(cl, rq, in))

#endif /* _SOL_RPC_CLNT_H */

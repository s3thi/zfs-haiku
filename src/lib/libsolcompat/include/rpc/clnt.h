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

#endif /* _SOL_RPC_CLNT_H */

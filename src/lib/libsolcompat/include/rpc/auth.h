#ifndef _SOL_RPC_AUTH_H
#define _SOL_RPC_AUTH_H

/*
 * Status returned from authentication check
 */
enum auth_stat {
	AUTH_OK = 0,
	/*
	 * failed at remote end
	 */
	AUTH_BADCRED = 1,		/* bogus credentials (seal broken) */
	AUTH_REJECTEDCRED = 2,		/* client should begin new session */
	AUTH_BADVERF = 3,		/* bogus verifier (seal broken) */
	AUTH_REJECTEDVERF = 4,		/* verifier expired or was replayed */
	AUTH_TOOWEAK = 5,		/* rejected due to security reasons */
	/*
	 * failed locally
	 */
	AUTH_INVALIDRESP = 6,		/* bogus response verifier */
	AUTH_FAILED = 7,			/* some unknown reason */
	/*
	 * kerberos errors
	 */
	AUTH_KERB_GENERIC = 8,		/* kerberos generic error */
	AUTH_TIMEEXPIRE = 9,		/* time of credential expired */
	AUTH_TKT_FILE = 10,		/* something wrong with ticket file */
	AUTH_DECODE = 11,		/* can't decode authenticator */
	AUTH_NET_ADDR = 12,		/* wrong net address in ticket */
	/*
	 * GSS related errors
	 */
	RPCSEC_GSS_NOCRED = 13,		/* no credentials for user */
	RPCSEC_GSS_FAILED = 14		/* GSS failure, credentials deleted */
};
typedef enum auth_stat AUTH_STAT;

#endif /* _SOL_RPC_AUTH_H */

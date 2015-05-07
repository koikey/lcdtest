#ifndef PRESS_KEY_HEADER
#define PRESS_KEY_HEADER

/* Return value type define */
#define RET_PROC_SUCCESS		(0)
#define RET_PROC_FAILURE		(-1)

/* Key type define */
#define KEY_TYPE_UP			(0x0001u)
#define KEY_TYPE_DOWN      		(0x0002u)
#define KEY_TYPE_LEFT      		(0x0004u)
#define KEY_TYPE_RIGHT     		(0x0008u)
#define KEY_TYPE_ENTER     		(0x0010u)
#define KEY_TYPE_CLEAR     		(0x0020u)

/* Key event type define */
#define KEY_EVT_PRESSED			(0x1000u)
#define KEY_EVT_RELEASED		(0x2000u)

/* Max length of command line */
#define MAX_CMDREQ_LEN			(128)
#define MAX_CMDRES_LEN			(256)
#define MAX_CMDTYPE_LEN			(5)	/* Key type (Script arg1 string) */
#define MAX_CMDEVT_LEN			(5)	/* Event type. (Script arg2 string) */

/* public api */
extern int presskey( int key_type, int evt_type );

#endif /* PRESS_KEY_HEADER */

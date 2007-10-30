 * Copyright (c) 2003-2007 Apple Inc. All rights reserved.
/*
 * NOTICE: This file was modified by SPARTA, Inc. in 2005 to introduce
 * support for mandatory and extensible security protections.  This notice
 * is included in support of clause 2.2 (b) of the Apple Public License,
 * Version 2.0.
 */
#if CONFIG_MACF
#include <security/mac_framework.h>
#endif

static lck_grp_t	*bsm_audit_grp;
static lck_attr_t	*bsm_audit_attr;
static lck_grp_attr_t	*bsm_audit_grp_attr;
static lck_mtx_t	*bsm_audit_mutex;
	bsm_audit_grp_attr = lck_grp_attr_alloc_init();
	bsm_audit_grp = lck_grp_alloc_init("BSM Audit", bsm_audit_grp_attr);
	bsm_audit_attr = lck_attr_alloc_init();
	bsm_audit_mutex = lck_mtx_alloc_init(bsm_audit_grp, bsm_audit_attr);
	lck_mtx_lock(bsm_audit_mutex);
	lck_mtx_unlock(bsm_audit_mutex);
		lck_mtx_lock(bsm_audit_mutex);
			lck_mtx_unlock(bsm_audit_mutex);
		lck_mtx_unlock(bsm_audit_mutex);
		lck_mtx_lock(bsm_audit_mutex);
		lck_mtx_unlock(bsm_audit_mutex);
	lck_mtx_lock(bsm_audit_mutex);
	lck_mtx_unlock(bsm_audit_mutex);
 * to reduce the generated code size.
#if CONFIG_MACF
#define MAC_VNODE1_LABEL_TOKEN						\
	do {								\
		if (ar->ar_vnode1_mac_labels != NULL) {			\
			tok = au_to_text(ar->ar_vnode1_mac_labels);	\
			kau_write(rec, tok);				\
		}							\
	} while (0)

#define MAC_VNODE2_LABEL_TOKEN						\
	do {								\
		if (ar->ar_vnode2_mac_labels != NULL) {			\
			tok = au_to_text(ar->ar_vnode2_mac_labels);	\
			kau_write(rec, tok);				\
		}							\
	} while (0)
#else
#define MAC_VNODE1_LABEL_TOKEN
#define MAC_VNODE2_LABEL_TOKEN
#endif
			MAC_VNODE1_LABEL_TOKEN;			\
			MAC_VNODE1_LABEL_TOKEN;			\
			tok = kau_to_attr32(&ar->ar_arg_vnode2);\
			MAC_VNODE2_LABEL_TOKEN;			\
				MAC_VNODE1_LABEL_TOKEN;		\
#define PROCESS_MAC_TOKENS						\
	do {								\
		if (ar->ar_valid_arg & ARG_MAC_STRING) {		\
			tok = au_to_text(ar->ar_arg_mac_string);	\
			kau_write(rec, tok);				\
		}							\
	} while (0)							\

	struct au_token *tok = NULL, *subj_tok;
	case AUE_MAC_GETFSSTAT:
	case AUE_EXTATTR_GET_FD:
	case AUE_EXTATTR_LIST_FD:
	case AUE_EXTATTR_SET_FD:
	case AUE_EXTATTR_DELETE_FD:
	case AUE_GETLCID:
		tok = au_to_arg32(1, "pid", (u_int32_t)ar->ar_arg_pid);
		kau_write(rec, tok);
		break;

	case AUE_SETLCID:
		tok = au_to_arg32(1, "pid", (u_int32_t)ar->ar_arg_pid);
		kau_write(rec, tok);
		tok = au_to_arg32(2, "lcid", (u_int32_t)ar->ar_arg_value);
		kau_write(rec, tok);
		break;

#if CONFIG_MACF
	case AUE_MAC_MOUNT:
		PROCESS_MAC_TOKENS;
		/* fall through */
#endif
			u_int ctr;

		tok = au_to_arg64(2, "shmaddr", ar->ar_arg_svipc_addr);
		tok = au_to_arg64(1, "shmaddr", ar->ar_arg_svipc_addr);
			perm._seq = 0;
			perm._key = 0;
			perm._seq = 0;
			perm._key = 0;
			int ctr;

	case AUE_EXTATTR_GET_FILE:
	case AUE_EXTATTR_SET_FILE:
	case AUE_EXTATTR_LIST_FILE:
	case AUE_EXTATTR_DELETE_FILE:
	case AUE_EXTATTR_GET_LINK:
	case AUE_EXTATTR_SET_LINK:
	case AUE_EXTATTR_LIST_LINK:
	case AUE_EXTATTR_DELETE_LINK:
		UPATH1_KPATH1_VNODE1_TOKENS;
		break;

#if CONFIG_MACF
	case AUE_MAC_GET_FILE:
	case AUE_MAC_SET_FILE:
	case AUE_MAC_GET_LINK:
	case AUE_MAC_SET_LINK:
	case AUE_MAC_GET_MOUNT:
		UPATH1_KPATH1_VNODE1_TOKENS;
		PROCESS_MAC_TOKENS;
		break;

	case AUE_MAC_GET_FD:
	case AUE_MAC_SET_FD:
		FD_KPATH1_VNODE1_TOKENS;
		PROCESS_MAC_TOKENS;
		break;

	case AUE_MAC_SYSCALL:
		PROCESS_MAC_TOKENS;
		tok = au_to_arg32(3, "call", ar->ar_arg_value);
		kau_write(rec, tok);
		break;

	case AUE_MAC_EXECVE:
		UPATH1_KPATH1_VNODE1_TOKENS;
		PROCESS_MAC_TOKENS;
		break;

	case AUE_MAC_GET_PID:
		tok = au_to_arg32(1, "pid", (u_int32_t)ar->ar_arg_pid);
		kau_write(rec, tok);
		PROCESS_MAC_TOKENS;
		break;

	case AUE_MAC_GET_LCID:
		tok = au_to_arg32(1, "lcid", (u_int32_t)ar->ar_arg_value);
		kau_write(rec, tok);
		PROCESS_MAC_TOKENS;
		break;

	case AUE_MAC_GET_PROC:
	case AUE_MAC_SET_PROC:
	case AUE_MAC_GET_LCTX:
	case AUE_MAC_SET_LCTX:
		PROCESS_MAC_TOKENS;
		break;
#endif

#if CONFIG_MACF
	do {
		/* Convert the audit data from the MAC policies */
		struct mac_audit_record *mar;
		
		LIST_FOREACH(mar, ar->ar_mac_records, records) {
			switch (mar->type) {
				case MAC_AUDIT_DATA_TYPE:
					tok = au_to_data(AUP_BINARY, AUR_BYTE,
					    mar->length, mar->data);
					break;
				case MAC_AUDIT_TEXT_TYPE:
					tok = au_to_text((char*) mar->data);
					break;
				default:
					/*
					 * XXX: we can either continue,
					 * skipping this particular entry,
					 * or we can pre-verify the list and
					 * abort before writing any records
					 */
					printf("kaudit_to_bsm(): BSM conversion requested for unknown mac_audit data type %d\n",
					    mar->type);
			}

			kau_write(rec, tok);
		}
	} while (0);
#endif


#if CONFIG_MACF
	if (ar->ar_cred_mac_labels != NULL) {
		tok = au_to_text(ar->ar_cred_mac_labels);
		kau_write(rec, tok);
	}
#endif

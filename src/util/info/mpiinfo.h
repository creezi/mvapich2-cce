/* -*- Mode: C; c-basic-offset:4 ; -*- */
/*
 *  (C) 2001 by Argonne National Laboratory.
 *      See COPYRIGHT in top-level directory.
 */
extern void MPIU_Info_free( MPID_Info *info_ptr );
extern int MPIU_Info_alloc(MPID_Info **info_p_p);

/* TICKET_271: add new routine to dup info objects */
extern int MPIU_Info_dup(MPID_Info *info_ptr, MPID_Info **newinfo_p_p);

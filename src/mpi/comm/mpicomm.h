/* -*- Mode: C; c-basic-offset:4 ; -*- */
/*  
 *  (C) 2001 by Argonne National Laboratory.
 *      See COPYRIGHT in top-level directory.
 */

/* Function prototypes for communicator helper functions */
/* The MPIR_Get_contextid and void MPIR_Free_contextid routines are in
   mpiimpl.h so that the device may use them */
/* int MPIR_Get_contextid( MPID_Comm *, MPIR_Context_id_t * ); */
int MPIR_Get_intercomm_contextid( MPID_Comm *, MPIR_Context_id_t *, MPIR_Context_id_t * );
/* void MPIR_Free_contextid( MPIR_Context_id_t ); */

/* TICKET_271: create default info hints */
int MPIR_Comm_get_default_info(MPID_Info **info_p_p);

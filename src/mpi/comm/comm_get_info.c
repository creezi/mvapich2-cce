/* -*- Mode: C; c-basic-offset:4 ; -*- */
/*
 *
 *  (C) 2001 by Argonne National Laboratory.
 *      See COPYRIGHT in top-level directory.
 */

#include "mpiimpl.h"

/* TICKET_271: add new get_info routine for comm object */

/* -- Begin Profiling Symbol Block for routine MPI_Comm_get_info */
#if defined(HAVE_PRAGMA_WEAK)
#pragma weak MPI_Comm_get_info = PMPI_Comm_get_info
#elif defined(HAVE_PRAGMA_HP_SEC_DEF)
#pragma _HP_SECONDARY_DEF PMPI_Comm_get_info  MPI_Comm_get_info
#elif defined(HAVE_PRAGMA_CRI_DUP)
#pragma _CRI duplicate MPI_Comm_get_info as PMPI_Comm_get_info
#endif
/* -- End Profiling Symbol Block */

/* Define MPICH_MPI_FROM_PMPI if weak symbols are not supported to build
   the MPI routines */
#ifndef MPICH_MPI_FROM_PMPI
#undef MPI_Comm_get_info
#define MPI_Comm_get_info PMPI_Comm_get_info

void MPIR_Comm_get_info_impl(MPID_Comm *comm_ptr, char *comm_name, int *resultlen)
{
    /* The user must allocate a large enough section of memory */
    MPIU_Strncpy(comm_name, comm_ptr->name, MPI_MAX_OBJECT_NAME);
    *resultlen = (int)strlen(comm_name);
    return;
}

#endif

#undef FUNCNAME
#define FUNCNAME MPI_Comm_get_info
#undef FCNAME
#define FCNAME "MPI_Comm_get_info"

/*@
  MPI_Comm_get_info - Get the MPI Info object associated with the communicator

  Input Parameter:
. comm - Communicator to get name of (handle)

  Output Parameters:
+ info_used - new info object containing hints associated with window (handle)

 Notes:
 The info object is a duplicate of the info currently associated with
 the MPI window, and should be freed with 'MPI_Info_free' when
 it is no longer needed.

.N COMMNULL

.N ThreadSafeNoUpdate

.N Fortran

.N Errors
.N MPI_SUCCESS
.N MPI_ERR_COMM
@*/
int MPI_Comm_get_info(MPI_Comm comm, MPI_Info *info_used)
{
    int mpi_errno = MPI_SUCCESS;
    MPID_Comm *comm_ptr = NULL;
    MPID_Info *info_ptr;
    MPID_MPI_STATE_DECL(MPID_STATE_MPI_COMM_GET_NAME);

    MPIR_ERRTEST_INITIALIZED_ORDIE();
    
    MPID_MPI_FUNC_ENTER(MPID_STATE_MPI_COMM_GET_NAME);

    /* Validate parameters, especially handles needing to be converted */
#   ifdef HAVE_ERROR_CHECKING
    {
        MPID_BEGIN_ERROR_CHECKS;
        {
	    MPIR_ERRTEST_COMM(comm, mpi_errno);
            if (mpi_errno != MPI_SUCCESS) goto fn_fail;
	}
        MPID_END_ERROR_CHECKS;
    }
#   endif /* HAVE_ERROR_CHECKING */

    /* Validate parameters and objects (post conversion) */
    MPID_Comm_get_ptr( comm, comm_ptr );
    
    /* Validate parameters and objects (post conversion) */
#   ifdef HAVE_ERROR_CHECKING
    {
        MPID_BEGIN_ERROR_CHECKS;
        {
	    MPID_Comm_valid_ptr( comm_ptr, mpi_errno );

	    /* If comm_ptr is not valid, it will be reset to null */
//	    MPIR_ERRTEST_ARGNULL( comm_name, "comm_name", mpi_errno );
//	    MPIR_ERRTEST_ARGNULL( resultlen, "resultlen", mpi_errno );
            if (mpi_errno) goto fn_fail;
        }
        MPID_END_ERROR_CHECKS;
    }
#   endif /* HAVE_ERROR_CHECKING */

    /* ... body of routine ...  */

    mpi_errno = MPIU_Info_dup((*comm_ptr)->info_ptr, &info_ptr);
    if (mpi_errno != MPI_SUCCESS) goto fn_fail;
    *info_used = info_ptr->handle;

    /* ... end of body of routine ... */

#ifdef HAVE_ERROR_CHECKING
  fn_exit:
#endif
    MPID_MPI_FUNC_EXIT(MPID_STATE_MPI_COMM_GET_NAME);
    return mpi_errno;

    /* --BEGIN ERROR HANDLING-- */
#   ifdef HAVE_ERROR_CHECKING
  fn_fail:
    {
	mpi_errno = MPIR_Err_create_code(
	    mpi_errno, MPIR_ERR_RECOVERABLE, FCNAME, __LINE__, MPI_ERR_OTHER, 
	    "**mpi_comm_get_info",
	    "**mpi_comm_get_info %C %p", comm, info_used);
    }
    mpi_errno = MPIR_Err_return_comm( comm_ptr, FCNAME, mpi_errno );
    goto fn_exit;
#   endif
    /* --END ERROR HANDLING-- */
}


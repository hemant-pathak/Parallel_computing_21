//iittp_barrier() barrier

#include "mpi.h"

#ifndef iittp_barrier_FROM_PMPI
#define iittp_barrier PMPI_Barrier


/* This is the default implementation of the barrier operation.  The
   algorithm is:
   
   Algorithm: MPI_Barrier

   We use the dissemination algorithm described in:
   Debra Hensgen, Raphael Finkel, and Udi Manbet, "Two Algorithms for
   Barrier Synchronization," International Journal of Parallel
   Programming, 17(1):1-17, 1988.  

   It uses ceiling(lgp) steps. In step k, 0 <= k <= (ceiling(lgp)-1),
   process i sends to process (i + 2^k) % p and receives from process 
   (i - 2^k + p) % p.

   Possible improvements: 

   End Algorithm: MPI_Barrier

   This is an intracommunicator barrier only!
*/

/* not declared static because it is called in ch3_comm_connect/accept */

int iittp_barrier( MPID_Comm *comm_ptr )
{
    static const char FCNAME[] = "iittp_barrier";
    int size, rank, src, dst, mask, mpi_errno=MPI_SUCCESS;
    MPI_Comm comm;

    size = comm_ptr->local_size;
    /* Trivial barriers return immediately */
    if (size == 1) return MPI_SUCCESS;

    rank = comm_ptr->rank;
    comm = comm_ptr->handle;

    /* Only one collective operation per communicator can be active at any
       time */
    MPIDU_ERR_CHECK_MULTIPLE_THREADS_ENTER( comm_ptr );

    mask = 0x1;
    while (mask < size) {
        dst = (rank + mask) % size;
        src = (rank - mask + size) % size;
        mpi_errno = MPIC_Sendrecv(NULL, 0, MPI_BYTE, dst,
                                  MPIR_BARRIER_TAG, NULL, 0, MPI_BYTE,
                                  src, MPIR_BARRIER_TAG, comm,
                                  MPI_STATUS_IGNORE);
   /* --BEGIN ERROR HANDLING-- */
        if (mpi_errno)
   {
       mpi_errno = MPIR_Err_create_code(mpi_errno, MPIR_ERR_RECOVERABLE, FCNAME, __LINE__, MPI_ERR_OTHER, "**fail", 0);
       return mpi_errno;
   }
   /* --END ERROR HANDLING-- */
        mask <<= 1;
    }

    MPIDU_ERR_CHECK_MULTIPLE_THREADS_EXIT( comm_ptr );

    return mpi_errno;
}

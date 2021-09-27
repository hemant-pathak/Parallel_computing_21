#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"

int main(int argc, char **argv) {
    char filename[20];
    int rank, size;
    FILE *fp;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    /* proc 0 and 1 only */ 
    if (rank < 2) { 
        sprintf(filename, "file_%d.out", rank);
        fp = fopen(filename, "w");
        fprintf(fp, "P%d: before Barrier\n", rank);
        fclose(fp);
    }

    MPI_Barrier(MPI_COMM_WORLD);
    
    /* proc 0 and 1 only */ 
    if (rank < 2) { 
        sprintf(filename, "file_%d.out", (rank==0)?1:0 );
        fp = fopen(filename, "a");
        fprintf(fp, "P%d: after Barrier\n", rank);
        fclose(fp);
    }

    MPI_Finalize();
    return 0;

}

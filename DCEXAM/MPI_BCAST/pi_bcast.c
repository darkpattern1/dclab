#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <mpi.h>

int main (int argc, char* argv[]) {
    int pid, numberOfNodes, error, i, count = 0, sum = 0, iterations = 100000000;
    double pi = 0.0, begin = 0.0, end = 0.0, x, y, z;

    error = MPI_Init(&argc, &argv);
   
 
    MPI_Comm_rank(MPI_COMM_WORLD, &pid);
    MPI_Comm_size(MPI_COMM_WORLD, &numberOfNodes);
    MPI_Barrier(MPI_COMM_WORLD);
   
    srand((int)time(0));
   
    /* Each process calculates a part of the sum/result */
    for (i = pid; i < iterations; i += numberOfNodes) {
        x = rand() / (RAND_MAX + 1.0);
        y = rand() / (RAND_MAX + 1.0);
        z = ((x*x)+(y*y));
       
        if(z <= 1.0)
        {
            count++;
        }
    }
   
    /*
    1. Sum all the results
    2. Synchronize all processes
    3. Get end time
    */
    MPI_Reduce(&count, &sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    MPI_Barrier(MPI_COMM_WORLD);
   
    if (pid == 0)
    {
        pi = 4 * 1E-8 * sum;
        printf("PI = %0.10f\n", pi);
    }
   
    error=MPI_Finalize();
   
    return 0;
}

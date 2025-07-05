#include <mpi.h>
#include <iostream>
#include <cstdlib>

int main(int argc, char* argv[]) {
    MPI_Init(&argc, &argv);

    int world_rank, world_size;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    if (world_rank == 0) {
        std::cout << "Total processors/cores requested: " << world_size << std::endl;
    }

    std::cout << "Hello from processor " << world_rank << " of " << world_size << std::endl;

    MPI_Finalize();
    return 0;
}


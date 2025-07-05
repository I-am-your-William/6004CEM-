#include <mpi.h>
#include <iostream>
#include <cstring>

int main(int argc, char* argv[]) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    const int MSG_LEN = 100;
    char msg[MSG_LEN];

    if (rank == 0) {
        std::cout << "Master: Hello slaves, give me your messages" << std::endl;

        for (int i = 1; i < size; i++) {
            MPI_Recv(msg, MSG_LEN, MPI_CHAR, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            std::cout << "Message received from process " << i << ": " << msg << std::endl;
        }
    } else {
        const char* name = nullptr;
        switch (rank) {
            case 1: name = "Hello, I am John"; break;
            case 2: name = "Hello, I am Mary"; break;
            case 3: name = "Hello, I am Susan"; break;
            default: name = "Hello, I am a slave"; break;
        }
        std::strncpy(msg, name, MSG_LEN);

        MPI_Send(msg, std::strlen(msg) + 1, MPI_CHAR, 0, 0, MPI_COMM_WORLD);
    }

    MPI_Finalize();
    return 0;
}


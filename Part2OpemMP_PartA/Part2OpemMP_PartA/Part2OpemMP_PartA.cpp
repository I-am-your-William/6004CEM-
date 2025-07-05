#include <iostream>
#include <omp.h>
#include <windows.h>

int main() {
    char hostname[256];
    DWORD size = sizeof(hostname);
    GetComputerNameA(hostname, &size);  

    int num_threads;
    std::cout << "------------------------------------------\n";
    std::cout << "        OpenMP Hello World Program        \n";
    std::cout << "------------------------------------------\n";
    std::cout << "Machine Name: " << hostname << std::endl;

    std::cout << "Enter number of threads: ";
    std::cin >> num_threads;

    omp_set_num_threads(num_threads);

    std::cout << "\n----- Output from each thread -----\n";
#pragma omp parallel
    {
        int id = omp_get_thread_num();
        int total = omp_get_num_threads();
#pragma omp critical
        std::cout << "Thread [" << id << "/" << total
            << "] says: Hello World from machine [" << hostname << "]\n";
    }
    std::cout << "------------------------------------------\n";

    return 0;
}

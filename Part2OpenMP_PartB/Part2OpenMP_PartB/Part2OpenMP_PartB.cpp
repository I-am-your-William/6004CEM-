#include <iostream>
#include <vector>
#include <chrono>
#include <omp.h>
#include <windows.h>

#define SIZE 10000000

void vector_add_static() {     // Static
    std::vector<int> A(SIZE, 1);
    std::vector<int> B(SIZE, 2);
    std::vector<int> C(SIZE);

    auto start = std::chrono::high_resolution_clock::now();

#pragma omp parallel for schedule(static)
    for (int i = 0; i < SIZE; ++i) {
        C[i] = A[i] + B[i];
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;

    std::cout << "Schedule Type: Static  | Time Taken: " << elapsed.count() << " seconds\n";
}

void vector_add_dynamic() {  //dynamic
    std::vector<int> A(SIZE, 1);
    std::vector<int> B(SIZE, 2);
    std::vector<int> C(SIZE);

    auto start = std::chrono::high_resolution_clock::now();

#pragma omp parallel for schedule(dynamic)
    for (int i = 0; i < SIZE; ++i) {
        C[i] = A[i] + B[i];
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;

    std::cout << "Schedule Type: Dynamic | Time Taken: " << elapsed.count() << " seconds\n";
}

int main() {
    char hostname[256];
    DWORD size = sizeof(hostname);
    GetComputerNameA(hostname, &size);

    std::cout << "===================================================\n";
    std::cout << "      OpenMP Vector Addition: Static vs Dynamic    \n";
    std::cout << "===================================================\n";
    std::cout << "Machine Name: " << hostname << "\n";
    std::cout << "Array Size: " << SIZE << "\n";
    std::cout << "Thread Count: 4\n\n";

    omp_set_num_threads(4);

    std::cout << ">> Running with Static Schedule:\n";
    vector_add_static();

    std::cout << "\n>> Running with Dynamic Schedule:\n";
    vector_add_dynamic();

    std::cout << "===================================================\n";

    return 0;
}

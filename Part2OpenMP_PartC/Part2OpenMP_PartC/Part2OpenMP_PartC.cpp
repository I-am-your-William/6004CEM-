#include <iostream>
#include <vector>
#include <omp.h>
#include <windows.h>
#include <chrono>
#include <numeric>

void multiply_matrix_outer(int size, int threads, double& average_time) {
    std::vector<std::vector<double>> A(size, std::vector<double>(size, 1.0));
    std::vector<std::vector<double>> B(size, std::vector<double>(size, 1.0));
    std::vector<std::vector<double>> C(size, std::vector<double>(size, 0.0));

    std::vector<double> timings;

    for (int run = 0; run < 10; ++run) {
        auto start = std::chrono::high_resolution_clock::now();

#pragma omp parallel for num_threads(threads)
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                C[i][j] = 0;
                for (int k = 0; k < size; ++k) {
                    C[i][j] += A[i][k] * B[k][j];
                }
            }
        }

        auto end = std::chrono::high_resolution_clock::now();
        double time_taken = std::chrono::duration<double>(end - start).count();
        timings.push_back(time_taken);
    }

    average_time = std::accumulate(timings.begin(), timings.end(), 0.0) / timings.size();
}

void multiply_matrix_inner(int size, int threads, double& average_time) {
    std::vector<std::vector<double>> A(size, std::vector<double>(size, 1.0));
    std::vector<std::vector<double>> B(size, std::vector<double>(size, 1.0));
    std::vector<std::vector<double>> C(size, std::vector<double>(size, 0.0));

    std::vector<double> timings;

    for (int run = 0; run < 10; ++run) {
        auto start = std::chrono::high_resolution_clock::now();

        for (int i = 0; i < size; ++i) {
#pragma omp parallel for num_threads(threads)
            for (int j = 0; j < size; ++j) {
                C[i][j] = 0;
                for (int k = 0; k < size; ++k) {
                    C[i][j] += A[i][k] * B[k][j];
                }
            }
        }

        auto end = std::chrono::high_resolution_clock::now();
        double time_taken = std::chrono::duration<double>(end - start).count();
        timings.push_back(time_taken);
    }

    average_time = std::accumulate(timings.begin(), timings.end(), 0.0) / timings.size();
}

void run_tests(const std::string& loop_type, void(*multiply_func)(int, int, double&)) {
    int sizes[] = { 50, 500 };
    int thread_counts[] = { 1, 4, 8, 16 };

    std::cout << "\n==================================================\n";
    std::cout << " OpenMP Matrix Multiplication: " << loop_type << " Loop Parallelized\n";
    std::cout << "==================================================\n";
    std::cout << "Matrix Size | Threads | Average Time (seconds)\n";
    std::cout << "----------------------------------------------\n";

    for (int size : sizes) {
        for (int threads : thread_counts) {
            double avg_time = 0.0;
            multiply_func(size, threads, avg_time);
            std::cout << " " << size << "x" << size
                << "\t | " << threads
                << "\t | " << avg_time << "\n";
        }
    }
}

int main() {
    char hostname[256];
    DWORD size = sizeof(hostname);
    GetComputerNameA(hostname, &size);

    std::cout << "==================================================\n";
    std::cout << "     PART C - OpenMP Matrix Multiplication\n";
    std::cout << "     Machine: " << hostname << "\n";
    std::cout << "==================================================\n";

    run_tests("Outer", multiply_matrix_outer);
    run_tests("Inner", multiply_matrix_inner);

    std::cout << "==================================================\n";

    return 0;
}

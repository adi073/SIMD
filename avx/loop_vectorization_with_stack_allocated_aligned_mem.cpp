#include <iostream>
#include <immintrin.h>
#include <chrono>

// Use alignas to specify the alignment of the arrays
alignas(32) float a[512];
alignas(32) float b[512];
alignas(32) float c[512];

alignas(32) __m256 avx_a[512/8];
alignas(32) __m256 avx_b[512/8];
alignas(32) __m256 avx_c[512/8];

int main(int argc, char **argv)
{
    const int size = 512;

    // Initialize arrays
    for (int i=0; i<size; ++i)
    {
        a[i] = 1.0*(i+1);
        b[i] = 2.5*(i+1);
        c[i] = 0.0;
    }

    // Standard loop
    auto start = std::chrono::high_resolution_clock::now();
    for (int j=0; j<100000; ++j)
    {
        for (int i=0; i<size; ++i)
        {
            c[i] = a[i] + b[i];
        }
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::micro> duration = end - start;
    std::cout << "The standard loop took " << duration.count() << " microseconds to complete." << std::endl;

    // AVX loop
    start = std::chrono::high_resolution_clock::now();
    for (int j=0; j<100000; ++j)
    {
        for (int i=0; i<size/8; ++i)
        {
            avx_c[i] = _mm256_add_ps(avx_a[i], avx_b[i]);
        }
    }
    end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::micro> avx_duration = end - start;
    std::cout << "The AVX loop took " << avx_duration.count() << " microseconds to complete." << std::endl;

    return 0;
}


#include <iostream>
#include <immintrin.h>
#include <chrono>
#include <cstdlib>

// Define a helper function to allocate aligned memory
template <typename T>
T* aligned_alloc(std::size_t num) {
    void* ptr = nullptr;
    if (posix_memalign(&ptr, 32, num * sizeof(T))) {
        throw std::bad_alloc();
    }
    return reinterpret_cast<T*>(ptr);
}

int main(int argc, char **argv)
{
    const int size = 512;

    float* a = aligned_alloc<float>(size);
    float* b = aligned_alloc<float>(size);
    float* c = aligned_alloc<float>(size);

    __m256* avx_a = aligned_alloc<__m256>(size/8);
    __m256* avx_b = aligned_alloc<__m256>(size/8);
    __m256* avx_c = aligned_alloc<__m256>(size/8);

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

    free(a);
    free(b);
    free(c);
    free(avx_a);
    free(avx_b);
    free(avx_c);

    return 0;
}


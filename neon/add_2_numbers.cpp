#include <iostream>
#include <arm_neon.h>

int32x4_t add_numbers(int32x4_t a, int32x4_t b) {
    return vaddq_s32(a, b);
}

int main() {
    int32_t a[4] = {1, 2, 3, 4};
    int32_t b[4] = {5, 6, 7, 8};
    int32_t result[4];

    int32x4_t va = vld1q_s32(a);
    int32x4_t vb = vld1q_s32(b);

    int32x4_t vresult = add_numbers(va, vb);

    vst1q_s32(result, vresult);
	
    std::cout << result[0] << result[3] << std::endl;
    return 0;
}

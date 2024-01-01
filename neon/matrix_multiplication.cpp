#include <iostream>
#include <arm_neon.h>

void neonmult(const float *matrixA, const float *matrixB, float *matrixR)
{
    float32x4_t a0, a1, a2, a3, b0, b1, b2, b3, r0, r1, r2, r3;
    a0 = vld1q_f32(matrixA); /* col 0 of matrixA */
    a1 = vld1q_f32(matrixA + 4); /* col 1 of matrixA */
    a2 = vld1q_f32(matrixA + 8); /* col 2 of matrixA */
    a3 = vld1q_f32(matrixA + 12); /* col 3 of matrixA */

    b0 = vld1q_f32(matrixB); /* col 0 of matrixB */
    b1 = vld1q_f32(matrixB + 4); /* col 1 of matrixB */
    b2 = vld1q_f32(matrixB + 8); /* col 2 of matrixB */
    b3 = vld1q_f32(matrixB + 12); /* col 3 of matrixB */

    /* compute all the cols in the order specified by compiler */
    r0 = vmulq_lane_f32(a0, vget_low_f32(b0), 0);
    r0 = vmlaq_lane_f32(r0, a1, vget_low_f32(b0), 1);
    r0 = vmlaq_lane_f32(r0, a2, vget_high_f32(b0), 0);
    r0 = vmlaq_lane_f32(r0, a3, vget_high_f32(b0), 1);

    r1 = vmulq_lane_f32(a0, vget_low_f32(b1), 0);
    r1 = vmlaq_lane_f32(r1, a1, vget_low_f32(b1), 1);
    r1 = vmlaq_lane_f32(r1, a2, vget_high_f32(b1), 0);
    r1 = vmlaq_lane_f32(r1, a3, vget_high_f32(b1), 1);

    r2 = vmulq_lane_f32(a0, vget_low_f32(b2), 0);
    r2 = vmlaq_lane_f32(r2, a1, vget_low_f32(b2), 1);
    r2 = vmlaq_lane_f32(r2, a2, vget_high_f32(b2), 0);
    r2 = vmlaq_lane_f32(r2, a3, vget_high_f32(b2), 1);

    r3 = vmulq_lane_f32(a0, vget_low_f32(b3), 0);
    r3 = vmlaq_lane_f32(r3, a1, vget_low_f32(b3), 1);
    r3 = vmlaq_lane_f32(r3, a2, vget_high_f32(b3), 0);
    r3 = vmlaq_lane_f32(r3, a3, vget_high_f32(b3), 1);

    vst1q_f32(matrixR, r0);
    vst1q_f32(matrixR + 4, r1);
    vst1q_f32(matrixR + 8, r2);
    vst1q_f32(matrixR + 12, r3);
}

int main()
{
    float matrixA[16] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
    float matrixB[16] = {16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    float matrixR[16];

    neonmult(matrixA, matrixB, matrixR);

    printf("Result:\n");
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            std::cout << matrixR[i*4 + j] << " " << std::endl;
        }
        std::cout << std::endl;
    }

    return 0;
}

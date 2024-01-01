#include <iostream>
#include <arm_neon.h>

int main (void)
{
	uint8x8x3_t v; // This represents 3 vectors.
	// Each vector has eight lanes of 8-bit data.
	
	unsigned char A[24]; // This array represents a 24-bit RGB image.
	v = vld3_u8(A); // This de-interleaves the 24-bit image from array A
	
	// and stores them in 3 separate vectors
	// v.val[0] is the first vector in V. It is for the red channel
	// v.val[1] is the second vector in V. It is for the green channel
	// v.val[2] is the third vector in V. It is for the blue channel.
	//Double the red channel
	
	v.val[0] = vadd_u8(v.val[0],v.val[0]);
	vst3_u8(A, v); // store the vector back into the array, with the red channel doubled.
	return 0;
}

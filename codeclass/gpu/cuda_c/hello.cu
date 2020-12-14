#include <stdio.h>


__global__ void HelloGpu() {
	__shared__ int arr[10];
	for(int i = 0; i < 10; i++) {
		printf("%d ", arr[i]);
	}
	printf("\nHello GPU\n");
}

int main() {
	printf("Hello CPU\n");
	HelloGpu<<<1,10>>>();
	cudaDeviceReset();
	return 0;
}

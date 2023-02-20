#define _USE_MATH_DEFINES
#include <stdio.h>
#include <malloc.h>
#include <math.h>
#define N 10000000

inline void float_arr_fill(float *arr, int len)
{
	float angle_inc = 2 * M_PI / len;
	float sum = 0;
#pragma data copy(arr [0:len])
	{
#pragma acc kernels
		for (long long i = 0; i < len; i++)
		{
			arr[i] = sinf(angle_inc * i);
		}

#pragma acc kernels
		for (long long i = 0; i < len; i++)
		{
			sum += arr[i];
		}
	}
	printf("sum = %lf", sum);
}

int main()
{
	long long len = N;
	float *f_arr = (float *)malloc(sizeof(float) * len);

	float_arr_fill(f_arr, len);
	free(f_arr);

	return 0;
}

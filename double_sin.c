#define _USE_MATH_DEFINES
#include <stdio.h>
#include <malloc.h>
#include <math.h>
#define N 10000000

inline void double_arr_fill(double *arr, int len)
{
	double angle_inc = 2 * M_PI / len; // 0 — 2*Pi
	double sum = 0;
#pragma data copy(arr [0:len])
	{
		{
#pragma acc kernels
			for (long long i = 0; i < len; i++)
			{
				arr[i] = sin(angle_inc * i);
			}

#pragma acc kernels
			for (long long i = 0; i < len; i++)
			{
				sum += arr[i];
			}
		}
	}
}

int main()
{
	long long len = N;
	double *d_arr = (double *)malloc(sizeof(double) * len);

	double_arr_fill(d_arr, len);

	free(d_arr);

	return 0;
}

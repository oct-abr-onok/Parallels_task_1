#define _USE_MATH_DEFINES
#include <stdio.h>
#include <malloc.h>
#include <math.h>
#include <time.h>
#define N 10000000

inline void double_arr_fill(double *arr, int len)
{
	double angle_inc = 2 * M_PI / len; // 0 — 2*Pi
	double sum = 0;
	clock_t start, end;
	
#pragma data create(arr [0:len]) copy(sum) copyin(angle_inc)
	{
		start = clock();
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
	end = clock();
	}
	
	printf("loops time = %lf\n", (double)(end - start) / CLOCKS_PER_SEC);
	printf("sum = %lf\n", sum);
}

int main()
{
	clock_t start, end;
	start = clock();
	long long len = N;
	double *d_arr = (double *)malloc(sizeof(double) * len);

	double_arr_fill(d_arr, len);

	free(d_arr);

	end = clock();
	printf("programm time = %lf\n\n", (double)(end - start) / CLOCKS_PER_SEC);

	return 0;
}

#define _USE_MATH_DEFINES
#include <stdio.h>
#include <malloc.h>
#include <math.h>
#include <time.h>
#define N 10000000

inline void float_arr_fill(float *arr, int len)
{
	float angle_inc = 2 * M_PI / len;
	float sum = 0;
	clock_t start, end;

	
#pragma data create(arr [0:len]) copy(sum) copyin(angle_inc)
	{
		start = clock();
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
		end = time();
	}
	
	printf("loops time = %lf\n", (double)(end - start) / CLOCKS_PER_SEC);
	printf("sum = %lf\n", sum);
}

int main()
{
	clock_t start, end;
	start = clock();
	long long len = N;
	float *f_arr = (float *)malloc(sizeof(float) * len);

	float_arr_fill(f_arr, len);
	free(f_arr);

	end = clock();
	printf("programm time = %lf\n", (double)(end - start) / CLOCKS_PER_SEC);

	return 0;
}

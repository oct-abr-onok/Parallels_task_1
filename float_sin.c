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
	time_t start, end;

	time(&start);
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
	time(&end);
	printf("loops time = %lf\n", difftime(end, start));
	printf("sum = %lf\n", sum);
}

int main()
{
	time_t start, end;
	time(&start);
	long long len = N;
	float *f_arr = (float *)malloc(sizeof(float) * len);

	float_arr_fill(f_arr, len);
	free(f_arr);

	time(&end);
	printf("programm time = %lf", difftime(end, start));

	return 0;
}

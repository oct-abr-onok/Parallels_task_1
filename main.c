#include <stdio.h>
#include <malloc.h>
#include <math.h>
#define N 10000000
#define M_PI 3.14159265358979323846	

inline void double_arr_fill(double* arr, int len)
{
	double cur_angle = 0;
	double angle_inc = 2 * M_PI / len; //0 — 2*Pi
	double sum = 0;

#pragma acc kernels
	for (long long i = 0; i < len; i++)
	{
		arr[i] = sin(cur_angle);
		cur_angle += angle_inc;
	}
	
#pragma acc kernels
	for (long long i = 0; i < len; i++)
	{
		sum += arr[i];
	}
}
inline void float_arr_fill(float* arr, int len)
{
	float cur_angle = 0;
	float angle_inc = 2 * M_PI / len;
	float sum = 0;

#pragma acc kernels
	for (long long i = 0; i < len; i++)
	{
		arr[i] = sinf(cur_angle);
		cur_angle += angle_inc;
	}
	
#pragma acc kernels
	for (long long i = 0; i < len; i++)
	{
		sum += arr[i];
	}
}

int main()
{
	long long len = N;
	double* d_arr = (double*)malloc(sizeof(double) * len);
	float* f_arr = (float*)malloc(sizeof(float) * len);
	
	double_arr_fill(d_arr, len);
	float_arr_fill(f_arr, len);

	free(d_arr);
	free(f_arr);

	return 0;
}

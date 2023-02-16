#include <stdio.h>
#include <malloc.h>
#include <math.h>
#define N 10000000
#define M_PI 3.14159265358979323846	

void FuncArray(double* my_array, int len)
{
	double cur_angle = 0;
	#pragma acc data create(my_array[:len])
	{
		double add_angle = 2 * M_PI / N;
		#pragma acc kernels
		for (long long i = 0; i < len; i++)
		{
			my_array[i] = sin(cur_angle);
			cur_angle += add_angle;
		}

		double sum = 0; 
		#pragma acc kernels
		for (long long i = 0; i < len; i++)
		{
			sum += my_array[i];
		}
	}
	
}

int main()
{
	long long len = N;
	double* array = (double*)malloc(sizeof(double) * len);
	FuncArray(array, len);

	return 0;
}

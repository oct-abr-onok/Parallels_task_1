#include <stdio.h>
#include <malloc.h>
#include <math.h>
#define N 10000000

void FuncArray(double** my_array, int len)
{
	double* temp = (double*)malloc(sizeof(double) * len);
	int cur_angle = 0;
	for (long long i = 0; i < len; i++)
	{
		temp[i] = sin(cur_angle);
	}
	*my_array = temp;
}

int main()
{
	double** array = (double**)malloc(sizeof(double**));
	long long len = N;
	FuncArray(array, len);

	return 0;
}
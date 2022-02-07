//Задача 05-12: Решение системы линейных уравнений
//Грустная панда сидит и смотрит на систему линейных алгебраических уравнений Ax = b с целочисленными коэффициентами. 
//С первого взгляда бросается в глаза, что все эти коэффициенты невелики. Для того, чтобы развеселить панду, 
//требуется реализовать программу, которая смогла бы найти точное решение этой системы.
//На вход программе подается натуральное число N (N ≤ 500) и последовательность целых чисел a11, a12, ..., a1N, b1, a21, ...., aNN, bN. 
//Требуется вывести последовательность целых чисел x1, ..., xN, являющихся решением данной системы уравнений.
//Панда уверена в том, что такое решение существует и единственно.

#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "malloc.h"

void swap_ld(long double* a, long double* b)
{
	long double t = *a;
	*a = *b;
	*b = t;
}
void swap_mas_ld(long double* a, long double* b, int n)
{
	for (int i = 0; i < n; i++)
		swap_ld(&a[i], &b[i]);
}

void line_multiply(long double* a, int n, long double m)
{
	for (int i = 0; i < n; i++)
		a[i] *= m;
}
void line_add(long double* a, long double* b, int n)
{
	for (int i = 0; i < n; i++)
		a[i] += b[i];
}

int long_double_cmp(long double a, long double b)
{
	if ((a + 0.000001) > b && (a - 0.000001) < b)
		return 0;
	return (a > b ? 1 : -1);
}

int main(void)
{
	int n;
	scanf("%d", &n);

	long double** A_b = (long double**)malloc(n * sizeof(long double*));
	for (int i = 0; i < n; i++)
		A_b[i] = (long double*)malloc((n + 1) * sizeof(long double));

	int tmp;

	for (int i = 0; i < n; i++)
		for (int j = 0; j <= n; j++)
		{
			scanf("%d", &tmp);
			A_b[i][j] = (long double)tmp;
		}

	for (int i = 0; i < n - 1; i++)
	{
		int t;
		for (t = i; long_double_cmp(A_b[t][i], 0) == 0; t++);

		if (t != i)
			swap_mas_ld(A_b[i], A_b[t], n + 1);

		for (int j = i + 1; j < n; j++)
		{
			if (long_double_cmp(A_b[j][i], 0) != 0)
			{
				long double m = A_b[i][i] / A_b[j][i];
				line_multiply(A_b[j], n + 1, -m);
			}
		}

		for (int j = i + 1; j < n; j++)
			if (long_double_cmp(A_b[j][i], 0) != 0)
				line_add(A_b[j], A_b[i], n + 1);
	}

	long double* ans = (long double*)malloc(n * sizeof(long double));

	for (int i = n - 1; i >= 0; i--)
	{
		long double add = 0;

		for (int j = i + 1; j < n; j++)
			add += A_b[i][j] * ans[j];

		ans[i] = (A_b[i][n] - add) / A_b[i][i];
	}

	printf("\n");
	for (int i = 0; i < n; i++)
		printf("%d ", (int)(ans[i] * 1.000001));
	printf("\n");
	
	for(int i = 0; i < n; i++)
		free(A_b[i]);
	free(A_b);
	free(ans);

	return 0;
}

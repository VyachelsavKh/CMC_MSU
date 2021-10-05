#include "stdio.h"

#ifdef __cplusplus
#pragma warning(disable:4996)
#endif

#define max(a, b) (a > b ? a : b)
#define min(a, b) (a < b ? a : b)

//Задача 01-1: Разность максимума и минимума
//На стандартном потоке ввода задаётся натуральное число N (N > 0), после которого следует последовательность из N целых чисел.
//На стандартный поток вывода напечатайте разность между наибольшим и наименьшим элементами последовательности.

int main(void)
{
	int n;

	scanf("%d", &n);

	int max, min, x;

	scanf("%d", &x);

	max = min = x;

	for (int i = 0; i < n - 1; i++)
	{
		scanf("%d", &x);
		max = max(max, x);
		min = min(min, x);
	}

	printf("%d", max - min);

	return 0;
}

#include "stdio.h"

#ifdef __cplusplus
#pragma warning(disable:4996)
#endif

//Задача 01-2: Число вхождений максимума
//На стандартном потоке ввода задаётся натуральное число N (N > 0), после которого следует последовательность из N целых чисел.
//На стандартный поток вывода напечатайте, сколько раз в этой последовательности встречается максимум.
//Указание: использовать массивы запрещается.

int main(void)
{
	int n;

	scanf("%d", &n);

	int max, count, x;

	scanf("%d", &x);

	max = x;
	count = 1;

	for (int i = 0; i < n - 1; i++)
	{
		scanf("%d", &x);

		if (x > max)
		{
			max = x;
			count = 1;
		}
		else if (x == max)
			count++;
	}

	printf("%d", count);

	return 0;
}

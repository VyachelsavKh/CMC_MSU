//Задача 01-14: Максимальное произведение
//На стандартном потоке ввода задаётся натуральное число N (N > 1), 
//после которого следует последовательность из N целых 32-битных чисел Ai (1 ≤ i ≤ N).
//Требуется найти такие числа Ai, Aj (i ≠ j, 1 ≤ i,j ≤ N), что произведение Ai*Aj максимально. 
//На стандартный поток вывода напечатайте эти числа: сначала меньшее, потом большее. 
//Если различные пары чисел дают одно и то же максимальное произведение, напечатайте ту пару, сумма чисел в которой меньше.
//Указание: использовать массивы запрещается.

#include "stdio.h"

void swap(long long* a, long long* b)
{
	long long t;
	t = *b;
	*b = *a;
	*a = t;
}

int main(void)
{
	int n;

	scanf("%d", &n);

	long long max1, max2, min1, min2, a;

	scanf("%lld%lld", &max1, &max2);

	if (max2 < max1)
		swap(&max1, &max2);

	min1 = max1;
	min2 = max2;

	for (int i = 3; i <= n; i++)
	{
		scanf("%lld", &a);

		if (a >= max2)
		{
			max1 = max2;
			max2 = a;
		}
		else if (a >= max1)
			max1 = a;

		if (a <= min1)
		{
			min2 = min1;
			min1 = a;
		}
		else if (a <= min2)
			min2 = a;
	}

	long long m1 = min1 * min2, m2 = max1 * max2;

	if (m1 == m2)
		printf("%lld %lld", min1, min2);
	else if (m1 > m2)
		printf("%lld %lld", min1, min2);
	else
		printf("%lld %lld", max1, max2);

	return 0;
}

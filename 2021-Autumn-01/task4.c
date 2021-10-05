#include "stdio.h"

//Задача 01-4: Длина максимальной возрастающей подпоследовательности
//На стандартном потоке ввода задаётся натуральное число N (N > 0), после которого следует последовательность из N целых чисел.
//На стандартный поток вывода напечатайте длину максимальной (по длине) возрастающей непрерывной подпоследовательности входной последовательности.
//Указание: использовать массивы запрещается.

#define max(a, b) (a > b ? a : b)
#define min(a, b) (a < b ? a : b)

int main(void)
{
	int n;

	scanf("%d", &n);

	int cur_x, prev_x, max, now;

	scanf("%d", &cur_x);

	now = max = 1;
	prev_x = cur_x;

	for (int i = 0; i < n - 1; i++)
	{
		scanf("%d", &cur_x);

		if (cur_x > prev_x)
			now++;
		else
		{
			max = max(max, now);
			now = 1;
		}

		prev_x = cur_x;
	}

	max = max(max, now);

	printf("%d", max);

	return 0;
}

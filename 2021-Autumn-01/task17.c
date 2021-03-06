//Задача 01-17: Не пара
//Преподаватели первого курса создали набор, содержащий N (1 ≤ N ≤ 1 000 000) натуральных чисел, не превосходящих 1 000 000. 
//Известно, что ровно одно число в этом наборе встречается один раз, а остальные — ровно по два раза. Помогите преподавателям найти это число.
//Входные данные: в первой входной строке вводится число N, затем по одному числу в строке вводятся N натуральных чисел, не превосходящих 1 000 000.
//Выходные данные: ваша программа должна определить число, встречающееся один раз, и вывести его на экран.
//Указание: использовать массивы запрещается.

#include "stdio.h"

int main(void)
{
	int n;
	scanf("%d", &n);

	int x, out = 0;

	for (int i = 0; i < n; i++)
	{
		scanf("%d", &x);

		out ^= x;
	}

	printf("%d", out);

	return 0;
}

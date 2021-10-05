//Задача 01-22: Кузнечик
//Кузнечик прыгает по плоскости так, что его координаты на плоскости – всегда целые числа, длина прыжка равна 1,
//а каждый следующий прыжок (начиная со второго) повернут к предыдущему на 90 градусов по выбору кузнечика. 
//Найти за какое наименьшее число прыжков из точки (0,0) кузнечик может попасть в точку (X,Y).
//Формат входных данных: два целых числа X и Y, не превосходящих по модулю 10000.
//Формат выходных данных: единственное целое число – наименьшее количество прыжков.

#include "stdio.h"
#include "stdlib.h"
#include "math.h"

void swap(int* a, int* b)
{
	int t;
	t = *b;
	*b = *a;
	*a = t;
}

int main(void)
{
	int x, y;

	scanf("%d%d", &x, &y);

	x = abs(x);
	y = abs(y);

	if (y > x)
		swap(&x, &y);

	int d = x - y;

	int count = d / 2 * 4 + (d & 1);

	count += y * 2;

	printf("%d\n", count);

	return 0;
}

//Задача 02-5: Шары
//Дано N шаров. Требуется определить, есть ли среди них два шара, которые имеют общую точку.
//На стандартном потоке ввода задаётся натуральное число N (0 < N ≤ 100), после которого следуют N строк, описывающие шары. 
//В каждой строке записаны координаты центра i-го шара xi yi zi и его радиус ri. xi, yi, zi и ri вещественные не превосходящие по модулю 1000. ri строго положительно.
//На стандартный поток вывода напечатайте YES, если среди шаров есть два, которые имеют общую точку. В противном случае напечатайте NO.

#include "stdio.h"
#include "malloc.h"

#include <math.h>

struct point
{
	double x, y, z, r;
};

void readPoint(struct point* p)
{
	scanf("%lf", &p->x);
	scanf("%lf", &p->y);
	scanf("%lf", &p->z);
	scanf("%lf", &p->r);
}

double dist(struct point* p1, struct point* p2)
{
	double dx, dy, dz;
	dx = p1->x - p2->x;
	dy = p1->y - p2->y;
	dz = p1->z - p2->z;

	return sqrt(dx * dx + dy * dy + dz * dz);
}

int main(void)
{
	int n;
	scanf("%d", &n);

	struct point* points = (struct point*)malloc(n * sizeof(struct point));

	for (int i = 0; i < n; i++)
	{
		readPoint(points + i);
	}

	for (int i = 0; i < n; i++)
		for (int j = i + 1; j < n; j++)
		{
			if (dist(points + i, points + j) <= points[i].r + points[j].r)
			{
				printf("YES");
				return 0;
			}
		}

	printf("NO");

	free(points);

	return 0;
}

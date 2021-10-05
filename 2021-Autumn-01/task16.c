//Задача 01-16: Медианы треугольника
//На вход программе подаются координаты вершин треугольника. 
//Требуется найти координаты точки пересечения медиан данного треугольника. 
//Ответ выводите с точностью до 4 знаков после запятой.

#include "stdio.h"

#define sign(a) (a > 0 ? 1 : -1)

int equal(double a, double b)
{
	return (a + 0.000001 > b && a - 0.000001 < b);
}

int main(void)
{
	double a1, a2, b1, b2, c1, c2;

	scanf("%lf%lf%lf%lf%lf%lf", &a1, &a2, &b1, &b2, &c1, &c2);

	double ab1, ab2, bc1, bc2;

	ab1 = (a1 + b1) / 2;
	ab2 = (a2 + b2) / 2;

	bc1 = (b1 + c1) / 2;
	bc2 = (b2 + c2) / 2;

	double k1, k2, k3, k4;

	double x, y;

	int f1, f2;

	f1 = equal(bc1, a1);
	f2 = equal(ab1, c1);

	if (!f1 && !f2)
	{
		k1 = (bc2 - a2) / (bc1 - a1);
		k2 = -(a1 * bc2 - a2 * bc1) / (bc1 - a1);

		k3 = (ab2 - c2) / (ab1 - c1);
		k4 = -(c1 * ab2 - c2 * ab1) / (ab1 - c1);

		x = (k4 - k2) / (k1 - k3);
		y = (k1 * k4 - k2 * k3) / (k1 - k3);

	}
	else
	{
		if (!f1)
		{
			x = c1;

			k1 = (bc2 - a2) / (bc1 - a1);
			k2 = -(a1 * bc2 - a2 * bc1) / (bc1 - a1);

			y = k1 * x + k2;
		}
		else
		{
			x = a1;

			k3 = (ab2 - c2) / (ab1 - c1);
			k4 = -(c1 * ab2 - c2 * ab1) / (ab1 - c1);

			y = k3 * x + k4;
		}
	}

	printf("%.4lf %.4lf", x, y);

	return 0;
}

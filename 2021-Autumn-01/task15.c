//Задача 01-15: Многоугольник
//На плоскости последовательным перечислением своих вершин (в порядке обхода по часовой или против часовой стрелки) 
//задан невырожденный многоугольник без самопересечений и самоналожений. Никакие три идущие подряд вершины не лежат на одной прямой.
//Требуется определить, является ли данный многоугольник выпуклым.
//Формат ввода данных таков. На стандартном потоке ввода сначала задаётся число вершин многоугольника N (3 ≤ N), 
//после чего следуют пары координат Xi, Yi. Все координаты являются целыми числами, по модулю не превосходящими 32000. 
//Вершины упорядочены в порядке обхода многоугольника по часовой или против часовой стрелки.
//Указание: воспользуйтесь свойствами псевдоскалярного произведения.
//Указание: использовать массивы запрещается.

#include "stdio.h"

#define sign(a) (a > 0 ? 1 : -1)

double vec_mult(double x1, double y1, double x2, double y2, double x3, double y3)
{
	double ax, ay, bx, by;
	ax = x2 - x1;
	ay = y2 - y1;
	bx = x3 - x2;
	by = y3 - y2;

	return ax * by - ay * bx;
}

int main(void)
{
	int n;
	scanf("%d", &n);

	int x1, y1, x2, y2, x3, y3, x_cur, y_cur;

	scanf("%d%d%d%d%d%d", &x1, &y1, &x2, &y2, &x3, &y3);

	if (n == 3)
	{
		printf("Yes");
		return 0;
	}

	int p1x = x1, p1y = y1;
	int p2x = x2, p2y = y2;

	int sign_start = sign(vec_mult(x1, y1, x2, y2, x3, y3));

	for (int i = 0; i < n - 3; i++)
	{
		scanf("%d%d", &x_cur, &y_cur);

		x1 = x2;
		y1 = y2;
		x2 = x3;
		y2 = y3;
		x3 = x_cur;
		y3 = y_cur;

		int sign_now = sign(vec_mult(x1, y1, x2, y2, x3, y3));

		if (sign_start != sign_now)
		{
			printf("No");
			return 0;
		}
	}

	x1 = x3;
	y1 = y3;
	x2 = p1x;
	y2 = p1y;
	x3 = p2x;
	y3 = p2y;

	int sign_now = sign(vec_mult(x1, y1, x2, y2, x3, y3));

	if (sign_start != sign_now)
	{
		printf("No");
		return 0;
	}

	printf("Yes");
}

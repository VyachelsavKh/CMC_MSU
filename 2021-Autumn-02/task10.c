//Задача 02-10: Атлет Вася
//Благодаря внедрению Системы Повсеместного Контроля и Надзора, трененры легкоатлетической сборной Очень Известного Университета 
//могут теперь собирать подробную информацию про спортсменов во время тренировок. Так например, им стало известно, что весь путь, 
//который пробегает атлет Вася, можно разбить на N участков, на каждом из которых он движется равноускоренно.
//На стандартном потоке ввода задаётся натуральное число N (0 < N ≤ 100), после которого следуют N вещественных чисел 
//si — длины отрезков, на которых Вася движется равноускореено (0 < si ≤ 100). Далее идут N вещественных чисел ai — ускорения на этих участках (-10 ≤ ai ≤ 10).
//Начинает бежать Вася с нулевой скоростью. Во время тренировки его скорость никогда не становится отрицательной. Финишировать он может с любой скорость.
//Ваша задача состоит в том, чтобы определить, сколько времени понадобилось Васе на то, чтобы пробежать тренировочный маршрут. 
//Ответ на поставленную задачу выводите с точностью до 4 знаков после десятичной запятной.

#include "stdio.h"
#include "malloc.h"
#include "math.h"

#ifdef __cplusplus
#pragma warning(disable:4996)
#endif

int main(void)
{
	int n;
	scanf("%d", &n);

	double* len = (double*)malloc(n * sizeof(double));
	double* a = (double*)malloc(n * sizeof(double));

	for (int i = 0; i < n; i++)
		scanf("%lf", len + i);

	for (int i = 0; i < n; i++)
		scanf("%lf", a + i);

	double v = 0, t = 0;

	for (int i = 0; i < n; i++)
	{
		if (a[i] + 0.000001 > 0 && a[i] - 0.000001 < 0)
			t += len[i] / v;
		else
		{
			double d = sqrt(v * v + 2 * a[i] * len[i]);

			double dt = (-v + d) / a[i];

			t += dt;

			v += a[i] * dt;
		}
	}

	printf("%.4lf", t);

	free(len);
	free(a);

	return 0;
}

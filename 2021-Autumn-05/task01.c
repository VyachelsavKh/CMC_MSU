//Задача 05-1: Эрмитово-сопряжённая матрица
//Дана квадратная матрица, содержащая комплексные числа. Требуется вывести эрмитово-сопряжённую к данной матрицу.
//На стандартном потоке ввода задано натуральное число N (N ≤ 500) и квадратная матрица M размерности N по строкам - то есть, 
//в первой строке задана первая строка матрицы, во второй - вторая и так далее. 
//Элементы матрицы M заданы в алгебраической форме в виде пар двух чисел A и B, где A - действительная часть, B - мнимая часть. Числа A, B - целые, 32-битные.
//На стандартный поток вывода выведите матрицу, являющуюся эрмитово-сопряжённой к матрице M, по строкам.
//Указание: для хранения матрицы используйте динамическую память.

#include "stdio.h"
#include "stdlib.h"

struct pair
{
    long long first, second;
};

int main(void)
{
    int n;
    scanf("%d", &n);

    struct pair** mas = (struct pair**)malloc(n * sizeof(struct pair*));
    for (int i = 0; i < n; i++)
        mas[i] = (struct pair*)malloc(n * sizeof(struct pair));

    struct pair cur;

    for(int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
        {
            scanf("%lld%lld", &cur.first, &cur.second);
            cur.second *= -1;
            mas[i][j] = cur;
        }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("%lld %lld ", mas[j][i].first, mas[j][i].second);
        }
        printf("\n");
    }

    for (int i = 0; i < n; i++)
        free(mas[i]);
    free(mas);

    return 0;
}

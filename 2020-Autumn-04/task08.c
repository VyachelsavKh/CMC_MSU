//Задача 04-8: Вычеркивание
//Сколько различных трехзначных чисел можно получить из заданного натурального N, вычеркивая цифры из его десятичной записи?
//Формат входных данных: единственное натуральное число N, не превосходящее 10^100.
//Формат выходных данных: единственное целое число – найденное количество.

#include "stdio.h"
#include "string.h"

char str[105];
int check[1005];

int main(void)
{
    fgets(str, 105, stdin);

    int n, len;
    len = strlen(str) - 1;

    for (int l = 0; l < len - 2; l++)
        for (int m = l + 1; m < len - 1; m++)
            for (int r = m + 1; r < len; r++)
            {
                n = (str[l] - '0') * 100 + (str[m] - '0') * 10 + (str[r] - '0');
                check[n]++;
            }
    
    int count = 0;

    for (int i = 100; i < 1000; i++)
        if (check[i] != 0)
            count++;
    
    printf("%d", count);
}

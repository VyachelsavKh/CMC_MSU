//Задача 03-1: НОД четырех
//На вход программе подаются 4 натуральных числа не превосходящих 10^9. Требуется найти их наибольший общий делитель.

#include "stdio.h"

int NOD(int a, int b)
{
    if (b)
        return NOD(b, a % b);

    return a;
}

int main(void)
{
    int a, b, c, d;
    scanf("%d%d%d%d", &a, &b, &c, &d);

    printf("%d", NOD(NOD(a, b), NOD(c, d)));

    return 0;
}

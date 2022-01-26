//Задача 03-20: Антифункция
//Давным давно, в далекой галактике кто-то написал функцию f:
/*
unsigned f(unsigned x)
{
    long long s = 0;
    unsigned i;
    for (i = 0; s <= x; i++) {
        s += 2 * i + 1;
    }
    return x * (i - 1);
}
*/
//Вам требуется написать функцию g с прототипом unsigned g(unsigned) такую, что f(g(x)) = x для любого x из области значений функции f. 
//Функция g может использовать любые вспомогательные функции.
//Также напишите программу, демонстрирующую работу полученной функции. На вход программе подается число x из области значений функции f. Программа должна вывести g(x).
//Примечание: считайте что тип unsigned 32-битный, а long long - 64-битный даже в далекой галактике.

#include "stdio.h"

long long sqrt_3(long long x)
{
    long long a = 1;

    for (; a * a * a <= x; a <<= 1);

    if (a * a * a == x)
        return a;

    long long l = a >> 1;
    long long r = a;
    long long m, m_3, m_1_3;

    while (1)
    {
        m = (l + r) / 2;
        m_3 = m * m * m;
        m_1_3 = (m + 1) * (m + 1) * (m + 1);

        if (m_3 <= x && m_1_3 > x)
            return m;

        if (m_3 > x)
            r = m;
        else
            l = m;
    }
}

long long g_ex(long long x)
{
    long long a = sqrt_3(x);

    long long l = a * a;
    long long r = (a + 1) * (a + 1);

    if (l * a == x)
        return l;

    long long m;

    while (l < r - 1)
    {
        m = (l + r) / 2;

        if (m * a == x)
            return m;

        if (m * a > x)
            r = m;
        else
            l = m;
    }

    return 0;
}

unsigned g(unsigned x)
{
    if (x <= 3)
        return x;

    long long x_ex = x;

    int c = 0;

    long long p = 1;
    p <<= 32;

    long long my_g;

    while (1)
    {
        x_ex = x + c * p;

        my_g = g_ex(x_ex);

        if (my_g)
            return my_g;

        c++;
    }
}

int main(void)
{
    unsigned n;
    scanf("%u", &n);

    printf("%u\n", g(n));

    return 0;
}

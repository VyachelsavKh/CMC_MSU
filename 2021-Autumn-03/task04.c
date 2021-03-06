//Задача 03-4: Разворот половины последовательности
//На стандартном потоке ввода задаётся некоторое количество целых чисел, не равных 0. Последовательность оканчивается нулём, который в неё не входит.
//На стандартный поток вывода напечатайте последовательность, полученную из исходной следующей перестановкой чисел. 
//Сначала выводятся все нечётные элементы исходной последовательности (то есть первый, третий, пятый и так далее), а затем — все чётные в обратном порядке. 
//Число 0, являющееся признаком конца последовательности, выводить не нужно.
//Указание: использовать массивы запрещается.

#include "stdio.h"

void scan_chet(void);
void scan_nechet(void);

void scan_nechet(void)
{
    int n;
    scanf("%d", &n);

    if (n)
    {
        printf("%d ", n);
        scan_chet();
    }
}

void scan_chet(void)
{
    int n;
    scanf("%d", &n);

    if (n)
    {
        scan_nechet();
        printf("%d ", n);
    }
}

int main(void)
{
    scan_nechet();

    return 0;
}

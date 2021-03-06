//Задача 05-3: Перетасовка последовательности
//На вход программе подается последовательность натуральных чисел, заканчивающаяся нулем (ноль в последовательность не входит) 
//a1, a2, ..., an, 0. Все числа в последовательности не превосходят 109.
//Требуется распечатать сначала все элементы последовательности, стоящие на нечетных местах в том порядке, в котором они встречаются в последовательности, 
//а затем все элементы стоящие на четных местах в том порядке, в котором они встречаются в последовательности.
//Гарантируется, что программе выделено как минимум в 3 раза больше памяти, чем необходимо для хранения всей последовательности. 
//Преподаватели могут произвольно менять ограничение по памяти и размеры тестов при условии сохранения этого ограничения. 
//Вся динамически выделенная в программе память должна быть освобождена в конце.

#include "stdio.h"
#include "stdlib.h"

int main(void)
{
    int size = 8;
    int* mas = (int*)malloc(size * sizeof(int));

    int count = 0;
    int cur;

    while (scanf("%d", &cur) != EOF)
    {
        if (!cur)
            break;

        if (count >= size - 2)
        {
            size *= 2;
            mas = (int*)realloc(mas, size * sizeof(int));
        }

        mas[count] = cur;
        count++;
    }

    for (int i = 0; i < count; i += 2)
        printf("%d ", mas[i]);

    for (int i = 1; i < count; i += 2)
        printf("%d ", mas[i]);

    free(mas);

    return 0;
}

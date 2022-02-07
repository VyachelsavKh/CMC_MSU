//Задача 05-5: Конкатенация строк
//На вход программе подается число L, за которым следуют строки s1, s2 и s3. Каждая из них состоит ровно из L маленьких латинских букв. 
//Строки разделены одним или несколькими пробелами и/или переводами строк.
//Программа должна выводить строку, полученную конкатенацией строк s3, s1 и s2.
//Гарантируется, что памяти, выделенной программе, хватит для хранения всех трех строк. 
//Преподаватели могут произвольно менять ограничение по памяти и размеры тестов при условии сохранения этого ограничения. 
//Вся динамически выделенная в программе память должна быть освобождена в конце.
//Указание: в данной задаче память для хранения строк должна выделяться динамически с помощью функции malloc.

#include "stdio.h"
#include "stdlib.h"
#include "string.h"

int main(void)
{
    int l;
    scanf("%d", &l);

    char* s1 = (char*)malloc((l + 5) * sizeof(char));
    char* s2 = (char*)malloc((l + 5) * sizeof(char));
    char* s3 = (char*)malloc((l + 5) * sizeof(char));

    scanf("%s%s%s", s1, s2, s3);

    printf("%s%s%s", s3, s1, s2);

    free(s1);
    free(s2);
    free(s3);

    return 0;
}
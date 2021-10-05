//Задача 01-6: Поворот
//На вход программе подается беззнаковое 32-битное целое число N и натуральное число K (1 ≤ K ≤ 31). 
//Требуется циклически сдвинуть биты числа N вправо на K битов и вывести полученное таким образом число.

#include "stdio.h"

int main(void)
{
	unsigned int n, k;

	scanf("%u%u", &n, &k);


	printf("%u", (n >> k) | (n << (32 - k)));

	return 0;
}
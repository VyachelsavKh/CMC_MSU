//Задача 03-2: Проще некуда
//На вход программе подается натуральное число N, не превосходящее 10^9. Требуется найти наименьшее возможное простое число P, больше либо равное N.
//Указание: реализуйте функцию isprime, проверяющую число на простоту.

#include "stdio.h"

int isprime(int n)
{
	if (n == 1)
		return 0;

	for (int i = 2; i * i <= n; i++)
		if (n % i == 0)
			return 0;

	return 1;
}

int main(void)
{
	int n;
	scanf("%d", &n);

	if (n <= 2)
	{
		printf("2");
		return 0;
	}

	int i = n + !(n & 1);;
	for (; !isprime(i); i += 2);

	printf("%d", i);

	return 0;
}

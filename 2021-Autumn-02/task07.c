//Задача 02-7: Проверка на перестановочность
//На вход программе подается натуральное число N и, далее, N целых чисел. Все числа не превосходят 10000 по абсолютной величине. 
//Программа должна выводить Yes, если данная последовательность задает перестановку и No в противном случае.

#include "stdio.h"
#include "malloc.h"

int main(void)
{
	int n;
	scanf("%d", &n);

	int* mas = (int*)malloc((n + 1) * sizeof(int));

	for (int i = 1; i <= n; i++)
		mas[i] = 0;

	int x;

	int flag = 1;

	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &x);

		if (x <= 0 || x > n)
		{
			flag = 0;
			continue;
		}

		if (mas[x] != 0)
		{
			flag = 0;
			continue;
		}

		mas[x] = 1;
	}

	if (flag)
		printf("Yes");
	else
		printf("No");

	free(mas);

	return 0;
}

//Задача 05-14: Гиперпростые числа
//Простое натуральное число называется гиперпростым, если любое число, получающееся из него откидыванием нескольких последних цифр, тоже является простым. 
//Например, число 7331 – гиперпростое, т.к. и оно само, и числа 733, 73, 7 являются простыми. Найдите все N-значные гиперпростые числа.
//Входные данные: единственное целое число N (1 ≤ N ≤ 9).
//Выходные данные: возрастающая последовательность целых чисел через пробел – ответ задачи.

#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#ifdef __cplusplus
#pragma warning(disable:4996)
#endif

int is_prime(long long n)
{
	int ans = 1;

	for (long long i = 2; i * i <= n; i++)
		if (n % i == 0)
		{
			ans = 0;
			break;
		}

	return ans;
}

int main(void)
{
	long long** ans = (long long**)malloc(10 * sizeof(long long*));
	ans[1] = (long long*)malloc(4 * sizeof(long long));
	ans[2] = (long long*)malloc(4 * 4 * sizeof(long long));
	ans[3] = (long long*)malloc(4 * 4 * 4 * sizeof(long long));
	ans[4] = (long long*)malloc(4 * 4 * 4 * 4 * sizeof(long long));
	ans[5] = (long long*)malloc(4 * 4 * 4 * 4 * 4 * sizeof(long long));
	ans[6] = (long long*)malloc(4 * 4 * 4 * 4 * 4 * 4 * sizeof(long long));
	ans[7] = (long long*)malloc(4 * 4 * 4 * 4 * 4 * 4 * 4 * sizeof(long long));
	ans[8] = (long long*)malloc(4 * 4 * 4 * 4 * 4 * 4 * 4 * 4 * sizeof(long long));
	ans[9] = (long long*)malloc(4 * 4 * 4 * 4 * 4 * 4 * 4 * 4 * 4 * sizeof(long long));

	ans[1][0] = 2;
	ans[1][1] = 3;
	ans[1][2] = 5;
	ans[1][3] = 7;

	int count[10];
	count[1] = 4;
	count[2] = 0;
	count[3] = 0;
	count[4] = 0;
	count[5] = 0;
	count[6] = 0;
	count[7] = 0;
	count[8] = 0;
	count[9] = 0;

	int add_n[] = { 1, 3, 7, 9 };

	for (int i = 2; i <= 9; i++)
	{
		int cur_count = count[i - 1];

		for (int j = 0; j < cur_count; j++)
		{
			long long cur_num = ans[i - 1][j] * 10;

			for (int k = 0; k < 4; k++)
			{
				long long cur_num_add = cur_num + add_n[k];

				if (is_prime(cur_num_add))
				{
					ans[i][count[i]] = cur_num_add;
					count[i]++;
				}
			}
		}
	}

	int n;
	scanf("%d", &n);

	for (int i = 0; i < count[n]; i++)
		printf("%lld ", ans[n][i]);

	for (int i = 1; i < 9; i++)
		free(ans[i]);

	free(ans);

	return 0;
}

//Задача 05-16: Апельсин
//К Вам на улице подходит незнакомец и говорит, что всем известно эффективное решение задачи вычисления i-ого члена последовательности Фибоначчи по модулю числа p*. 
//Однако, теперь его интересует более общая задача для произвольной линейной рекуррентной последовательности, заданной формулой
//Fn = A1 * Fn-1 + ... + AkFn-k.
//Не в силах противостоять ему, Вы решаете помочь. Ваша задача посчитать FN mod p.
//Входные данные имеют следующий формат. Сначала идут целые положительные числа k, N, p каждое с новой строки.2 ≤ k ≤ 10, N ≤ 2*109, p ≤ 2*105. 
//В следующей строке содержатся первые k членов данной последовательности F1..Fk. Каждое число целое неотрицательное и не превосходит 105. 
//В последней строке файла содержатся коэффициенты A1..Ak. Каждое число целое неотрицательное и не превосходит 105.

#include "stdio.h"
#include "stdlib.h"
#include "string.h"

long long** matrix_multiply(long long** m1, long long** m2, int k, int mod)
{
	long long** ans = (long long**)malloc(k * sizeof(long long*));
	for (int i = 0; i < k; i++)
		ans[i] = (long long*)malloc(k * sizeof(long long));

	for (int i = 0; i < k; i++)
		for (int j = 0; j < k; j++)
			ans[i][j] = 0;

	for (int i = 0; i < k; i++)
		for (int j = 0; j < k; j++)
			for (int p = 0; p < k; p++)
			{
				ans[i][j] += ((m1[i][p] % mod) * (m2[p][j] % mod)) % mod;
				ans[i][j] %= mod;
			}

	return ans;
}

long long** matrix_power(long long** m, int k, int power, int mod)
{
	long long** ans;

	if (power == 1)
	{
		ans = (long long**)malloc(k * sizeof(long long*));
		for (int i = 0; i < k; i++)
			ans[i] = (long long*)malloc(k * sizeof(long long));

		for (int i = 0; i < k; i++)
			for (int j = 0; j < k; j++)
				ans[i][j] = m[i][j];

		return ans;
	}

	if (power % 2)
	{
		long long** a = matrix_power(m, k, power - 1, mod);

		ans = matrix_multiply(a, m, k, mod);

		for (int i = 0; i < k; i++)
			free(a[i]);
		free(a);
	}
	else
	{
		long long** a = matrix_power(m, k, power / 2, mod);

		ans = matrix_multiply(a, a, k, mod);

		for (int i = 0; i < k; i++)
			free(a[i]);
		free(a);
	}

	return ans;
}

int main(void)
{
	int k, N, p;
	scanf("%d%d%d", &k, &N, &p);

	long long* F = (long long*)malloc(k * sizeof(long long));
	for (int i = 0; i < k; i++)
		scanf("%lld", &F[i]);

	long long** A = (long long**)malloc(k * sizeof(long long*));
	for (int i = 0; i < k; i++)
		A[i] = (long long*)malloc(k * sizeof(long long));

	for (int i = 0; i < k; i++)
		for (int j = 0; j < k; j++)
			A[i][j] = 0;

	for (int i = 0; i < k; i++)
		scanf("%lld", &A[0][i]);

	if (N < k)
	{
		printf("%llu", F[N - 1] % p);
		return 0;
	}

	for (int i = 1; i < k; i++)
		A[i][i - 1] = 1;

	long long** A_N = matrix_power(A, k, N - k, p);

	long long ans = 0;

	for (int i = 0; i < k; i++)
	{
		ans += (A_N[0][i] * F[k - 1 - i]) % p;
		ans %= p;
	}

	printf("%lld", ans);
	
	for(int i = 0; i < k; i++)
		free(A[i]);
	free(A);
	
	free(F);
	
	for(int i = 0; i < k; i++)
		free(A_N[i]);
	free(A_N);

	return 0;
}

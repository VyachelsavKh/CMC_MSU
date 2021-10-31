//Задача 02-15: Не пара 2
//Преподаватели первого курса создали набор, содержащий N (1 ≤ N ≤ 1 500 000) целых неотрицательных чисел, не превосходящих 1 500 000 000. 
//Известно, что ровно два различных числа в этом наборе встречается по одному разу, а остальные — ровно по два раза. Помогите преподавателям найти эти числа.
//Входные данные: в первой входной строке вводится число N, затем вводятся N целых неотрицательных чисел, не превосходящих 1 500 000 000.
//Выходные данные: ваша программа должна определить числа, встречающиеся один раз, и вывести их в возрастающем порядке.
//Указание: сортировать исходный массив или его копии запрещается.

#include "stdio.h"
#include "malloc.h"

#ifdef __cplusplus
#pragma warning(disable:4996)
#endif

struct vector
{
	int* mas;
	int used;
	int size;
};

void init(struct vector* a, int n)
{
	int n_ = n + 1;
	n_ |= n_ >> 1;
	n_ |= n_ >> 2;
	n_ |= n_ >> 4;
	n_ |= n_ >> 8;
	n_ |= n_ >> 16;

	n_ = (n_ - (n_ >> 1)) << 2;

	a->mas = (int*)malloc(n_ * sizeof(int));
	a->used = n;
	a->size = n_;

	for (int i = 0; i < n; i++)
		a->mas[i] = 0;
}
void clear(struct vector* a)
{
	a->used = 0;
}
void destroy(struct vector* a)
{
	free(a->mas);
	a->used = 0;
	a->size = 0;
}

void vector_print(struct vector* a, int l, int r)
{
	for (int i = l; i <= r; i++)
		printf("%d ", a->mas[i]);
}

int size(struct vector* a)
{
	return a->used;
}
int capacity(struct vector* a)
{
	return a->size;
}

int overflow(struct vector* a)
{
	return a->size - a->used <= 1;
}
void expand(struct vector* a)
{
	if (!overflow(a))
		return;

	int* b = (int*)malloc((a->size == 0 ? 1 : a->size) * 2 * sizeof(int));

	a->size *= 2;

	for (int i = 0; i < a->used; i++)
	{
		b[i] = a->mas[i];
	}

	free(a->mas);

	a->mas = b;
}

int empty(struct vector* a)
{
	return a->used <= (a->size - 2) / 2;
}
void squeeze(struct vector* a)
{
	if (!empty(a))
		return;

	int* b = (int*)malloc(a->size / 2 * sizeof(int));

	a->size /= 2;

	for (int i = 0; i < a->used; i++)
	{
		b[i] = a->mas[i];
	}

	free(a->mas);

	a->mas = b;
}

void push_back(struct vector* a, int n)
{
	expand(a);
	a->mas[a->used] = n;
	a->used++;
}
void insert(struct vector* a, int pos, int n)
{
	if (pos < 0 || pos >= a->used)
		return;

	expand(a);

	int cur = a->mas[pos];
	a->mas[pos] = n;
	int prev = cur;

	for (int i = pos + 1; i < a->used; i++)
	{
		cur = a->mas[i];
		a->mas[i] = prev;
		prev = cur;
	}

	a->mas[a->used] = prev;

	a->used++;
}

void pop_back(struct vector* a)
{
	if (!a->used)
		return;

	a->used--;

	squeeze(a);
}
void erase(struct vector* a, int pos)
{
	if (pos < 0 || pos >= a->used)
		return;

	for (int i = pos; i < a->used - 1; i++)
		a->mas[i] = a->mas[i + 1];

	a->used--;

	squeeze(a);
}

void swap(int* a, int* b)
{
	int t;
	t = *b;
	*b = *a;
	*a = t;
}

void reverse(struct vector* a)
{
	for (int i = 0; i < a->used / 2; i++)
		swap(a->mas + i, a->mas + a->used - 1 - i);
}

int main(void)
{
	int n;
	scanf("%d", &n);

	struct vector mas;
	init(&mas, n);

	for (int i = 0; i < n; i++)
		scanf("%d", mas.mas + i);

	unsigned int bits[31];

	for (int i = 0; i < 31; i++)
		bits[i] = 0;

	unsigned int x_xor_y = 0;

	for (int i = 0; i < n; i++)
	{
		x_xor_y ^= mas.mas[i];

		for (int j = 0; (j < 31) && (mas.mas[i] >> j); j++)
			if (mas.mas[i] & (1 << j))
				bits[j] ^= mas.mas[i];
	}

	unsigned int x = x_xor_y, y;

	int flag = 0;

	for (int i = 0; i < 31; i++)
		if (bits[i] != 0 && bits[i] != x_xor_y)
		{
			x = bits[i];
			y = x ^ x_xor_y;

			flag = 1;

			break;
		}

	if (flag)
		printf("%u %u", (x < y ? x : y), (x > y ? x : y));
	else
		printf("0 %d", x_xor_y);

	destroy(&mas);

	return 0;
}

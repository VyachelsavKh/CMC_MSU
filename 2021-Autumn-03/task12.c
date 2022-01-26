//Задача 03-12: Жертвоприношение
//Вводится целое число N (1 ≤ N ≤ 14), и следом N целых чисел A1,...,AN (0 ≤ Ai ≤ 100). 
//Требуется найти два непустых подмножества таких, что сумма их элементов равна и максимальна среди всех возможных решений (подмножества не должны пересекаться), 
//и вывести эту сумму или 0, если такой пары нет.

#include "stdio.h"
#include "malloc.h"

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

void vector_print(struct vector* a)
{
	for (int i = 0; i < a->used; i++)
	{
		printf("%d ", a->mas[i]);
	}
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

int sum_elem(struct vector a)
{
	int sum = 0;

	for (int i = 0; i < a.used; i++)
	{
		sum += a.mas[i];
	}

	return sum;
}

int main(void)
{
	int n;
	scanf("%d", &n);

	int mas[20];

	for (int i = 0; i < n; i++)
		scanf("%d", mas + i);

	struct vector set1, ost, set2;

	init(&set1, 20);
	init(&ost, 20);
	init(&set2, 20);

	int max_sum = 0;

	int cur_sum1, cur_sum2;

	for (int i = 0; i < (1 << n); i++)
	{
		clear(&set1);
		clear(&ost);

		for (int j = 0; j < n; j++)
		{
			if (i & (1 << j))
				push_back(&set1, mas[j]);
			else
				push_back(&ost, mas[j]);
		}

		if (set1.used && ost.used)
		{
			for (int k = 0; k < (1 << ost.used); k++)
			{
				clear(&set2);

				for (int m = 0; m < ost.used; m++)
				{
					if (k & (1 << m))
						push_back(&set2, ost.mas[m]);
				}

				cur_sum1 = sum_elem(set1);
				cur_sum2 = sum_elem(set2);

				if (cur_sum1 == cur_sum2 && cur_sum1 > max_sum)
					max_sum = cur_sum1;
			}
		}
	}

	printf("%d", max_sum);

	destroy(&set1);
	destroy(&ost);
	destroy(&set2);

	return 0;
}

//Задача 02-1: Разворот последовательности
//На стандартном потоке ввода задаётся некоторое количество целых чисел (не более 10000 штук), не равных 0. 
//Последовательность оканчивается нулём, который в неё не входит.
//На стандартный поток вывода напечатайте исходную последовательность в обратном порядке. 
//Число 0, являющееся признаком конца последовательности, выводить не нужно.
//Указание: при решении используйте массивы.

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

int main(void)
{
	int n;

	struct vector a;
	init(&a, 0);

	while (1)
	{
		scanf("%d", &n);

		if (!n)
			break;

		push_back(&a, n);
	}

	reverse(&a);

	vector_print(&a);
	
	destroy(&a);

	return 0;
}

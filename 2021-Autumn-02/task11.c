//Задача 02-11: Все могут короли?
//На шахматной доске стоят белые короли. Вася хочет поставить на доску несколько черных фигур так, 
//чтобы никакую из них короли не били (не стояли в клетках, граничащих хотя бы вершиной). 
//Какое наибольшее количество фигур может поставить Вася?
//На вход подается в строке без разделителей список клеток, в которых стоят короли 
//(в шахматной аннотации, используются строчные латинские буквы от a до h). 
//Выведите единственное целое число - наибольшее количество черных фигур.

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
	char inp[200];

	scanf("%s", inp);

	struct vector board[10];
	for (int i = 0; i < 10; i++)
		init(board + i, 10);

	struct vector kings[10];
	for (int i = 0; i < 10; i++)
		init(kings + i, 10);

	int horizontal, vertical;

	for (int i = 0; inp[i] != '\0'; i += 2)
	{
		horizontal = inp[i] - 'a' + 1;
		vertical = inp[i + 1] - '0';

		kings[horizontal].mas[vertical] = 1;
	}

	for (int j = 1; j < 9; j++)
		for (int i = 1; i < 9; i++)
			if (kings[j].mas[i])
			{
				board[j].mas[i] = 1;
				board[j].mas[i - 1] = 1;
				board[j].mas[i + 1] = 1;

				board[j - 1].mas[i] = 1;
				board[j - 1].mas[i - 1] = 1;
				board[j - 1].mas[i + 1] = 1;

				board[j + 1].mas[i] = 1;
				board[j + 1].mas[i - 1] = 1;
				board[j + 1].mas[i + 1] = 1;
			}

	int sum = 64;

	for (int j = 1; j < 9; j++)
		for (int i = 1; i < 9; i++)
			sum -= board[j].mas[i];

	printf("%d", sum);

	for (int i = 0; i < 10; i++)
	{
		destroy(board + i);
		destroy(kings + i);
	}

	return 0;
}

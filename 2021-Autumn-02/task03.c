//Задача 02-3: Чередование массивов
//Даны два массива a[] и b[]. Требуется составить массив, в который входят поочередно элементы первого и второго массивов, 
//то есть элементы a[0], b[0], a[1], b[1] и так далее. Если длина массивов различна, требуется вывести в конце оставшуюся часть более длинного массива.
//На стандартном потоке ввода задано целое число N (N ≥ 0) и далее N элементов первого массива 
//(если N = 0, массив считается пустым и ни одного элемента не задано), далее целое число M (M ≥ 0) и M элементов второго массива. 
//Известно, что хотя бы один входной массив непуст.
//На стандартный поток вывода напечатайте массив - результат описанного выше преобразования.

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

#define min(a, b) ((a) < (b) ? (a) : (b))

int main(void)
{
	int n;
	struct vector a;

	scanf("%d", &n);

	init(&a, n);

	for (int i = 0; i < n; i++)
		scanf("%d", a.mas + i);

	int m;
	struct vector b;

	scanf("%d", &m);

	init(&b, m);

	for (int i = 0; i < m; i++)
		scanf("%d", b.mas + i);

	struct vector c;
	init(&c, 0);

	int i;

	for (i = 0; i < min(a.used, b.used); i++)
	{
		push_back(&c, a.mas[i]);
		push_back(&c, b.mas[i]);
	}

	int j;

	for (j = i; j < a.used; j++)
		push_back(&c, a.mas[j]);

	for (j = i; j < b.used; j++)
		push_back(&c, b.mas[j]);

	vector_print(&c);
	
	destroy(&a);
	destroy(&b);
	destroy(&c);

	return 0;
}

//Задача 02-9: Вычисление полинома
//На стандартном потоке ввода задан полином вида a0+a1*x + ... + an-1*xn-1: сначала задано натуральное число n, за ним идут n целых чисел ai (0 ≤ i ≤ n-1). 
//После полинома задается натуральное число m и m целых чисел xj.
//На стандартный поток вывода напечатайте значения заданного полинома для каждого из чисел xj в порядке, обратном тому, в котором были заданы эти числа.
//Указание: считайте, что во время вычисления промежуточных результатов переполнений целочисленной арифметики не возникает (входные данные корректны).

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

long long calculate(struct vector* a, long long x)
{
	long long sum = 0;

	for (int i = a->used - 1; i >= 0; i--)
	{
		sum *= x;
		sum += a->mas[i];
	}

	return sum;
}

int main(void)
{
	int n;
	scanf("%d", &n);

	struct vector a;
	init(&a, n);

	for (int i = 0; i < n; i++)
		scanf("%d", a.mas + i);

	int m;
	scanf("%d", &m);

	struct vector ans;
	init(&ans, m);

	long long x;

	for (int i = 0; i < m; i++)
	{
		scanf("%lld", &x);
		ans.mas[i] = calculate(&a, x);
	}

	reverse(&ans);

	vector_print(&ans, 0, ans.used - 1);

	destroy(&a);
	destroy(&ans);

	return 0;
}

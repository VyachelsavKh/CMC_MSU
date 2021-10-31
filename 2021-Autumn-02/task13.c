//Задача 02-13: Кубики наоборот
//Вася выложил на шахматную доску кубики в несколько столбиков. При этом если один кубик лежит на другом, 
//то нижняя грань верхнего кубика совпадает с верхней гранью нижнего кубика, а у каждого из кубиков, 
//лежащих непосредственно на доске, нижняя грань совпадает с одной из клеток доски. 
//Затем Вася посмотрел спереди на сооружение (увидев при этом восемь столбиков) и записал высоту каждого столбика слева направо.
//Потом он посчитал высоту каждого столбика и записал ее, глядя на кубики справа от доски. 
//После этого Вася сообщил найденные 16 чисел Пете. Петя хочет узнать, какое наименьшее количество кубиков мог использовать Вася.
//На вход программе подается 16 целых неотрицательных чисел (каждое не больше 100) в указанном порядке. 
//Требуется вывести единственное целое число – наименьшее возможное количество кубиков, либо число –1, если Вася ошибся в подсчете.

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

void sort(struct vector* mas, int n)
{
	for (int i = 0; i < n; i++)
		for (int j = i + 1; j < n; j++)
			if (mas->mas[i] > mas->mas[j])
				swap(mas->mas + i, mas->mas + j);
}

int main(void)
{
	struct vector horizontal, vertical;
	init(&horizontal, 8);
	init(&vertical, 8);

	for (int i = 0; i < 8; i++)
		scanf("%d", horizontal.mas + i);

	for (int i = 0; i < 8; i++)
		scanf("%d", vertical.mas + i);

	sort(&horizontal, 8);
	sort(&vertical, 8);

	if (horizontal.mas[7] != vertical.mas[7])
	{
		printf("-1");
		return 0;
	}

	int sum = 0;

	int i = 0, j = 0;

	for (; horizontal.mas[i] == 0; i++);
	for (; vertical.mas[j] == 0; j++);

	while (i < 8 && j < 8)
	{
		if (horizontal.mas[i] == vertical.mas[j])
		{
			sum += horizontal.mas[i];
			i++;
			j++;
		}
		else if (horizontal.mas[i] < vertical.mas[j])
		{
			sum += horizontal.mas[i];
			i++;
		}
		else if (horizontal.mas[i] > vertical.mas[j])
		{
			sum += vertical.mas[j];
			j++;
		}
	}

	while (i < 8)
	{
		sum += horizontal.mas[i];
		i++;
	}

	while (j < 8)
	{
		sum += vertical.mas[j];
		j++;
	}

	printf("%d", sum);

	destroy(&horizontal);
	destroy(&vertical);

	return 0;
}

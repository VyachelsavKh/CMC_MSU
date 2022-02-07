//Необходимо реализовать операции сложения, вычитания и умножения двух чисел a и b. Каждое число содержит не более 10000 десятичных знаков, то есть 0 ≤ a, b < 10^10001.
//Входные данные:
//Числа a и b, разделённые знаком сложения, вычитания или умножения.
//Выходные данные: результат выполнения соответствующей операции

#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#ifndef vectorh
#define vectorh

#include "stdio.h"
#include "malloc.h"

struct vector
{
	int* mas;
	int used;
	int size;
};

//======All functions======

void vector_init(struct vector*);
void vector_destroy(struct vector*);
void vector_copy(struct vector*, const struct vector*);

void vector_expand_Dont_use_it(struct vector*);
void vector_squeeze_Dont_use_it(struct vector* a);

int vector_front(const struct vector*);
int vector_back(const struct vector*);

int* vector_begin(const struct vector*);
int* vector_end(const struct vector*);

int vector_size(const struct vector*);
int vector_capacity(const struct vector*);
int vector_empty(const struct vector*);

void vector_resize(struct vector*, int);
void vector_clear(struct vector*);
void vector_insert(struct vector*, int, int);
void vector_erase(struct vector*, int);
void vector_push_back(struct vector*, int);
void vector_pop_back(struct vector*);
void vector_swap(struct vector*, struct vector*);

void vector_printf(const struct vector*);
void vector_printf_l_r(const struct vector*, int, int);

//======Member functions======

void vector_init(struct vector* a)
{
	a->mas = (int*)malloc(8 * sizeof(int));
	a->used = 0;
	a->size = 8;
}
void vector_destroy(struct vector* a)
{
	free(a->mas);
	a->mas = 0;
	a->used = 0;
	a->size = 0;
}
void vector_copy(struct vector* dst, const struct vector* src)
{
	if (dst->size < src->size)
		vector_resize(dst, src->used);

	for (int i = 0; i < src->used; i++)
		dst->mas[i] = src->mas[i];

	dst->used = src->used;
}

//======Private functions======

void vector_expand_Dont_use_it(struct vector* a)
{
	if (a->size >= a->used + 1)
		return;

	a->size *= 2;
	a->mas = (int*)realloc(a->mas, a->size * sizeof(int));;
}
void vector_squeeze_Dont_use_it(struct vector* a)
{
	if (a->used >= a->size / 2 + 1 || a->size <= 8)
		return;

	a->size /= 2;
	a->mas = (int*)realloc(a->mas, a->size * sizeof(int));;
}

//======Element access======

int vector_front(const struct vector* a)
{
	return a->mas[0];
}
int vector_back(const struct vector* a)
{
	return a->mas[a->used - 1];
}

//======Iterators======

int* vector_begin(const struct vector* a)
{
	return &a->mas[0];
}
int* vector_end(const struct vector* a)
{
	return &a->mas[a->used];
}

//======Capacity======

int vector_size(const struct vector* a)
{
	return a->used;
}
int vector_capacity(const struct vector* a)
{
	return a->size;
}
int vector_empty(const struct vector* a)
{
	return a->used == 0;
}

//======Modifiers======

void vector_resize(struct vector* a, int count)
{
	int prev_used = a->used;
	a->size = (count > 8 ? count : 8);
	a->used = a->size;

	a->mas = (int*)realloc(a->mas, a->size * sizeof(int));

	for (int i = prev_used; i < a->size; i++)
		a->mas[i] = 0;
}
void vector_clear(struct vector* a)
{
	a->used = 0;
}
void vector_insert(struct vector* a, int pos, int n)
{
	vector_expand_Dont_use_it(a);

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
void vector_erase(struct vector* a, int pos)
{
	for (int i = pos; i < a->used - 1; i++)
		a->mas[i] = a->mas[i + 1];

	a->used--;

	vector_squeeze_Dont_use_it(a);
}
void vector_push_back(struct vector* a, int n)
{
	vector_expand_Dont_use_it(a);
	a->mas[a->used] = n;
	a->used++;
}
void vector_pop_back(struct vector* a)
{
	if (!a->used)
		return;

	a->used--;

	vector_squeeze_Dont_use_it(a);
}
void vector_swap(struct vector* a, struct vector* b)
{
	int* mas_tmp = a->mas;
	int used_tmp = a->used;
	int size_tmp = b->size;

	a->mas = b->mas;
	a->used = b->used;
	a->size = b->size;

	b->mas = mas_tmp;
	b->used = used_tmp;
	b->size = size_tmp;
}

//======Printf functions======

void vector_printf(const struct vector* a)
{
	for (int i = 0; i < a->used - 1; i++)
	{
		printf("%d ", a->mas[i]);
	}
	printf("%d", a->mas[a->used - 1]);
}
void vector_printf_l_r(const struct vector* a, int l, int r)
{
	for (int i = l; i < r - 1; i++)
	{
		printf("%d ", a->mas[i]);
	}
	printf("%d", a->mas[r]);
}
#endif

#ifndef lnumh
#define lnumh

#include "stdio.h"
#include "stdlib.h"
#include "string.h"

void lnum_string_reverse(char s[])
{
	int i, j;
	char c;

	for (i = 0, j = strlen(s) - 1; i < j; i++, j--) {
		c = s[i];
		s[i] = s[j];
		s[j] = c;
	}
}
void lnum_itoa(int n, char s[])
{
	int i, sign;

	if ((sign = n) < 0)
		n = -n;

	i = 0;

	do
	{
		s[i++] = n % 10 + '0';
	} while ((n /= 10) > 0);

	if (sign < 0)
		s[i++] = '-';

	s[i] = '\0';

	lnum_string_reverse(s);
}

//Based on https://e-maxx.ru/algo/big_integer
struct lnum
{
	struct vector num;
	int base;
	int sign;
};

//======All functions======
void lnum_init(struct lnum*);
void lnum_destroy(struct lnum*);
void lnum_copy(struct lnum*, const struct lnum*);

void lnum_read(struct lnum*, const char*);
void lnum_printf(const struct lnum*);
char* lnum_to_string(const struct lnum*, char*);
int lnum_cmp(const struct lnum*, const struct lnum*);
struct lnum* lnum_add_positive_Dont_use_it(const struct lnum*, const struct lnum*);
struct lnum* lnum_subtract_positive_Dont_use_it(const struct lnum*, const struct lnum*);
struct lnum* lnum_multiply_positive_Dont_use_it(const struct lnum*, const struct lnum*);
struct lnum* lnum_add(const struct lnum*, const struct lnum*);
struct lnum* lnum_subtract(const struct lnum*, const struct lnum*);
struct lnum* lnum_multiply(const struct lnum*, const struct lnum*);

void lnum_swap(struct lnum*, struct lnum*);

//======Member functions======

void lnum_init(struct lnum* n)
{
	n->base = 1000000000;
	n->sign = 1;
	vector_init(&n->num);
}
void lnum_destroy(struct lnum* n)
{
	vector_destroy(&n->num);
}
void lnum_copy(struct lnum* dst, const struct lnum* src)
{
	vector_copy(&dst->num, &src->num);
	dst->sign = src->sign;
}

//======Private functions======

#define lnum_max(a, b) ((a) > (b) ? (a) : (b))
struct lnum* lnum_add_positive_Dont_use_it(const struct lnum* first, const struct lnum* second)
{
	struct lnum* ans = (struct lnum*)malloc(sizeof(struct lnum));
	lnum_init(ans);
	vector_copy(&ans->num, &first->num);

	int carry = 0;

	for (int i = 0; i < lnum_max(vector_size(&ans->num), vector_size(&second->num)) || carry; i++)
	{
		if (i == vector_size(&ans->num))
			vector_push_back(&ans->num, 0);

		ans->num.mas[i] += carry + (i < vector_size(&second->num) ? second->num.mas[i] : 0);

		carry = ans->num.mas[i] >= first->base;

		if (carry)
			ans->num.mas[i] -= first->base;
	}

	return ans;
}
struct lnum* lnum_subtract_positive_Dont_use_it(const struct lnum* first, const struct lnum* second)
{
	struct lnum* ans = (struct lnum*)malloc(sizeof(struct lnum));
	lnum_init(ans);
	vector_copy(&ans->num, &first->num);

	int carry = 0;
	for (int i = 0; i < vector_size(&second->num) || carry; i++)
	{
		ans->num.mas[i] -= carry + (i < vector_size(&second->num) ? second->num.mas[i] : 0);

		carry = ans->num.mas[i] < 0;

		if (carry)
			ans->num.mas[i] += first->base;
	}

	while (vector_size(&ans->num) > 1 && vector_back(&ans->num) == 0)
		vector_pop_back(&ans->num);

	return ans;
}
struct lnum* lnum_multiply_positive_Dont_use_it(const struct lnum* first, const struct lnum* second)
{
	struct lnum* ans = (struct lnum*)malloc(sizeof(struct lnum));
	lnum_init(ans);
	vector_resize(&ans->num, vector_size(&first->num) + vector_size(&second->num) + 1);

	for (int i = 0; i < vector_size(&first->num); i++)
		for (int j = 0, carry = 0; j < vector_size(&second->num) || carry; j++)
		{
			long long cur = (first->num.mas[i]);
			cur *= (j < vector_size(&second->num) ? second->num.mas[j] : 0);
			cur += ans->num.mas[i + j];
			cur += carry;

			ans->num.mas[i + j] = cur % first->base;
			carry = cur / first->base;
		}

	while (vector_size(&ans->num) > 1 && vector_back(&ans->num) == 0)
		vector_pop_back(&ans->num);

	return ans;
}

//======Non-member functions======

void lnum_read(struct lnum* n, const char* str)
{
	char* s = (char*)malloc((strlen(str) + 1) * sizeof(char));

	if (str[0] == '-')
	{
		n->sign = -1;
		strcpy(s, str + 1);
	}
	else
		strcpy(s, str);

	for (int i = strlen(s); i > 0; i -= 9)
	{
		s[i] = 0;
		vector_push_back(&n->num, atoi(i >= 9 ? s + i - 9 : s));
	}

	free(s);

	while (vector_size(&n->num) > 1 && vector_back(&n->num) == 0)
		vector_pop_back(&n->num);
}
void lnum_printf(const struct lnum* n)
{
	if (n->sign == -1 && !vector_empty(&n->num))
		printf("-");

	printf("%d", vector_empty(&n->num) ? 0 : vector_back(&n->num));

	for (int i = vector_size(&n->num) - 2; i >= 0; i--)
		printf("%09d", n->num.mas[i]);
}
char* lnum_to_string(const struct lnum* n, char* str)
{
	char tmp[15];

	if (n->sign == -1)
	{
		str[0] = '-';
		str[1] = 0;
	}
	else
		str[0] = 0;

	char zero[] = "0";

	for (int i = vector_size(&n->num) - 1; i >= 0; i--)
	{
		tmp[0] = 0;
		lnum_itoa(n->num.mas[i], tmp);
		for (int i = 1; strlen(tmp) - 9; i++)
			strcat(str, zero);
		strcat(str, tmp);
	}

	return str;
}
int lnum_cmp(const struct lnum* first, const struct lnum* second)
{
	if (vector_size(&first->num) > vector_size(&second->num))
		return 1;
	if (vector_size(&first->num) < vector_size(&second->num))
		return -1;

	int cmp = 0;

	for (int i = vector_size(&first->num) - 1; i >= 0; i--)
		if (first->num.mas[i] != second->num.mas[i])
		{
			if (first->num.mas[i] > second->num.mas[i])
			{
				cmp = 1;
				break;
			}
			if (first->num.mas[i] < second->num.mas[i])
			{
				cmp = -1;
				break;
			}
		}

	return cmp;
}
struct lnum* lnum_add(const struct lnum* first, const struct lnum* second)
{
	struct lnum* ans = (struct lnum*)malloc(sizeof(struct lnum));
	struct lnum* tmp;
	lnum_init(ans);

	if (first->sign == 1 && second->sign == 1)
	{
		tmp = lnum_add_positive_Dont_use_it(first, second);
		lnum_copy(ans, tmp);
		lnum_destroy(tmp);
	}
	if (first->sign == -1 && second->sign == 1)
	{
		tmp = lnum_subtract(second, first);
		lnum_copy(ans, tmp);
		lnum_destroy(tmp);
	}
	if (first->sign == 1 && second->sign == -1)
	{
		tmp = lnum_subtract(first, second);
		lnum_copy(ans, tmp);
		lnum_destroy(tmp);
	}
	if (first->sign == -1 && second->sign == -1)
	{
		tmp = lnum_add_positive_Dont_use_it(first, second);
		lnum_copy(ans, tmp);
		lnum_destroy(tmp);
		ans->sign = -1;
	}

	return ans;
}
struct lnum* lnum_subtract(const struct lnum* first, const struct lnum* second)
{
	struct lnum* ans = (struct lnum*)malloc(sizeof(struct lnum));
	struct lnum* tmp;
	lnum_init(ans);

	if (first->sign == 1 && second->sign == 1)
	{
		if (lnum_cmp(first, second) >= 0)
		{
			tmp = lnum_subtract_positive_Dont_use_it(first, second);
			lnum_copy(ans, tmp);
			lnum_destroy(tmp);
		}
		else
		{
			tmp = lnum_subtract_positive_Dont_use_it(second, first);
			lnum_copy(ans, tmp);
			lnum_destroy(tmp);
			ans->sign = -1;
		}
	}
	if (first->sign == -1 && second->sign == 1)
	{
		tmp = lnum_add_positive_Dont_use_it(first, second);
		lnum_copy(ans, tmp);
		lnum_destroy(tmp);
		ans->sign = -1;
	}
	if (first->sign == 1 && second->sign == -1)
	{
		tmp = lnum_add_positive_Dont_use_it(first, second);
		lnum_copy(ans, tmp);
		lnum_destroy(tmp);
	}
	if (first->sign == -1 && second->sign == -1)
	{
		if (lnum_cmp(second, first) >= 0)
		{
			tmp = lnum_subtract_positive_Dont_use_it(second, first);
			lnum_copy(ans, tmp);
			lnum_destroy(tmp);
		}
		else
		{
			tmp = lnum_subtract_positive_Dont_use_it(first, second);
			lnum_copy(ans, tmp);
			lnum_destroy(tmp);
			ans->sign = -1;
		}
	}

	return ans;
}
struct lnum* lnum_multiply(const struct lnum* first, const struct lnum* second)
{
	struct lnum* ans = (struct lnum*)malloc(sizeof(struct lnum));
	struct lnum* tmp;
	lnum_init(ans);

	tmp = lnum_multiply_positive_Dont_use_it(first, second);
	lnum_copy(ans, tmp);
	lnum_destroy(tmp);

	if (first->sign == -1 && second->sign == 1)
		ans->sign = -1;

	if (first->sign == 1 && second->sign == -1)
		ans->sign = -1;

	return ans;
}

//======Modifiers======

void lnum_swap(struct lnum* a, struct lnum* b)
{
	int sign_tmp = a->sign;
	a->sign = b->sign;
	b->sign = sign_tmp;

	vector_swap(&a->num, &b->num);
}
#endif

int is_num(char c)
{
	if (c >= '0' && c <= '9')
		return 1;
	return 0;
}
int is_mode(char c)
{
	return c == '+' || c == '-' || c == '*';
}
char read_expr(char* inp_str, char* n1, char* n2)
{
	int i = 0;

	for (; !is_num(inp_str[i]); i++);

	int j = 0;
	while (is_num(inp_str[i]))
	{
		n1[j] = inp_str[i];
		i++;
		j++;
	}
	n1[j] = 0;

	for (; !is_mode(inp_str[i]); i++);

	char mode = inp_str[i];

	i++;

	for (; !is_num(inp_str[i]); i++);

	j = 0;
	while (is_num(inp_str[i]))
	{
		n2[j] = inp_str[i];
		i++;
		j++;
	}
	n2[j] = 0;

	return mode;
}

int main(void)
{
	struct lnum n1, n2;
	struct lnum ans;
	struct lnum* tmp;

	char* inp_str = (char*)malloc(20005 * sizeof(char));
	char* n1_str = (char*)malloc(20005 * sizeof(char));
	char* n2_str = (char*)malloc(20005 * sizeof(char));

	lnum_init(&n1);
	lnum_init(&n2);
	lnum_init(&ans);

	fgets(inp_str, 20005, stdin);

	char mode = read_expr(inp_str, n1_str, n2_str);

	lnum_read(&n1, n1_str);
	lnum_read(&n2, n2_str);

	switch (mode)
	{
	default:
		break;
	case '+':
		tmp = lnum_add(&n1, &n2);
		lnum_copy(&ans, tmp);
		lnum_destroy(tmp);
		break;
	case '-':
		tmp = lnum_subtract(&n1, &n2);
		lnum_copy(&ans, tmp);
		lnum_destroy(tmp);
		break;
	case '*':
		tmp = lnum_multiply(&n1, &n2);
		lnum_copy(&ans, tmp);
		lnum_destroy(tmp);
		break;
	}

	lnum_printf(&ans);

	lnum_destroy(&n1);
	lnum_destroy(&n2);
	lnum_destroy(&ans);

	free(inp_str);
	free(n1_str);
	free(n2_str);

	return 0;
}

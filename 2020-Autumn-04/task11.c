//Задача 04-11: Экстерминатус
//Мир наш исполнен войны - целая вечность сражений во имя Императора. Он никогда не прекращает и не отступается от бесконечной вражды, а значит - не должны и мы.
//Второй год Похода Мучений. В отдалённой системе войска Императора столкнулись с планетой полной ужасающих человекоподобных зверей, представляющих собой серьёзную угрозу. 
//После ожесточённых боёв связь с ударным отрядом чёрных тамплиеров во главе с братом Герхартом была потеряна, 
//в связи с чем было приятно единственно верное решение в таких ситуациях - ЭКСТЕРМИНАТУС, то есть полное уничтожение всего живого на поверхности. 
//Для запуска орбитальной бомбардировки требуются специальные коды запуска. Обычно они приходят на отдельный канал и с ними не возникает никаких проблем, 
//но в этот раз в связи с оплошностью подчинённого несколько передач принимались по одному каналу и результаты перемешались. 
//Ваша задача состоит в том, чтобы извлечь из полученной информации коды запуска орудий.
//Передача состоит из заглавных и строчных латинских букв, цифр, а также 4 основных арифметических действий '+', '-', '*', '/'. 
//Её длина не превосходит 2000 символов. Известно, что кодом является некоторая команда вида A op B, где A и B - целые неотрицательные числа, 
//а op - одно из арифметических действий, результат которой является корректно вычислимым выражением модуль которого не превосходит 120000. 
//При этом выражение "A op B" является подстрокой исходного сообшения. Гарантируется, что числа A,B и результат операции над ними не переполняют 32-х битные целые знаковые числа. 
//Необходимо найти все такие команды и вывести их каждую с новой строки в виде A op B = res, где res - результат вычисления. Всё остальное считается мусором из других передач. 
//Заметим, что для выражения A op1 B op2 C нужно вывести
//A op1 B = res1
//B op2 C = res2

#include "stdio.h"
#include "stdlib.h"
#include "string.h"

struct string
{
	char* mas;
	int used;
	int size;
};

void init(struct string* a, int n)
{
	int n_ = n + 1;
	n_ |= n_ >> 1;
	n_ |= n_ >> 2;
	n_ |= n_ >> 4;
	n_ |= n_ >> 8;
	n_ |= n_ >> 16;

	n_ = (n_ - (n_ >> 1)) << 2;

	a->mas = (char*)malloc(n_ * sizeof(char));
	a->used = n;
	a->size = n_;

	for (int i = 0; i < n; i++)
		a->mas[i] = 0;
}
void clear(struct string* a)
{
	a->used = 0;
}
void destroy(struct string* a)
{
	free(a->mas);
	a->used = 0;
	a->size = 0;
}

void string_print(struct string* a)
{
	for (int i = 0; i <= a->used - 1; i++)
		printf("%c", a->mas[i]);
}

void push_back(struct string* a, char n)
{
	a->mas[a->used] = n;
	a->used++;
}

int is_let(char c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return 1;
	return 0;
}

int is_sign(char c)
{
	if (c == '+' || c == '-' ||c == '*' || c == '/')
		return 1;
	return 0;
}

int is_num(char c)
{
	if (c >= '0' && c <= '9')
		return 1;
	return 0;
}

int num_cpy(char* str, struct string* expr, int i)
{
	int t = i;
	while(is_num(str[t]))
	{
		push_back(expr, str[t]);
		t++;
	}
	return t;
}

struct pair
{
	int first;
	int second;
};

struct pair str_to_num(struct string* expr, int i)
{
	int n = 0;
	
	for (;is_num(expr->mas[i]); i++)
	{
		n *= 10;
		n += expr->mas[i] - '0';
	}

	struct pair out;
	out.first = n;
	out.second = i;

	return out;
}

long long make_op(long long a, long long b, char sign)
{
	if (sign == '+')
		return a + b;
	if (sign == '-')
		return a - b;
	if (sign == '*')
		return a * b;
	return a / b;
}

char str[2005];

int main(void)
{
	scanf("%s", str);
	
	int i = 0;

	struct string expr;
	init(&expr, 2005);
	clear(&expr);

	int flag;

	while (!is_num(str[i]))
		i++;

	while (1)
	{
		flag = 0;

		if (is_num(str[i]))
		{
			i = num_cpy(str, &expr, i);
		}
		else if (is_let(str[i]))
		{
			push_back(&expr, '#');

			while (!is_num(str[i]))
			{
				i++;
				if (str[i] == 0)
				{
					flag = 1; 
					break;
				}
			}
		}
		else if ( is_sign(str[i]) && !is_num(str[i + 1]) )
		{
			push_back(&expr, '#');

			while (!is_num(str[i]))
			{
				i++;
				if (str[i] == 0)
				{
					flag = 1; 
					break;
				}
			}
		}
		else
		{
			push_back(&expr, str[i]);
			i++;
		}

		if (flag || str[i] == '\0')
			break;
	}

	int a = 0, b = 0;

	i = 0;

	while (1)
	{
		if (expr.mas[i] == '#')
		{
			a = 0;
			b = 0;
			i++;
		}
		else if (is_num(expr.mas[i]))
		{
			struct pair p = str_to_num(&expr, i);
			b = p.first;
			i = p.second;
		}
		else if (is_sign(expr.mas[i]))
		{
			a = b;

			char sign = expr.mas[i];
			i++;

			struct pair p = str_to_num(&expr, i);

			b = p.first;
			i = p.second;

			if (!(b == 0 && sign == '/'))
			{
				int ans = make_op(a, b, sign);

				if (abs(ans) <= 120000)
				{
					printf("%d %c %d = %d\n", a, sign, b, ans);
				}
			}
		}
		else
			break;
	}

	return 0;
}

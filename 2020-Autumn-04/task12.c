//Задача 04-12: Вёрстка для начинающих
//Требуется написать программу для разбиения входного текста по колонкам и страницам. Известны натуральные числа K, C и S. K - число символов в одном столбце. 
//Каждая выходная страница должна содержать ровно C столбцов, в каждом столбце ровно S строк, но последняя страница может содержать меньшее число столбцов 
//и последний столбец может содержать меньшее число строк. Столбцы в странице читаются сверху вниз, слева направо.
//В каждом столбце каждая строка должна иметь длину K символов. В очередной строке очередного столбца должно быть выведено максимальное количество очередных слов входного текста, 
//которые целиком помещаются в строку длины K (при условии, что слова разделены хотя бы одним пробелом). 
//При этом, требуется каждую строку каждого столбца отформатировать следующим образом. Необходимо, чтобы среднеквадратическое отклонение 
//длин пробельных серий в каждой такой строке было минимальным (пробельная серия - непрерывная последовательность пробелов между двумя словами). 
//То есть, если в строке есть n пробельных серий длины li и среднее арифметическое этих длин равно L, то среднее арифметическое величин (li - L)^2 
//должно быть минимально для результирующей строки.
//Если в очередную строку очередного столбца входит больше одного слова, дополнять пробелами разрешается только промежутки между двумя словами. 
//При возможности добавить пробел в несколько промежутков, выбирать следует тот промежуток, который расположен ближе всего к началу строки. 
//Если же только одно очередное слово входной строки входит в очередную выходную строку столбца, то необходимо вывести сначала это слово, 
//а потом дополнить длину очередной строки столбца пробелами до K символов.
//Промежуток между двумя соседними столбцами одной страницы должен составлять 4 пробела, между двумя страницами - ровно две пустые строки, 
//выведенные с использованием символа перевода строки '\n'. Если в последней выходной странице столбцов меньше, чем C, то каждая строка, 
//содержащая эти столбцы, не должна содержать лишних символов, т.е. должна оканчиваться символом перевода строки, идущим после K символов последнего столбца.
//На стандартном потоке ввода в первой строке заданы числа K, C, S ( 1 ≤ K,C,S ≤ 100), во второй строке задана последовательность символов (строка) S, 
//состоящая из пробелов, букв латинского алфавита, цифр и знаков препинания, признак окончания которой - символ перевода строки. 
//Известно, что длина строки S ≤ 10^6. Строка состоит из слов, разделенных пробельными символами (по одному пробелу между двумя словами). 
//Строка начинается и кончается словами, либо является одним словом. В строке содержится по крайней мере одно слово. 
//Известно, что любое слово входной последоватьности имеет длину не больше K.
//На стандартный поток вывода напечатайте результат описанного выше преобразования.

#include "stdio.h"
#include "malloc.h"
#include "string.h"

char sep[] = " ";
char sep_c = ' ';

int count_gaps(char* str)
{
	int count = 0;

	for (int i = 0; str[i]; i++)
		if (str[i] == sep_c)
			count++;

	return count;
}
void add_gaps(char* str, int k)
{
	int len = strlen(str);
	int gaps_count = count_gaps(str);

	if (gaps_count == 0)
	{
		for (int i = strlen(str); i < k; i++)
			str[i] = sep_c;

		str[k] = 0;

		return;
	}

	int i = 0;
	int j = 0;

	int a = (k - len + gaps_count) % gaps_count;
	int b = (k - len + gaps_count) / gaps_count;

	char* str_out = (char*)malloc((k + 5) * sizeof(char));

	for (int c_g = 1; c_g <= a; i++, j++)
	{
		if (str[i] == sep_c)
		{
			c_g++;

			for (int k = 1; k <= b + 1; k++, j++)
				str_out[j] = sep_c;
			j--;
		}
		else
			str_out[j] = str[i];
	}

	for (; str[i]; i++, j++)
	{
		if (str[i] == sep_c)
		{
			for (int k = 1; k <= b; k++, j++)
				str_out[j] = sep_c;
			j--;
		}
		else
			str_out[j] = str[i];
	}

	str_out[j] = 0;

	strcpy(str, str_out);
	free(str_out);
}

struct column
{
	char** strings;
	int string_len;
	int strings_used;
	int strings_count;
	int can_add;
};

void column_init(struct column* col, int K, int S)
{
	col->string_len = K;
	col->strings_count = S;
	col->strings_used = 0;
	col->can_add = 1;

	col->strings = (char**)malloc(S * sizeof(char*));

	for (int i = 0; i < S; i++)
	{
		col->strings[i] = (char*)malloc((K + 10) * sizeof(char));
		col->strings[i][0] = 0;
	}
}
void column_destroy(struct column* col)
{
	for (int i = 0; i < col->strings_count; i++)
		free(col->strings[i]);

	free(col->strings);
}

int string_add(char* dst, char* src, int K)
{
	int rem_space = K - strlen(dst);

	if (dst[0] != 0)
		rem_space -= 1;

	int src_len = strlen(src);

	if (rem_space - src_len >= 0)
	{
		if (dst[0] != 0)
			strcat(dst, sep);

		strcat(dst, src);

		return 1;
	}

	return 0;
}
int column_add(struct column* col, char* str)
{
	if (!col->can_add)
		return 0;

	int add_posible = string_add(col->strings[col->strings_used], str, col->string_len);

	if (!add_posible)
	{
		col->strings_used++;

		if (col->strings_used >= col->strings_count)
		{
			col->can_add = 0;
			return 0;
		}

		string_add(col->strings[col->strings_used], str, col->string_len);

		return 1;
	}

	return 1;
}

struct page
{
	struct column* columns;
	int columns_used;
	int columns_count;
	int can_add;
};

void page_init(struct page* p, int C, int K, int S)
{
	p->columns_count = C;
	p->columns_used = 0;
	p->can_add = 1;

	p->columns = (struct column*)malloc(C * sizeof(struct column));

	for (int i = 0; i < C; i++)
		column_init(&p->columns[i], K, S);
}
void page_destroy(struct page* p)
{
	for (int i = 0; i < p->columns_count; i++)
		column_destroy(&p->columns[i]);

	free(p->columns);
}

int page_add(struct page* p, char* str)
{
	if (!p->can_add)
		return 0;

	int add_posible = column_add(&p->columns[p->columns_used], str);

	if (!add_posible)
	{
		p->columns_used++;

		if (p->columns_used >= p->columns_count)
		{
			p->can_add = 0;
			return 0;
		}

		column_add(&p->columns[p->columns_used], str);

		return 1;
	}

	return 1;
}
void page_print(struct page p)
{
	int C, S;
	C = p.columns_count;
	S = p.columns[0].strings_count;

	for (int i = 0; i < S; i++)
	{
		printf("%s", p.columns[0].strings[i]);

		for (int j = 1; j < C; j++)
			if (p.columns[j].strings[i][0])
				printf("    %s", p.columns[j].strings[i]);

		printf("\n");
	}
}

struct document
{
	struct page* pages;
	int pages_used;
	int pages_count;
};

void document_init(struct document* doc, int C, int K, int S, int len)
{
	doc->pages_count = ((len / C / K / S) + 2) * 2;
	doc->pages_used = 0;

	doc->pages = (struct page*)malloc(doc->pages_count * sizeof(struct page));

	for (int i = 0; i < doc->pages_count; i++)
		page_init(&doc->pages[i], C, K, S);
}
void document_destroy(struct document* doc)
{
	for (int i = 0; i < doc->pages_count; i++)
		page_destroy(&doc->pages[i]);

	free(doc->pages);
}

void document_add(struct document* doc, char* str)
{
	int add_posible = page_add(&doc->pages[doc->pages_used], str);

	if (!add_posible)
	{
		doc->pages_used++;

		page_add(&doc->pages[doc->pages_used], str);
	}
}
void document_add_gaps(struct document* doc)
{
	for (int i = 0; i <= doc->pages_used; i++)
		for (int j = 0; j < doc->pages[0].columns_count; j++)
			for (int k = 0; k < doc->pages[0].columns[0].strings_count; k++)
				if (doc->pages[i].columns[j].strings[k][0])
					add_gaps(doc->pages[i].columns[j].strings[k], doc->pages[0].columns[0].string_len);
}
void document_print(struct document doc)
{
	page_print(doc.pages[0]);

	for (int i = 1; i <= doc.pages_used; i++)
	{
		printf("\n\n");

		page_print(doc.pages[i]);
	}
}

int get_str(char* str_in, char* str_out, int* i)
{
	for (; str_in[*i] == ' '; (*i)++);

	if (str_in[*i] == 0)
		return 0;

	int j = 0;

	for (; str_in[*i] != ' ' && str_in[*i]; (*i)++, j++)
		str_out[j] = str_in[*i];

	str_out[j] = 0;

	return 1;
}

char str[1000005];
char next_str[105];

int main(void)
{
	int K, C, S;

	scanf("%d%d%d", &K, &C, &S);

	fgets(str, 1000005, stdin);
	fgets(str, 1000005, stdin);

	str[strlen(str) - 1] = 0;

	struct document doc;

	int c_g = strlen(str);
	document_init(&doc, C, K, S, c_g);

	int i = 0;

	while (get_str(str, next_str, &i))
		document_add(&doc, next_str);

	document_add_gaps(&doc);

	document_print(doc);

	document_destroy(&doc);

	return 0;
}

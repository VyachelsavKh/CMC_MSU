//Задача 04-6: Форматирование
//Дана строка текста, состоящая из слов, отделенных пробелами. Требуется отформатировать строку следующим образом. 
//Необходимо увеличить длину строки до K символов, дополнив ее пробелами между словами. 
//При этом требуется, чтобы среднеквадратическое отклонение длин пробельных серий в результирующей строке было минимальным 
//(пробельная серия - непрерывная последовательность пробелов между двумя словами). 
//То есть, если в строке есть n пробельных серий длины li и среднее арифметическое этих длин равно L, то среднее арифметическое величин (li - L)^2 
//должно быть минимально для результирующей строки. Дополнять пробелами разрешается только промежутки между двумя словами. 
//При возможности добавить пробел в несколько промежутков, выбирать следует тот промежуток, который расположен ближе всего к началу строки.
//На стандартном потоке ввода в первой строке задано число K (K ≥ 3, K ≤ 10^6), во второй строке задана последовательность символов (строка) 
//S, состоящая из пробелов и букв латинского алфавита, признак окончания которой - символ перевода строки. Известно, что длина строки S ≤ K. 
//Строка состоит из слов, разделенных пробельными символами (по одному пробелу между двумя словами). Строка начинается и кончается словами. 
//В строке содержится по крайней мере два слова.
//На стандартный поток вывода напечатайте отформатированную строку.

#include "stdio.h"
#include "stdlib.h"
#include "malloc.h"
#include "string.h"

int count_gaps(char* str)
{
	int count = 0;

	for (int i = 0; str[i]; i++)
		if (str[i] == ' ')
			count++;

	return count;
}

void add_gaps(char* str, int k)
{
	int len = strlen(str);
	int gaps_count = count_gaps(str);

	int i = 0;
	int j = 0;

	int a = (k - len + gaps_count) % gaps_count;
	int b = (k - len + gaps_count) / gaps_count;

	char* str_out = (char*)malloc((k + 5) * sizeof(char));

	for (int c_g = 1; c_g <= a; i++, j++)
	{
		if (str[i] == ' ')
		{
			c_g++;

			for (int k = 1; k <= b + 1; k++, j++)
				str_out[j] = ' ';
			j--;
		}
		else
			str_out[j] = str[i];
	}

	for (; str[i]; i++, j++)
	{
		if (str[i] == ' ')
		{
			for (int k = 1; k <= b; k++, j++)
				str_out[j] = ' ';
			j--;
		}
		else
			str_out[j] = str[i];
	}

	str_out[j] = 0;

	strcpy(str, str_out);
	free(str_out);
}

char str1[10];

char str2[1000005];
char str_out[1000005];

int main(void)
{
	int k;

	fgets(str1, 10, stdin);
	str1[strlen(str1) - 1] = 0;

	k = atoi(str1);

	fgets(str2, 1000005, stdin);
	str2[strlen(str2) - 1] = 0;

	add_gaps(str2, k);

	printf("%s", str2);

	return 0;
}
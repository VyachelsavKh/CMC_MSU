//Задача 04-10: Большие префиксы и суффиксы
//На стандартном потоке ввода задаются две символьные строки, разделённые символом перевода строки. 
//Каждая из строк не превышает по длине 106. В строках не встречаются пробельные символы.
//На стандартный поток вывода напечатайте два числа, разделённых пробелом: первое число — длина наибольшего префикса первой строки, 
//являющегося суффиксом второй; второе число — наоборот, длина наибольшего суффикса первой строки, являющегося префиксом второй. 
//Сравнение символов проводите с учётом регистра (т.е. символы 'a' и 'A' различны).

#include "stdio.h"
#include "string.h"

void pref_func(char* str, int* pi)
{
	int i = 1;
	int j = 0;
	pi[0] = 0;

	while (str[i])
	{
		if (str[i] == str[j])
		{
			pi[i] = j + 1;
			i++;
			j++;
		}
		else if (j == 0)
		{
			pi[i] = 0;
			i++;
		}
		else
			j = pi[j - 1];
	}
}

char str1[1000005];
char str2[1000005];
char str_new[2000005];

int pi[2000005];

int main(void)
{
	scanf("%s%s", str1, str2);

	char sep[] = "\n";

	str_new[0] = 0;

	strcat(str_new, str1);
	strcat(str_new, sep);
	strcat(str_new, str2);

	pref_func(str_new, pi);

	int ans1 = pi[strlen(str_new) - 1];

	str_new[0] = 0;

	strcat(str_new, str2);
	strcat(str_new, sep);
	strcat(str_new, str1);

	pref_func(str_new, pi);

	int ans2 = pi[strlen(str_new) - 1];

	printf("%d %d", ans1, ans2);

	return 0;
}

//Задача 06-9: Тайна пирамид
//Египетские археологи обнаружили в одной из гробниц носитель информации, предположительно, инопланетного происхождения. 
//Изучение находящихся на нем файлов может пролить свет на историю Древнего Египта. 
//Требуется прочитать последовательность 32-битных целых знаковых чисел, хранящихся в бинарном файле input.bin в формате little endian, 
//и вывести в бинарный файл output.bin в таком же формате ответ на вопрос, является ли эта последовательность пирамидой, и если да, 
//то неубывающей или невозрастающей. В случае неубывающей пирамиды нужно вывести 1, в случае невозрастающей (не являющейся при этом неубывающей) - -1, 
//а если последовательность чисел не является пирамидой - 0.
//Размер файла input.bin не превышает 4 МБ. Размер int - 32 бита. Программу должна корректно работать на машине, 
//основанной на архитектуре x86. Использование fseek запрещено.

#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "malloc.h"

union little_endian
{
	int n;
	char bytes[4];
};

int check_heap(union little_endian* mas, int count, int* type, int pos)
{
	if (pos * 2 > count)
		return 1;

	if (*type == 0)
	{
		if (pos * 2 + 1 > count)
		{
			if (mas[pos].n > mas[pos * 2].n)
			{
				*type = -1;
				return 1;
			}
			else if (mas[pos].n < mas[pos * 2].n)
			{
				*type = 1;
				return 1;
			}
			else
				return check_heap(mas, count, type, pos * 2) && check_heap(mas, count, type, pos * 2 + 1);
		}
		else
		{
			if (mas[pos].n > mas[pos * 2].n || mas[pos].n > mas[pos * 2 + 1].n)
			{
				*type = -1;
				return check_heap(mas, count, type, pos);
			}
			else if (mas[pos].n < mas[pos * 2].n || mas[pos].n < mas[pos * 2 + 1].n)
			{
				*type = 1;
				return check_heap(mas, count, type, pos);
			}
			else
				return check_heap(mas, count, type, pos * 2) && check_heap(mas, count, type, pos * 2 + 1);
		}
	}
	else if (*type == 1)
	{
		if (pos * 2 + 1 > count)
		{
			if (mas[pos].n <= mas[pos * 2].n)
				return 1;

			return 0;
		}
		else
		{
			if (mas[pos].n <= mas[pos * 2].n && mas[pos].n <= mas[pos * 2 + 1].n)
				return check_heap(mas, count, type, pos * 2) && check_heap(mas, count, type, pos * 2 + 1);

			return 0;
		}
	}
	else if (*type == -1)
	{
		if (pos * 2 + 1 > count)
		{
			if (mas[pos].n >= mas[pos * 2].n)
				return 1;

			return 0;
		}
		else
		{
			if (mas[pos].n >= mas[pos * 2].n && mas[pos].n >= mas[pos * 2 + 1].n)
				return check_heap(mas, count, type, pos * 2) && check_heap(mas, count, type, pos * 2 + 1);

			return 0;
		}
	}

	return 0;
}

int main(void)
{
	FILE* fin = fopen("input.bin", "r");
	FILE* fout = fopen("output.bin", "w");

	union little_endian* inp_mas = (union little_endian*)malloc(2000000 * sizeof(union little_endian));
	int count = 1;

	while (fscanf(fin, "%c", &inp_mas[count].bytes[0]) != EOF)
	{
		for (int i = 1; i < 4; i++)
			fscanf(fin, "%c", &inp_mas[count].bytes[i]);
		count++;
	}
	count--;

	int type = 0;

	int ans = check_heap(inp_mas, count, &type, 1);

	union little_endian out;
	out.n = 0;

	if (ans)
	{
		if (type == -1)
			out.n = -1;
		else
			out.n = 1;
	}

	for (int i = 0; i < 4; i++)
		fprintf(fout, "%c", out.bytes[i]);

	free(inp_mas);

	fclose(fin);
	fclose(fout);

	return 0;
}

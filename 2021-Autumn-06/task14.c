//Задача 06-14: Наизнанку
//На вход подаётся бинарный файл в следующем формате: первые два байта являются целым числом, которое не превышает 2000 
//и задаёт размер квадратной матрицы, затем следуют целочисленные 32х битные элементы матрицы. 
//Все числа находятся в представлении big-endian. Требуется отыскать след матрицы и вывести его в бинарный файл 
//в виде 64х битного целого числа в формате big-endian.

#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "malloc.h"

union format
{
	long long n_ll;
	unsigned char bytes[8];
};

int main(void)
{
	FILE* fin = fopen("matrix.in", "rb");
	FILE* fout = fopen("trace.out", "wb");

	int n = fgetc(fin) * 256;
	n += fgetc(fin);

	long long trace = 0;

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (i == j)
			{
				int elem = fgetc(fin);
				elem *= 256;
				elem += fgetc(fin);
				elem *= 256;
				elem += fgetc(fin);
				elem *= 256;
				elem += fgetc(fin);

				trace += elem;
			}
			else
			{
				fgetc(fin);
				fgetc(fin);
				fgetc(fin);
				fgetc(fin);
			}
		}
	}

	union format f;
	f.n_ll = trace;

	for (int i = 7; i >= 0; i--)
		fputc(f.bytes[i], fout);

	fclose(fin);
	fclose(fout);

	return 0;
}

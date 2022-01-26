//Задача 03-11: Сложение дробей
//Вводится целое число N (2 ≤ N ≤ 5), и следом N пар целых чисел A1,B1,...,AN,BN (0 ≤ Ai < Bi ≤ 50)
//Требуется найти сумму чисел A1/B1 + ... + AN/BN. Сумму необходимо вывести в видел трех неотрицательных целых чисел X, Y, Z, 
//таких что требуемая сумма равняется X+Y/Z, причем Y/Z - правильная несократимая дробь.
//Указание: использование массивов запрещено.

#include "stdio.h"

struct fraction
{
	int numerator;
	int denominator;
};

void init(struct fraction* n, int a, int b)
{
	n->numerator = a;
	n->denominator = b;
}

void read(struct fraction* a)
{
	scanf("%d%d", &a->numerator, &a->denominator);
}

int nod(int a, int b)
{
	if (b == 0)
		return a;

	return nod(b, a % b);
}

void reduce(struct fraction* a)
{
	int NOD = nod(a->numerator, a->denominator);
	a->numerator /= NOD;
	a->denominator /= NOD;
}

void sum(struct fraction* a, struct fraction b)
{
	int NOD = nod(a->denominator, b.denominator);

	a->numerator = b.denominator / NOD * a->numerator + a->denominator / NOD * b.numerator;
	a->denominator = a->denominator / NOD * b.denominator;

	reduce(a);
}

int main(void)
{
	int n;
	scanf("%d", &n);

	struct fraction ans;

	init(&ans, 0, 1);

	struct fraction cur;

	for (int i = 0; i < n; i++)
	{
		read(&cur);

		sum(&ans, cur);
	}

	printf("%d %d %d", ans.numerator / ans.denominator, ans.numerator % ans.denominator, ans.denominator);

	return 0;
}

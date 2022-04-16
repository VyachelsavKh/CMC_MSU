//Задача 06-15: Domain Name System
//Представьте, что вы пишете DNS сервер. У вас есть соответствие доменных имен компьютеров их IP-адресам. 
//Вам необходимо эффективно обрабатывать запросы на получение IP-адреса компьютера по его имени.
//Во входном файле input.txt записано число N (1 ≤ N ≤ 100000) - количество известных соответствий между именем компьютера и его адресом, 
//за которым следует N записей вида ⟨имя компьютера⟩ ⟨IP-адрес компьютера⟩ - сами эти соответствия. Далее идет число M (1 ≤ M ≤ 100000) - количество запросов. 
//Каждый запрос представляет собой одну строку с именем компьютера.
//Имена компьютеров - строки, состоящие из маленьких латинских букв, символов "." и "-". Длины имен не превышают 100 символов. 
//IP-адреса - 32-битные беззнаковые целые числа. Не бывает двух компьютеров с одинаковым именем. 
//У каждого компьютера может быть только один адрес, но может быть несколько различных имен.
//В выходной файл output.txt требуется вывести результаты обработки всех запросов в том порядке, в котором запросы встречаются во входном файле. 
//Результатом обработки запроса является одно беззнаковое 32-битное число - IP-адрес запрашиваемого компьютера, если он известен, либо -1, 
//если IP-адрес данного компьютера неизвестен.

#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "malloc.h"

unsigned int table_size = 1000000;

unsigned int str_hash(char* str)
{	
	unsigned int hash = 7;

	for (int i = 0; str[i]; i++)
	{
		hash = (hash * 31 + str[i]) % table_size;
	}

	return hash;
}

struct list_node
{
	char* name;
	long long ip;
	struct list_node* next;
};

struct list_node* push_front(struct list_node* l, char* name, long long ip)
{
	struct list_node* tmp = (struct list_node*)malloc(sizeof(struct list_node));

	tmp->name = (char*)malloc(105 * sizeof(char));
	strcpy(tmp->name, name);
	tmp->ip = ip;
	tmp->next = l;

	return tmp;
}

struct list_node* destroy(struct list_node* l)
{
	if (l == NULL)
		return NULL;

	struct list_node* next;

	while (l)
	{
		next = l->next;
		free(l->name);
		free(l);
		l = next;
	}

	return NULL;
}

long long find(struct list_node* l, char* name)
{
	while (l != NULL)
	{
		if (strcmp(l->name, name) == 0)
			return l->ip;
		l = l->next;
	}

	return -1;
}

int main(void)
{
	FILE* fin = fopen("input.txt", "r");
	FILE* fout = fopen("output.txt", "w");

	struct list_node** h_map = (struct list_node**)malloc(table_size * sizeof(struct list_node*));
	for (int i = 0; i < table_size; i++)
		h_map[i] = NULL;

	char name[105];
	long long ip;

	int n;
	fscanf(fin, "%d", &n);

	for (int i = 0; i < n; i++)
	{
		fscanf(fin, "%s%lld", name, &ip);

		unsigned int hash = str_hash(name);

		h_map[hash] = push_front(h_map[hash], name, ip);
	}

	int m;
	fscanf(fin, "%d", &m);

	for (int i = 0; i < m; i++)
	{
		fscanf(fin, "%s", name);

		unsigned int hash = str_hash(name);

		fprintf(fout, "%lld\n", find(h_map[hash], name));
	}

	for (int i = 0; i < table_size; i++)
		h_map[i] = destroy(h_map[i]);
	free(h_map);

	fclose(fin);
	fclose(fout);

	return 0;
}

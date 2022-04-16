//Задача 06-16: Сортировка большого списка
//Во входном файле input.txt записана последовательность чисел. Числа в последовтельности целые, по модулю не превосходящие 109. Их количество не превышает 105.
//Требуется отсортировать данную последовательность по неубыванию и вывести результат в файл output.txt.
//Указание: при решении данной задачи запрещается использовать массивы. Для хранения последовательности используйте однонаправленный или двунаправленный список.

#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "malloc.h"

#ifndef l2_listh
#define l2_listh

#include "stdio.h"
#include "malloc.h"

struct list_2_node
{
	int data;
	struct list_2_node* next;
	struct list_2_node* prev;
};

struct list_2
{
	struct list_2_node* head;
	struct list_2_node* tail;
	int size;
};

//======All functions======

void list_2_init(struct list_2*);
void list_2_destroy(struct list_2*);

struct list_2_node* list_2_get_list_2_node_Dont_use_it(const struct list_2*, int);
void list_2_merge_sort_Dont_use_it(struct list_2*, int, int, struct list_2*, struct list_2_node*, struct list_2_node*, int (*)(int, int));

int list_2_front(const struct list_2*);
int list_2_back(const struct list_2*);

int list_2_size(const struct list_2*);
int list_2_empty(const struct list_2*);

void list_2_clear(struct list_2*);
void list_2_resize(struct list_2*, int, int);
void list_2_insert(struct list_2*, int, int);
void list_2_erase(struct list_2*, int);
void list_2_push_back(struct list_2*, int);
void list_2_pop_back(struct list_2*);
void list_2_push_front(struct list_2*, int);
void list_2_pop_front(struct list_2*);
void list_2_swap_elements(struct list_2*, int, int);
void list_2_swap(struct list_2*, struct list_2*);
void list_2_merge_sort(struct list_2*, int (*)(int, int));

void list_2_printf(const struct list_2* l, FILE*);
void list_2_printf_reverse(const struct list_2* l, FILE*);

//======Member functions======

void list_2_init(struct list_2* l)
{
	l->head = NULL;
	l->tail = NULL;
	l->size = 0;
}
void list_2_destroy(struct list_2* l)
{
	struct list_2_node* prev;
	struct list_2_node* next = l->head;

	while (next != NULL)
	{
		prev = next;
		next = next->next;
		free(prev);
	}

	l->head = NULL;
	l->tail = NULL;
	l->size = 0;
}

//======Private functions======

struct list_2_node* list_2_get_list_2_node_Dont_use_it(const struct list_2* l, int pos)
{
	struct list_2_node* cur_list_2_node;
	int cur_pos;

	if (pos <= l->size / 2)
	{
		cur_list_2_node = l->head;
		cur_pos = 0;

		while (cur_pos < pos)
		{
			cur_list_2_node = cur_list_2_node->next;
			cur_pos++;
		}
	}
	else
	{
		cur_list_2_node = l->tail;
		cur_pos = l->size - 1;

		while (cur_pos > pos)
		{
			cur_list_2_node = cur_list_2_node->prev;
			cur_pos--;
		}
	}

	return cur_list_2_node;
}
void list_2_merge_sort_Dont_use_it(struct list_2* l, int left, int right, struct list_2* buffer, struct list_2_node* l_node, struct list_2_node* r_node, int (*cmp)(int, int))
{
	if (left == right)
		return;

	int mid = (left + right) / 2;

	struct list_2_node* mid_node = l_node;
	int cur_pos = left;

	while (cur_pos != mid)
	{
		mid_node = mid_node->next;
		cur_pos++;
	}

	list_2_merge_sort_Dont_use_it(l, left, mid, buffer, l_node, mid_node, cmp);
	list_2_merge_sort_Dont_use_it(l, mid + 1, right, buffer, mid_node->next, r_node, cmp);

	struct list_2_node* i_node = l_node;
	struct list_2_node* j_node = mid_node->next;
	struct list_2_node* step_node = buffer->head;

	int i = left;
	int j = mid + 1;

	while (i <= mid && j <= right)
	{
		if (cmp(i_node->data, j_node->data) < 0)
		{
			step_node->data = i_node->data;
			step_node = step_node->next;
			i_node = i_node->next;
			i++;
		}
		else
		{
			step_node->data = j_node->data;
			step_node = step_node->next;
			j_node = j_node->next;
			j++;
		}
	}

	while (i <= mid)
	{
		step_node->data = i_node->data;
		step_node = step_node->next;
		i_node = i_node->next;
		i++;
	}

	while (j <= right)
	{
		step_node->data = j_node->data;
		step_node = step_node->next;
		j_node = j_node->next;
		j++;
	}

	struct list_2_node* cur_node = l_node;
	step_node = buffer->head;

	for (int k = 0; k < right - left + 1; k++)
	{
		cur_node->data = step_node->data;
		step_node = step_node->next;
		cur_node = cur_node->next;
	}
}

//======Element access======

int list_2_front(const struct list_2* l)
{
	return l->head->data;
}
int list_2_back(const struct list_2* l)
{
	return l->tail->data;
}
int* list_2_get_element(const struct list_2* l, int pos)
{
	return &list_2_get_list_2_node_Dont_use_it(l, pos)->data;
}

//======Capacity======

int list_2_size(const struct list_2* l)
{
	return l->size;
}
int list_2_empty(const struct list_2* l)
{
	return l->size == 0;
}

//======Modifiers======

void list_2_clear(struct list_2* l)
{
	list_2_destroy(l);
}
void list_2_resize(struct list_2* l, int new_size, int new_value)
{
	if (new_size == l->size)
		return;

	if (new_size > l->size)
	{
		for (int i = l->size; i < new_size; i++)
			list_2_push_back(l, new_value);
	}

	if (new_size < l->size)
	{
		for (int i = new_size; i < l->size; i--)
			list_2_pop_back(l);
	}
}
void list_2_insert(struct list_2* l, int pos, int value)
{
	if (pos == 0)
	{
		list_2_push_front(l, value);
		return;
	}
	if (pos == l->size)
	{
		list_2_push_back(l, value);
		return;
	}

	struct list_2_node* right = list_2_get_list_2_node_Dont_use_it(l, pos);
	struct list_2_node* left = right->prev;

	struct list_2_node* new_list_2_node = (struct list_2_node*)malloc(sizeof(struct list_2_node));

	new_list_2_node->data = value;
	new_list_2_node->next = right;
	new_list_2_node->prev = left;

	left->next = new_list_2_node;
	right->prev = new_list_2_node;

	l->size++;
}
void list_2_erase(struct list_2* l, int pos)
{
	if (pos == 0)
	{
		list_2_pop_front(l);
		return;
	}
	if (pos == l->size - 1)
	{
		list_2_pop_back(l);
		return;
	}

	struct list_2_node* cur_list_2_node = list_2_get_list_2_node_Dont_use_it(l, pos);

	struct list_2_node* del_list_2_node = cur_list_2_node;

	cur_list_2_node->prev->next = cur_list_2_node->next;
	cur_list_2_node->next->prev = cur_list_2_node->prev;

	free(del_list_2_node);

	l->size--;
}
void list_2_push_back(struct list_2* l, int value)
{
	struct list_2_node* new_list_2_node = (struct list_2_node*)malloc(sizeof(struct list_2_node));

	new_list_2_node->data = value;
	new_list_2_node->prev = l->tail;
	new_list_2_node->next = NULL;

	if (l->size == 0)
	{
		l->head = new_list_2_node;
		l->tail = new_list_2_node;
		l->size = 1;
		return;
	}

	l->tail->next = new_list_2_node;
	l->tail = new_list_2_node;
	l->size++;
}
void list_2_pop_back(struct list_2* l)
{
	if (l->size == 0)
		return;

	if (l->size == 1)
	{
		free(l->head);

		l->head = NULL;
		l->tail = NULL;
		l->size = 0;
	}

	struct list_2_node* back = l->tail;

	l->tail->prev->next = NULL;
	l->tail = l->tail->prev;
	l->size--;

	free(back);
}
void list_2_push_front(struct list_2* l, int value)
{
	struct list_2_node* new_list_2_node = (struct list_2_node*)malloc(sizeof(struct list_2_node));

	new_list_2_node->data = value;
	new_list_2_node->prev = NULL;
	new_list_2_node->next = l->head;

	if (l->size == 0)
	{
		l->head = new_list_2_node;
		l->tail = new_list_2_node;
		l->size = 1;
		return;
	}

	l->head->prev = new_list_2_node;
	l->head = new_list_2_node;
	l->size++;
}
void list_2_pop_front(struct list_2* l)
{
	if (l->size == 0)
		return;

	if (l->size == 1)
	{
		free(l->head);

		l->head = NULL;
		l->tail = NULL;
		l->size = 0;
	}

	struct list_2_node* front = l->head;

	l->head->next->prev = NULL;
	l->head = l->head->next;
	l->size--;

	free(front);
}
void list_2_swap_elements(struct list_2* l, int pos1, int pos2)
{
	struct list_2_node* list_2_node1 = list_2_get_list_2_node_Dont_use_it(l, pos1);
	struct list_2_node* list_2_node2 = list_2_get_list_2_node_Dont_use_it(l, pos2);

	int tmp = list_2_node1->data;
	list_2_node1->data = list_2_node2->data;
	list_2_node2->data = tmp;
}
void list_2_swap(struct list_2* a, struct list_2* b)
{
	struct list_2_node* list_2_node_tmp;

	list_2_node_tmp = a->head;
	a->head = b->head;
	b->head = list_2_node_tmp;

	list_2_node_tmp = a->tail;
	a->tail = b->tail;
	b->tail = list_2_node_tmp;

	int size_tmp = a->size;
	a->size = b->size;
	b->size = size_tmp;
}
void list_2_merge_sort(struct list_2* l, int (*cmp)(int, int))
{
	struct list_2 buffer;
	list_2_init(&buffer);
	list_2_resize(&buffer, l->size, 0);

	list_2_merge_sort_Dont_use_it(l, 0, l->size - 1, &buffer, l->head, l->tail, cmp);

	list_2_destroy(&buffer);
}

//======Printf functions======

void list_2_printf(const struct list_2* l, FILE* fout)
{
	if (l->size == 0)
		return;

	struct list_2_node* next = l->head;
	while (next != l->tail)
	{
		fprintf(fout, "%d ", next->data);
		next = next->next;
	}
	fprintf(fout, "%d", next->data);
}
void list_2_printf_reverse(const struct list_2* l, FILE* fout)
{
	if (l->size == 0)
		return;

	struct list_2_node* prev = l->tail;
	while (prev != l->head)
	{
		fprintf(fout, "%d ", prev->data);
		prev = prev->prev;
	}
	fprintf(fout, "%d", prev->data);
}
#endif

int cmp(int a, int b)
{
	if (a < b) return -1;
	if (a > b) return 1;
	return 0;
}

int main(void)
{
	FILE* fin = fopen("input.txt", "r");
	FILE* fout = fopen("output.txt", "w");

	struct list_2 l;
	list_2_init(&l);

	int n;

	while (fscanf(fin, "%d", &n) != EOF)
		list_2_push_back(&l, n);

	list_2_merge_sort(&l, cmp);

	list_2_printf(&l, fout);

	fclose(fin);
	fclose(fout);

	return 0;
}

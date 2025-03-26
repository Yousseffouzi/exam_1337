#ifndef LIST_H
# define LIST_H

#include <stdlib.h>
#include <stdio.h>

typedef struct s_list t_list;

struct s_list
{
	int     data;
	t_list  *next;
};

void print_list(t_list *lst);
t_list *new_node(int data);
int ascending(int a, int b);
t_list		*sort_list(t_list* lst, int (*cmp)(int, int));

#endif
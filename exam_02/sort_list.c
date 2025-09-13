#include "list.h"

t_list		*sort_list(t_list* lst, int (*cmp)(int, int))
{
    t_list *tmp;
    int tmprary;
    int sorted;

    if(!lst)
        return(NULL);
    sorted = 0;
    while(!sorted)
    {    
        tmp = lst;
        sorted = 1;
        while (tmp->next)
        {
            if ((*cmp)(tmp->data , tmp->next->data) == 0)
            {
                tmprary = tmp->data;
                tmp->data = tmp->next->data;
                tmp->next->data = tmprary;
                sorted = 0;
            }
            tmp= tmp->next;
        }
    }
    return (lst);
}

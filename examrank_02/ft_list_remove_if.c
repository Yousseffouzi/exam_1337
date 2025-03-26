#include <stdlib.h>
#include "ft_list.h"

void ft_list_remove_if(t_list **begin_list, void *data_ref, int (*cmp)(void *, void *))
{
    t_list *current;
    t_list *previous;

    // Start from the head of the list
    current = *begin_list;
    previous = NULL;

    // Loop through the list
    while (current)
    {
        // Compare current node's data with data_ref
        if ((*cmp)(current->data, data_ref) == 0)
        {
            // If we are removing the first node (head node)
            if (previous == NULL)
            {
                *begin_list = current->next;  // Update head
            }
            else
            {
                previous->next = current->next;  // Skip over current node
            }

            // Free the current node's memory
            free(current);

            // Move to the next node
            current = previous ? previous->next : *begin_list;
        }
        else
        {
            // If not equal, just move to the next node
            previous = current;
            current = current->next;
        }
    }
}

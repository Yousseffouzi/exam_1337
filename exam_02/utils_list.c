#include "list.h"  // Assuming the strcct t_list and the sort_list function are in this file

// Sample comparison function for ascending order
int ascending(int a, int b)
{
    return (a <= b);  // Will return 0 if a > b, meaning out of order
}

// Function to create a new node
t_list *new_node(int data)
{
    t_list *node = malloc(sizeof(t_list));
    node->data = data;
    node->next = NULL;
    return node;
}

// Function to print the list
void print_list(t_list *lst)
{
    while (lst)
    {
        printf("%d -> ", lst->data);
        lst = lst->next;
    }
    printf("NULL\n");
}

int main()
{
    // Create a simple linked list: 3 -> 1 -> 4 -> 2
    t_list *head = new_node(3);
    head->next = new_node(1);
    head->next->next = new_node(4);
    head->next->next->next = new_node(2);

    // Print the unsorted list
    printf("Unsorted list:\n");
    print_list(head);

    // Sort the list
    head = sort_list(head, ascending);

    // Print the sorted list
    printf("\nSorted list:\n");
    print_list(head);

    // Free the allocated memory (important in a real program)
    t_list *tmp;
    while (head)
    {
        tmp = head;
        head = head->next;
        free(tmp);
    }

    return 0;
}

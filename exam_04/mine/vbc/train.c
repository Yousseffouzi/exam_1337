#include <stdio.h>
#include <stdlib.h> // change this to <stdlib.h>
#include <ctype.h>

typedef struct node {
    enum {
        ADD,
        MULTI,
        VAL
    }   type;
    int val;
    struct node *l;
    struct node *r;
}   node;

node    *new_node(node n)
{
    node *ret = calloc(1, sizeof(node));
    if (!ret)
        return (NULL);
    *ret = n;
    return (ret);
}

void    destroy_tree(node *n)
{
    if (!n)
        return ;
    if (n->type != VAL)
    {
        destroy_tree(n->l);
        destroy_tree(n->r);
    }
    free(n);
}

void    unexpected(char c)
{
    if (c)
        printf("Unexpected token '%c'\n", c);
    else
        printf("Unexpected end of file\n");
}

int accept(char **s, char c)
{
    if (**s == c)
    {
        (*s)++;
        return (1);
    }
    return (0);
}
node *multip(char **s);
node    *par_num(char **s);

node *addition(char **s)
{
    node *l = multip(s);
    if(!l)
        return (NULL);
    while (accept(s, '+'))
    {
        node *r = multip(s);
        if(!r)
        {
            destroy_tree(l);
            return (NULL);
        }
        node n = {ADD, 0, l, r};
        l = new_node(n);
    }
    return (l);
}

node *multip(char **s)
{
    node *l = par_num(s);
    if(!l)
        return (NULL);
    while (accept(s, '*'))
    {
        node *r = par_num(s);
        if(!r)
        {
            destroy_tree(l);
            return (NULL);
        }
        node n = {MULTI, 0, l, r};
        l = new_node(n);
    }
    return (l);
}

node    *par_num(char **s)
{
    if(accept(s, '('))
    {
        node *n = addition(s);
        if(!accept(s,')'))
        {
            unexpected(**s);
            destroy_tree(n);
            return NULL;
        }
        return n;
    }
    else if(isdigit(**s))
    {
        node n = {VAL, **s - '0', NULL, NULL};
        (*s)++;
        return (new_node(n));
    }
    unexpected(**s);
    return NULL;
}


int eval_tree(node *tree)
{
    switch (tree->type)
    {
        case ADD:
            return (eval_tree(tree->l) + eval_tree(tree->r));
        case MULTI:
            return (eval_tree(tree->l) * eval_tree(tree->r));
        case VAL:
            return (tree->val);
    }
}

int main(int ac, char **av)
{
    if (ac != 2)
        return (1);
    node *tree = addition(&av[1]);
    if (!tree)
        return (1);
    if(av[1][0])
    {
        unexpected(av[1][0]);
        destroy_tree(tree);
        return 1;
    }
    printf("%d\n", eval_tree(tree));
    destroy_tree(tree);
    return (0);
}

#include "vbc.h"

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
        destroy_tree(n->left);
        destroy_tree(n->right);
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

node    *addition(char **s)
{
    node    *left = multip(s);
    if (!left)
        return NULL;
    while (accept(s,'+'))
    {
        node *right = multip(s);
        if(!right)
        {
            destroy_tree(left);
            return NULL;
        }
        node n = {ADD, 0 , left, right};
        left = new_node(n);
    }
    return (left);
    
}

node    *multip(char **s)
{
    node *left = par_mun(s);
    if(!left)
        return NULL;
    while (accept(s, '*'))
    {
        node *right = par_mun(s);
        if(!right)
        {
            destroy_tree(left);
            return NULL;
        }
    node    n = {MULTI, 0 , left, right};
    left = new_node(n);
    }
    return left;
}

node    *par_mun(char **s)
{
    if (accept(s, '('))
    {
        node    *n = addition(s);
        if(!accept(s, ')'))
        {
            unexpected(**s);
            destroy_tree(n);
            return NULL;
        }
        return n;
    }
    if (isdigit(**s))
    {
       node n = {VAL, **s - '0', NULL, NULL};
       (*s)++;
       return (new_node(n));
    }
    unexpected(**s);
    return (NULL);
}

int eval_tree(node *tree)
{
    switch (tree->type)
    {
        case ADD:
            return (eval_tree(tree->left) + eval_tree(tree->right));
        case MULTI:
            return (eval_tree(tree->left) * eval_tree(tree->right));
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

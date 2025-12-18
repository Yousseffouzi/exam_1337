#ifndef VBC_H
#define VBC_H

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct node {
    enum {
        ADD,
        MULTI,
        VAL
    }   type;
    int val;
    struct node *left;
    struct node *right;
}   node;

node    *addition(char **s);
node    *multip(char **s);
node    *par_mun(char **s);

#endif
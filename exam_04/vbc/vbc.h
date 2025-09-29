/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vbc.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yofouzi <yofouzi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 10:04:08 by yofouzi           #+#    #+#             */
/*   Updated: 2025/09/29 10:04:09 by yofouzi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VBC_H
#define VBC_H

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

typedef struct node {
    enum {ADD, MULTI, VAL} type;
    int val;
    struct node *left;
    struct node *right;
} node;

node *parse_addition(char **s);

#endif
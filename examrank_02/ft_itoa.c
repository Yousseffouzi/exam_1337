#include <stdlib.h>

char *ft_itoa(int nbr)
{
    int  len;
    char *str;
    long n;
    long n_tmp;

    if(nbr == 0)
    {
        if(!(str = malloc(2)))
            return(NULL);
        str[0] = '0';
        str[1] = '\0';
        return (str);
    }
    len = 0;
    n = nbr;
    n_tmp = n;
    while(n_tmp)
    {
        n_tmp /= 10;
        len++;
    }
    if (n < 0)
    {
        len++;
        n = -n;
    }
    if(!(str = (char *)malloc(sizeof(char) * (len + 1))))
        return (NULL);
    str[len] = '\0';
    while(n)
    {
        str[--len] = (n % 10) + '0';
        n /= 10;
    }
    if(nbr < 0)
    {
        str[0] = '-';
    }
    return (str);
}

#include <stdio.h>


int main()
{
    printf("%s",ft_itoa(809099));
    printf("\n");
}


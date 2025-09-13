void    sort_int_tab(int *tab, unsigned int size)
{
    unsigned int i;
    unsigned int j;
    int tmp;

    i = 0;
    while(i < size - 1)
    {
        j = 0;
        while(j < size - 1 - i)
        {
            if (tab[j] > tab[j + 1])
            {
                tmp = tab[j];
                tab[j] = tab[j + 1];
                tab[j + 1] = tmp;
            }
            j++;
        }
        i++;
    }

}

#include <stdio.h>

int main()
{
    int tab[]  = {4, 7, 8, 3, 6};
    int i;
    int size = 5;

    i = 0;
    while(i < size)
    {
        printf("%d", tab[i]);
        printf(" ");
        i++;
    }
    sort_int_tab(tab, 5);
    i = 0;
    printf("\n");
    while(i < size)
    {
        printf("%d", tab[i]);
        printf(" ");
        i++;
    }
    printf("\n");
    return (0);
}
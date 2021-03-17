/*
**Useful functions created for minishell
**check word and search word detect keywords in commands
*/

#include "minishell.h"

int check_word(char *str, char *to_find, int i)
{
    int j;

    j = 0;
    while (to_find[j])
    {
        if (str[i + j] == to_find[j])
            j++;
        else
            return (0);
    }
    return (1);
}

int search_word(char *str, char *to_find)
{
    int i;

    i = 0;
    while(str[i])
    {
        if (str[i] == to_find[0])
        {
            if (check_word(str, to_find, i) == 1)
                return (1);
        }
        i++;
    }
    return (0);
}
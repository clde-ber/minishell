/*
**All functions pertaining the echo implementation. WIP: echo doc disappears to be attributed to redirection functions.
** echo stdin goes into echo main and creates char *output to be passed if redirection exists or to be printed.
*/

#include "minishell.h"

void    ft_echo_stdin(char *str, int option, int i)
{
    // add difference single double quote
    i++;
    while (str[i] != '\'' && str[i] != '\"')
    {
        write(1, &str[i], 1);
        i++;
    }
    if (option == 0)
        write(1, "\n", 1);
    // check if EOF print
    write(1, "\0", 1);
}

void    ft_echo_doc(char *str, int option, int i)
{
    write(1, "here", 4);
    return;
}


void    ft_echo(char *str)
{
    // tester linux echo sans guillements
    int option;
    int i;

    i = 0;
    option = search_word(str, "-n");
    while (str[i])
    {
        if (str[i] == '<' || str[i] == '>')
        {
            ft_echo_doc(str, option, i);
            return ;
        }
        else if (str[i] == '\"' || str[i] == '\'')
        {
            ft_echo_stdin(str, option, i);
            return ;
        }
        i++;
    }
}

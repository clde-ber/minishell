#include "minishell.h"

t_list *var_env = NULL;

void    redir_file(char *str, char *output)
{

}

void    check_redir(char *command, char *output)
{
    char *ret;

    //if ((ret = strchr(command, '<')) != NULL)
    //    redir_ext(command, output);
    /*else*/ if ((ret = strchr(command, '>')) != NULL)
    {
    //    if (ret++ == '>')
    //        redir_EOF(command, output);
        redir_file(command, output);
    }
}

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

char *getcommand(char *str)
{
    int i;
    int j;
    char *ret;

    i = 0;
    j = 0;
    while (str[i] && str[i] != '|' && str[i] != ';' && str[i] != ':')
        i++;
    if (i == 0)
        return (NULL);
    if (!(ret = malloc(sizeof(char) * (i + 1))))
        return (NULL);
    while(j < i)
    {
        ret[j] = str[j];
        j++;
    }
    ret[j] = '\0';
    return (ret);
}

void    ft_pwd(char *str)
{
    char *path;

    // path = NULL;
    // getcwd(path, 0);
    // version linux: oath alloué par appel de commande via malloc si size est 0 et buff null. Need free apres
    
    if (!(path = malloc(sizeof(char) * 1000)))
        return ;
    getcwd(path, 1000);
    check_redir(str, path);
    // printf("%s", path);
    free(path);
}

// trouve la fonction qui correspond a la commande.
// Problemes : ici trouve le mot cle sans difference de s'il est intégré a une autre commande ou pas.
// exemple: echo "pwd" > file pourrait trouver echo en premier.
// need parsing plus precis en lettre par lettre

void    dispatch(char *str, char **env)
{
    if (search_word(str, "pwd") == 1)
        ft_pwd(str);
    else if (search_word(str, "echo") == 1)
        ft_echo(str);
    else if (search_word(str, "./") == 1)
        find_exe(0, str);
    else if (ft_strcmp(ft_split(str, "\t\n\r\v\f ")[0], "export") == 0)
        set_env(env, ft_split(str, "\t\n\r\v\f "));
    else if (ft_strcmp(ft_split(str, "\t\n\r\v\f ")[0], "env") == 0)
        print_env(env, var_env);
    else if (ft_strcmp(ft_split(str, "\t\n\r\v\f ")[0], "unset") == 0)
        unset(var_env, ft_split(str, "\t\n\r\v\f "));
    else
        printf("nope");
}

// pour l'instant, ne prend qu'une commande. La commande doit etre enregistrée (pas fait), découpée (fait mais 
// rien n'est fait pour la suite de la commande) et envoyée a dispatch pour parsing.
int main(int ac, char **av, char **env)
{
    char *line;
    int end;
    int res;
    char *command;

    end = 0;
    line = NULL;
    while (end == 0)
    {
        write(1, "***minishell*** > ", 18);
        res = get_next_line(0, &line);
        if (ft_strcmp(line, "exit") == 0)
            end = 1;
        // printf("test:%s", line);
         if ((command = getcommand(line)) != NULL)
            dispatch(command, env);
//        end = 1;
    }
    free(line);
}
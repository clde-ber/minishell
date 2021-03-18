#include "minishell.h"

t_list *var_env = NULL;

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
    int i;
    char **res;

    i = 0;
    res = ft_split(str, "\t\n\r\v\f ");
    while (res[i])
    {
        printf("%d\n", i);
        printf("%s\n", res[i]);
        i++;
    }
/*    if (search_word(str, "pwd") == 1)
        ft_pwd(str);
    else if (search_word(str, "echo") == 1)
        ft_echo(str);
    else*/ if (ft_split(str, "\t\n\r\v\f ")[0][0] == '.' && ft_split(str, "\t\n\r\v\f ")[0][1] == '/')
        find_exe(0, str, env);
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
    while (res && end == 0)
    {
        write(1, "***minishell*** > ", 18);
        res = get_next_line(0, &line);
        if (ft_strcmp(line, "exit") == 0) //builtin à coder
            end = 1;
        // printf("test:%s", line);
         if ((command = getcommand(line)) != NULL)
            dispatch(command, env);
//        end = 1;
    }
    free(line);
    return (0);
}
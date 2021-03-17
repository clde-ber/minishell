#include "minishell.h"

char *ft_get_name(char *str)
{
    int i;
    int boolean;
    char *copy;

    i = 0;
    boolean = 0;
    copy = ft_strdup(str);
    while (copy[i] && boolean == 0)
    {
        if (copy[i] == '=')
        {
            copy[i] = '\0';
            boolean = 1;
        }
        i++;
    }
    while (copy[i])
    {
        copy[i] = '\0';
        i++;
    }
    return (copy);
}

void	ft_lstdelone(t_list *lst)
{
	if (lst)
	{
		lst->name = "\0";
		lst->value = "\0";
	}
}


t_list	*ft_lstnew(char *name, void *value)
{
	t_list *new;

	if (!(new = malloc(sizeof(t_list))))
		return (NULL);
	new->name = name;
    new->value = value;
	new->next = NULL;
    new->prec = NULL;
	return (new);
}

void	ft_lstadd_front(t_list **alst, t_list *new)
{
	if (alst && new)
	{
		new->next = *alst;
		*alst = new;
	}
}

t_list	*ft_lstlast(t_list *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

void	ft_lstadd_back(t_list **alst, t_list *new)
{
	t_list *last;

	if (!new)
		return ;
	if (*alst == NULL)
	{
		*alst = new;
		new->next = NULL;
	}
	else
	{
		last = ft_lstlast(*alst);
		last->next = new;
		new->next = NULL;
	}
}

t_list ft_record(void *lst, void *str)
{
    ((t_list *)lst)->name = ft_get_name(str);
    ((t_list *)lst)->value = ft_strchr(str, '=') + 1;
}

void	ft_lstiter(t_list *lst, t_list (*f)(void *, void *), char *str)
{
    int i = 0;
	if (!lst || !f)
		return ;
	f(lst, str);
	lst = lst->next;
}

t_list *set_env(char **env, char **tab)
{
    int i;
	int j;
	int k;
    t_list *lst;
    t_list *first;

	j = 0;
	while (tab[j])
		j++;
    i = j - 1;
	k = 0;
	while (env[k])
		k++;
	k--;
	var_env = ft_lstnew(ft_get_name(tab[i]), ft_strchr(tab[i], '=') + 1);
	while (i >= 1)
    {
		ft_lstadd_front(&var_env, ft_lstnew(ft_get_name(tab[i]), ft_strchr(tab[i], '=') + 1));
		ft_lstiter(var_env, &ft_record, tab[i]);
		i--;
	}
	while (k >= 1)
	{
		ft_lstadd_front(&var_env, ft_lstnew(ft_get_name(env[k]), ft_strchr(env[k], '=') + 1));
		ft_lstiter(var_env, &ft_record, env[k]);
		k--;
	}
    return (var_env);
}

t_list	*unset(t_list *env, char **tab)
{
	int i;
	int j = 0;

	while (tab[j])
		j++;
	i = 1;
	while (env->next)
	{
		while (i < j)
		{
			if (strcmp(tab[i], env->name) == 0)
			{
				env->name = "";
				env->value = "";
			}
			i++;
		}
		env = env->next;
		i = 1;
	}
	return (env);
}

void print_env(char **tab, t_list *env)
{
	char *str = NULL;
	char *str2 = NULL;
	while (env->next)
	{
		if (ft_strlen(env->name))
    	{
			str2 = ft_strjoin(env->name, "=");
			str = ft_strjoin(str2, env->value);
			printf("%s\n", str);
			free(str);
			free(str2);
		}
		env = env->next;
	}
}
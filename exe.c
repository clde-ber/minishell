#include "minishell.h"

void	*ft_calloc(size_t count, size_t size)
{
	size_t	i;
	void	*ptr;

	i = 0;
	if (!(ptr = (void *)malloc(count * size)))
		return (0);
	while (i < count * size)
	{
		((char *)ptr)[i] = 0;
		i++;
	}
	return (ptr);
}

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t i;

	if (!dst && !src)
		return (NULL);
	i = 0;
	while (i < n)
	{
		((char *)dst)[i] = ((char *)src)[i];
		i++;
	}
	return (dst);
}

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*tmp_src;
	unsigned char	*tmp_dst;

	if (!dst && !src)
		return (NULL);
	if (src <= dst)
	{
		tmp_dst = (unsigned char *)dst;
		tmp_src = (unsigned char *)src;
		while (len--)
			tmp_dst[len] = tmp_src[len];
	}
	else
		ft_memcpy(dst, src, len);
	return (dst);
}

int ft_ischarset(char *str, char c)
{
	int i;

	i = 0;
//	printf("str %s\n", str);
//	printf("c %c\n", c);
	while (str[i])
	{
		if ((char)c == str[i])
			return (1);
		i++;
	}
	return (0);
}

size_t	len_wd(char const *str, char *charset)
{
	size_t i;

	i = 0;
	while (str[i])
	{
		if (ft_ischarset(charset, str[i]))
			break ;
		i++;
	}
	return (i);
}

size_t	count_malloc(char const *s, char *str)
{
	size_t i;
	size_t count;

	i = 0;
	count = 0;
	if (s[i] == '\0')
		return (1);
	while (s[i])
	{
//		printf("count %d\n", count);
//		printf("i %d\n", i);
		if (ft_ischarset(str, s[i]) == 0 && (ft_ischarset(str, s[i + 1]) || s[i + 1] == '\0'))
			count++;
		i++;
	}
	return (count);
}

void		*ft_free(char **res, int j)
{
	int	i;

	i = 0;
	while (i < j)
	{
		free(res[i]);
		i++;
	}
	free(res);
	return (NULL);
}

char			**ft_split(char const *s, char *str)
{
	size_t	i;
	size_t	j;
	char	**res;

	i = 0;
	j = 0;
	if (!s || !*s)
		return ((char **)ft_calloc(2, sizeof(char *)));
	if (!(res = malloc(sizeof(char *) * (count_malloc(s, str) + 1))))
		return (0);
	while (i < ft_strlen((char *)s))
	{
		while (j < count_malloc(s, str) && s[i] && ft_ischarset(str, s[i]) == 0)
		{
			if (!(res[j] = malloc(sizeof(char) * (len_wd(&s[i], str) + 1))))
				return (ft_free(res, j));
			res[j] = ft_memmove(res[j], &s[i], len_wd(&s[i], str) + 1);
			res[j][len_wd(&s[i], str)] = '\0';
			j++;
			i += len_wd(&s[i], str);
		}
		i++;
	}
	res[count_malloc(s, str)] = 0;
	return (res);
}


size_t	ft_strlen(char *str)
{
	size_t i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}


char	*ft_strjoin(char *s1, char *s2)
{
	size_t	i;
	size_t	j;
	char	*ptr;

	i = -1;
	j = -1;
	if (!s1 && !s2)
		return (0);
	if (!(ptr = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1))))
		return (0);
	while (s1[++i])
		ptr[i] = s1[i];
	while (s2[++j])
		ptr[i + j] = s2[j];
	ptr[i + j] = '\0';
	return (ptr);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t i;

	i = 0;
	while (s1[i] || s2[i])
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (0);
}

char	*ft_strchr(const char *s, int c)
{
	char	*str;

	str = (char *)s;
	while (*str && *str != (char)c)
		str++;
	return (*str == c ? str : NULL);
}

char	*ft_strdup(const char *s1)
{
	size_t	i;
	char	*ptr;

	i = 0;
	if (!(ptr = malloc(sizeof(char) * (ft_strlen((char *)s1) + 1))))
		return (0);
	while (s1[i])
	{
		ptr[i] = s1[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

char	*ft_get_filename(const char *s, int c)
{
	char	*str;
    int i;

	str = (char *)s;
    i = ft_strlen(str);
//    if (str[ft_strlen(str) - 1] == '/')
//        str[ft_strlen(str) - 1] = '\0';
    while (i)
    {
        if (str[i] == c)
            return (ft_strdup((const char *)&str[i + 1]));
        i--;
    }
    return (NULL);
}

char *get_path(char *path, char c)
{
    char	*str;
    int i;
    int j;

    j = 1;
	str = (char *)path;
    i = ft_strlen(str);
//    if (str[ft_strlen(str) - 1] == '/')
//        str[ft_strlen(str) - 1] = '\0';
    while (i)
    {
        if (str[i] == c)
        {
            while (str[i + j])
            {
                str[i + j] = '\0';
                j++;
            }
            return (str);
        }
        i--;
    }
    return (NULL);
}

int launch_exe(char *exe, char *path)
{
    pid_t pid;
    int ret;
    int *pid_ret;

    pid = 0;
    ret = 0;
    errno = 0;
    pid_ret = 0;
    char* argv[] = { ft_strjoin(path, exe), "/bin/sh", "-c", NULL };
    char* envp[] = { ft_strjoin("HOME=", "."), ft_strjoin("PATH=", path), NULL };
    if ((pid = fork()) == 0)
    {
        if ((ret = execve(argv[0], argv, envp)) == -1)
        {
            printf("%s\n", strerror(errno));
            return (0);
        }
        return (0);
    }
    else if (pid == -1)
    {
        printf("%s\n", strerror(errno));
        return (0);
    }
    else
	{
		//waitpid
        return (0);
	}
// waitpid attd que le programme se termine 
}

int find_exe(int index, char *path)
{
    DIR *dir;
    int i;
    char *str;
    char *path_mod;

    i = 0;
    str = 0;
    struct dirent *s_dir;
    str = ft_get_filename(path, '/');
    path_mod = NULL;
    errno = 0;
    if (!(dir = opendir(get_path(path, '/'))))
        printf("%s\n", strerror(errno));
    while ((s_dir = readdir(dir)))
    {
        if (ft_strcmp(s_dir->d_name, str) == 0)
        {
            launch_exe(s_dir->d_name, path);
            closedir(dir);
            return (0);
        }
    }
    if (errno)
        printf("%s\n", strerror(errno));
    else
    {
        launch_exe(str, path);
        return (0);
    }
}

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
//	int i = -1;
//	printf("%d\n", var_env);
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
/*
int main(int argc, char **argv, char **env)
{
//	find_exe(0, argv[1]);
	var_env = NULL;
	if (strcmp(argv[1], "export") == 0)
		var_env = set_env(argc, argv);
	printf("%s\n", var_env->name);
	int i = -1;
	if (strcmp(argv[1], "env") == 0)
	{
		while (env[++i])
			printf("%s\n", env[i]);
//		printf("%d\n", var_env);
		while (var_env && var_env->next)
		{
			if (var_env->name)
    			printf(ft_strjoin(ft_strjoin(var_env->name, "="), var_env->value));
			printf("\n");
			var_env = var_env->next;
		}
	}
	if (strcmp(argv[1], "unset") == 0)
		ft_lstdelone(var_env);
    return (0);
}*/

//le traitement de la line doit englober commandes, ; | mais aussi traite guillemets simples & doubles
//$HOME renvoie pwd du profil 
//'$HOME'
//"$HOME"
//gérer les antislashs!!!!!
//deux et fork wait pid sur execve et pipe
// ctrl c d sigkill etc gréer une variable globale signaux = fonctions spécialisées qui dit observe si t'as des signaux fais attention
// derriere tu mets les autres fct sig
//faire le write sur le stderr ?
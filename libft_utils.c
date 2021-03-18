#include "minishell.h"

size_t	ft_strlen(char *str)
{
	size_t i;

	i = 0;
	write(1, "st", 2);
	if (!str)
		return (0);
	write(1, "sr", 2);
	while (str[i])
		i++;
	return (i);
}

/*
char	*ft_strjoin(char *s1, char *s2)
{
	size_t	i;
	size_t	j;
	char	*ptr;

	i = -1;
	j = -1;
	if (!s1 || !s2)
		return (0);
	if (!(ptr = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1))))
		return (0);
	while (s1[++i])
		ptr[i] = s1[i];
	while (s2[++j])
		ptr[i + j] = s2[j];
	ptr[i + j] = '\0';
	return (ptr);
}*/

char    *ft_strjoin(char *str1, char *str2)
{
    int i;
    int j;
    int len;
    char *ret;

    i = 0;
    j = 0;
    len = ft_strlen(str1) + ft_strlen(str2);
	write(1, "la", 2);
    if (!(ret = malloc(sizeof(char) * len + 1)))
        return (NULL);
    if (str1)
    {
        while (str1[i])
            ret[i] = str1[i++];
    }
    if (str2)
    {
        while (str2[j])
            ret[i++] = str2[j++];
    }
    ret[len] = '\0';
    return (ret);
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
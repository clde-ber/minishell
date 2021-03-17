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
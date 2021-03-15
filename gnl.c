#include "minishell.h"

#define BUFFER_SIZE 50

static char		*ft_read_a_join(size_t i, char *buf, char **line)
{
	buf[i] = '\0';
	line[0] = join_a_free(line[0], buf);
	return (line[0]);
}

static char		*ft_update_left(char *left, char *buf, char **line)
{
	line[0][find_n(line[0], ft_strlen(line[0]))] = '\0';
	ft_memmove(left, buf + find_n(buf, BUFFER_SIZE) + 1, ft_strlen(buf +
	find_n(buf, BUFFER_SIZE)));
	return (line[0]);
}

static char		*ft_create_a_clear_left(char *left, char *buf, size_t size)
{
	int k;

	buf[0] = '\0';
	if (left)
	{
		k = find_n(left, size);
		if (k != -1)
			ft_memmove(left, left + k + 1, ft_strlen(left + k));
		else
			left[0] = '\0';
		return (left);
	}
	else
	{
		if (!(left = malloc(sizeof(char) * (size + 1))))
			return (0);
		left[0] = '\0';
		return (left);
	}
}

int				get_next_line(int fd, char **line)
{
	ssize_t		i;
	char		buf[BUFFER_SIZE + 1];
	static char *left;

	left = (!left) ? ft_create_a_clear_left(left, buf, BUFFER_SIZE) : left;
	line[0] = ft_strjoin(left, "");
	ft_create_a_clear_left(left, buf, BUFFER_SIZE);
	if (find_n(line[0], ft_strlen(line[0])) != -1)
	{
		line[0][find_n(line[0], ft_strlen(line[0]))] = '\0';
		return (1);
	}
	while (find_n(buf, BUFFER_SIZE) == -1 &&
	(i = read(fd, buf, BUFFER_SIZE)) > 0)
		line[0] = ft_read_a_join(i, buf, line);
	line[0] = (i == 0) ? line[0] : join_a_free(line[0], buf);
	if (find_n(line[0], ft_strlen(line[0])) != -1)
	{
		line[0] = ft_update_left(left, buf, line);
		return (1);
	}
	line[0] = join_a_free(line[0], buf);
	free(left);
	left = 0;
	return (fd < 0 || read(fd, buf, 0) < 0 || BUFFER_SIZE <= 0) ? -1 : 0;
}
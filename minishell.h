#ifndef MINISHELL_H
#define MINISHELL_H

#include <stddef.h>
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <fcntl.h>

/*
**Liste chainee for termcap
*/
/*typedef struct s_list t_list;
struct s_list{
    char *line;
    void *next;
    void *prec;
};*/

typedef struct s_list
{
    char *name;
    void *value;
    struct s_list *prec;
    struct s_list *next;
}               t_list;


int		find_n(char *buf, size_t size);
void	*ft_memmove(void *dst, const void *src, size_t len);
size_t	ft_strlen(char *str);
char	*join_a_free(char *s1, char *s2);
char	*ft_strjoin(char *s1, char *s2);
int				get_next_line(int fd, char **line);
size_t	ft_strlen(char *str);
void    dispatch(char *str, char **env);
void    ft_pwd(char *str);
char *getcommand(char *str);
void    ft_echo(char *str);
void    ft_echo_doc(char *str, int option, int i);
void    ft_echo_stdin(char *str, int option, int i);
int search_word(char *str, char *to_find);
int check_word(char *str, char *to_find, int i);
void    check_redir(char *command, char *output);
void    redir_file(char *str, char *output);
int	ft_strcmp(const char *s1, const char *s2);
char			**ft_split(char const *s, char *str);
void print_env(char **tab, t_list *env);
t_list	*unset(t_list *env, char **tab);
t_list *set_env(char **env, char **tab);
void	ft_lstiter(t_list *lst, t_list (*f)(void *, void *), char *str);
t_list ft_record(void *lst, void *str);
void	ft_lstadd_front(t_list **alst, t_list *new);
t_list	*ft_lstnew(char *name, void *value);
void	ft_lstdelone(t_list *lst);
char *ft_get_name(char *str);
int find_exe(int index, char *path, char **env);
int launch_exe(char *exe, char *path, char **env);
char *get_path(char *path, char c);
char	*ft_get_filename(const char *s, int c);
char	*ft_strdup(const char *s1);
char	*ft_strchr(const char *s, int c);
int	ft_strcmp(const char *s1, const char *s2);
void	*ft_calloc(size_t count, size_t size);
void	*ft_memcpy(void *dst, const void *src, size_t n);
int ft_ischarset(char *str, char c);
size_t	len_wd(char const *str, char *charset);
size_t	count_malloc(char const *s, char *str);
void		*ft_free(char **res, int j);
void    check_redir(char *command, char *output);
void    redir_file(char *str, char *output);

extern t_list *var_env;

#endif
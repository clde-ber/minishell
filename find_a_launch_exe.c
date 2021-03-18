#include "minishell.h"

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

int launch_exe(char *exe, char *path, char **env)
{
    pid_t pid;
    int ret;
    int status;

    pid = 0;
    ret = 0;
    errno = 0;
    status = 0;
    char* argv[] = { ft_strjoin(path, exe), env, NULL };
    char* envp[] = { ft_strjoin("HOME=", "."), ft_strjoin("PATH=", path), NULL };
    if ((pid = fork()) == 0)
    {
        if ((ret = execve(argv[0], argv, envp)) == -1)
		{
		    printf("%s\n", strerror(errno));
			exit(0);
		}
    }
    waitpid(ret, &status, 0);
	if (WIFEXITED(status))
        return (0);
    else
	{
        printf("%s\n", strerror(errno));
		exit(0);
	}
    return (0);
// waitpid attd que le programme se termine 
}

int find_exe(int index, char *path, char **env)
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
	{
	    printf("%s\n", strerror(errno));
		return (0);
	}
    while ((s_dir = readdir(dir)))
    {
        if (ft_strcmp(s_dir->d_name, str) == 0)
        {
            launch_exe(s_dir->d_name, path, env);
            closedir(dir);
            return (0);
        }
    }
    if (errno)
        printf("%s\n", strerror(errno));
    else
        launch_exe(str, path, env);
	return (0);
}

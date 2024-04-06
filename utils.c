#include "pipex.h"

void ft_free_splits(char **split)
{
    int i;

    i = 0;
    while (split[i])
    {
        free(split[i]);
        i++;
    }
    free(split);
}

static char    *get_env(char **env)
{
    int i;
    while (env[i])
    {
        if (!ft_strncmp(env[i], "PATH=", 5))
            return (env[i] + 5);
        i++;
    }
}

char *get_path(char *cmd, char **env)
{
    int     i;
    char    **all_path;
    char    *path_part;
    char    *exec;

    i = 0;
    all_path = ft_split(get_env(env), ":");
    while (all_path[i])
    {
        path_part =ft_strjoin(all_path[i], "/");
        exec = ft_strjoin(path_part, cmd);
        free(path_part);
        if (!access(exec, F_OK | X_OK))
            return (exec);
        free(exec);
        i++;
    }
    ft_free_splits(all_path);
    return (cmd);
}

int open_file_child(char *file)
{
    int fd;
    
    if (access(file, F_OK))
        fd = open(file, O_RDONLY | O_CREAT, 0777);
    else
    {
        if (access(file, R_OK))
            ft_error("permission denied");
        fd = open(file, O_RDONLY);   
    }
    if (fd == -1)
        ft_error("infile");
    return (fd);
}

int open_file_parent(char *file)
{
    int fd;

    if (access(file, F_OK))
        fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
    else
    {
        if (access(file, W_OK))
            ft_error("permission denied");
        fd = open(file, O_WRONLY | O_TRUNC);
    }
    if (fd == -1)
        ft_error("outfile");
    return (fd);
}

#include "pipex.h"

void ft_error(char *str)
{
    perror(str);
    exit(EXIT_FAILURE);
}

static void exec_cmd(char *cmd, char **env)
{
    char **s_cmd;
    char *path;

    s_cmd = ft_split(cmd, ' ');
    path = get_path(s_cmd[0], env);
    if (execve(path, s_cmd, env) == -1)
    {
        ft_free_splits(s_cmd);
        ft_error("command not found");
    }
    
}

static void parent(char **argv, int *fd, char **env)
{
    int fd_p;

    close(fd[1]);
    fd_p = open_file_parent(argv[4]);
    if (dup2(fd_p, STDOUT_FILENO) == -1)
        ft_error("error: failed to redirect stdout");
    if (dup2(fd[0], STDIN_FILENO) == -1)
        ft_error("error: failed to redirect stdin");
    exec_cmd(argv[3], env);
}

static void child(char **argv, int *fd, char **env)
{
    int fd_c;

    close(fd[0]);
    fd_c = open_file_child(argv[1]);
    if (dup2(fd_c, STDIN_FILENO) == -1)
        ft_error("error: failed to redirect stdin");
    if (dup2(fd[1], STDOUT_FILENO) == -1)
        ft_error("error: failed to redirect stdout");
    exec_cmd(argv[2], env);
}

int main(int argc, char **argv, char **env)
{
    int fd[2];
    pid_t pid;
    int status;

    if (argc != 5)
        ft_error("./pipex file1 cmd cmd file2");
    if (pipe(fd) == -1)
        ft_error("fail in pipe");
    pid = fork();
    if (pid == -1)
        ft_error("fail in fork");
    if (!pid)
        child(argv, fd, env);
    wait(&status);
    if (pid)
        parent(argv, fd, env);
    return (0);
}
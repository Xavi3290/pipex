/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xavi <xavi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 11:55:20 by xroca-pe          #+#    #+#             */
/*   Updated: 2024/04/09 14:14:19 by xavi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static void put_in_pipe(char **argv, int *fd)
{
	char *lim;

	close(fd[0]);
	while (1)
	{
		lim = get_next_line(STDIN_FILENO);
		if (!ft_strncmp(lim, argv[2], ft_strlen(argv[2])))
		{
			free(lim);
			break;
		}
		ft_putstr_fd(lim, fd[1]);
		free(lim);
	}
}

static void here_doc(char **argv)
{
    int	fd[2];
	pid_t pid;
	int status;

	if (pipe(fd) == -1)
		ft_error("error in pipe");
	pid = fork();
	if (!pid)
		put_in_pipe(argv, fd);
	wait (&status);
	if (pid)
	{
		close(fd[1]);
		if (dup2(fd[0], STDIN_FILENO) == -1)
		    ft_error("error: failed to redirect stdin");
	}
}

static ft_pipe(char *cmd, char **env)
{
    int		fd[2];
	pid_t	pid;
	int		status;

	if (pipe(fd) == -1)
		ft_error("error in pipe");
	pid = fork();
	if (pid == -1)
		ft_error("error in fork");
	if (!pid)
    {
        close(fd[0]);
	    if (dup2(fd[1], STDOUT_FILENO) == -1)
		    ft_error("error: failed to redirect stdout");
	    exec_cmd(cmd, env);
    }
	wait(&status);
	if (pid)
    {
        close(fd[1]);
	    if (dup2(fd[0], STDIN_FILENO) == -1)
		    ft_error("error: failed to redirect stdin");
    }
}

static void	exec_cmd(char *cmd, char **env)
{
	char	**s_cmd;
	char	*path;

	s_cmd = ft_split(cmd, ' ');
	if (!s_cmd)
		ft_error("error in split");
	path = get_path(s_cmd[0], env);
	if (execve(path, s_cmd, env) == -1)
	{
		ft_free_splits(s_cmd);
		ft_error("command not found");
	}
}


int	main(int argc, char **argv, char **env)
{
    int i;
    int fd;
    
	if (argc < 5)
		ft_error("./pipex file1 cmd cmd ... file2");
    i = 2;
    if (!ft_strncmp(argv[1], "here_doc", 8))
    {
        if (argc <  6)
            ft_error("./pipex here_doc lim cmd cmd ... file2");
        i = 3;
        fd = open_file(argv[argc - 1], 0, NULL);
        here_doc(argv);
    }
    else
        fd = open_file(argv[argc - 1], 1, argv[1]);
    while (i < argc - 2)
        ft_pipe(argv[i], env);
    if (dup2(fd, STDOUT_FILENO) == -1)
        ft_error("error: failed to redirect stdout");
    exec_cmd(argv[argc - 1], env);
	return (0);
}

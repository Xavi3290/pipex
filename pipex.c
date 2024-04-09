/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xavi <xavi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 12:29:19 by xroca-pe          #+#    #+#             */
/*   Updated: 2024/04/09 13:10:41 by xavi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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

static void	parent(char **argv, int *fd, char **env)
{
	int	fd_p;

	close(fd[1]);
	fd_p = open_file(argv[4], 0);
	if (dup2(fd_p, STDOUT_FILENO) == -1)
		ft_error("error: failed to redirect stdout");
	if (dup2(fd[0], STDIN_FILENO) == -1)
		ft_error("error: failed to redirect stdin");
	exec_cmd(argv[3], env);
}

static void	child(char **argv, int *fd, char **env)
{
	int	fd_c;

	close(fd[0]);
	fd_c = open_file(argv[1], 1);
	if (dup2(fd_c, STDIN_FILENO) == -1)
		ft_error("error: failed to redirect stdin");
	if (dup2(fd[1], STDOUT_FILENO) == -1)
		ft_error("error: failed to redirect stdout");
	exec_cmd(argv[2], env);
}

int	main(int argc, char **argv, char **env)
{
	int		fd[2];
	pid_t	pid;
	int		status;

	if (argc != 5)
		ft_error("./pipex file1 cmd cmd file2");
	if (pipe(fd) == -1)
		ft_error("error in pipe");
	pid = fork();
	if (pid == -1)
		ft_error("error in fork");
	if (!pid)
		child(argv, fd, env);
	wait(&status);
	if (pid)
		parent(argv, fd, env);
	return (0);
}

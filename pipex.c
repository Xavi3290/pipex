/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xroca-pe <xroca-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 12:29:19 by xroca-pe          #+#    #+#             */
/*   Updated: 2024/04/11 15:23:54 by xroca-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	exec_cmd(char *cmd, char **env)
{
	char	**s_cmd;
	char	*path;

	s_cmd = ft_split(cmd, ' ');
	if (!s_cmd)
		ft_error("command not found\n", 0, 127);
	path = get_path(s_cmd[0], env);
	if (execve(path, s_cmd, env) == -1)
	{
		ft_free_splits(s_cmd);
		ft_error("command not found\n", 0, 127);
	}
}

static void	parent(char **argv, int *fd, char **env)
{
	int	fd_p;

	close(fd[1]);
	fd_p = open_file(argv[4], 0);
	if (dup2(fd_p, STDOUT_FILENO) == -1)
		ft_error("error failed to redirect stdout\n", 1, 2);
	if (dup2(fd[0], STDIN_FILENO) == -1)
		ft_error("error failed to redirect stdin", 1, 2);
	exec_cmd(argv[3], env);
	close(fd_p);
}

static void	child(char **argv, int *fd, char **env)
{
	int	fd_c;

	close(fd[0]);
	fd_c = open_file(argv[1], 1);
	if (dup2(fd_c, STDIN_FILENO) == -1)
		ft_error("error failed to redirect stdin\n", 1, 2);
	if (dup2(fd[1], STDOUT_FILENO) == -1)
		ft_error("error failed to redirect stdout\n", 1, 2);
	exec_cmd(argv[2], env);
	close(fd_c);
}

int	main(int argc, char **argv, char **env)
{
	int		fd[2];
	pid_t	pid;
	int		status;

	if (argc != 5)
		ft_error("./pipex file1 cmd cmd file2\n", 0, 2);
	if (pipe(fd) == -1)
		ft_error("error in pipe\n", 1, 2);
	pid = fork();
	if (pid == -1)
		ft_error("error in fork\n", 1, 2);
	if (!pid)
		child(argv, fd, env);
	wait(&status);
	if (pid)
		parent(argv, fd, env);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xroca-pe <xroca-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 11:59:34 by xroca-pe          #+#    #+#             */
/*   Updated: 2024/04/08 19:56:01 by xroca-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	ft_error(char *str)
{
	perror(str);
	exit(EXIT_FAILURE);
}

void	ft_free_splits(char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

static char	*get_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], "PATH=", 5))
			return (env[i] + 5);
		i++;
	}
	return (NULL);
}

char	*get_path(char *cmd, char **env)
{
	int		i;
	char	**all_path;
	char	*path_part;
	char	*exec;

	i = 0;
	all_path = ft_split(get_env(env), ':');
	if (!all_path)
		ft_error("split error");
	while (all_path[i])
	{
		path_part = ft_strjoin(all_path[i], "/");
		exec = ft_strjoin(path_part, cmd);
		if (!exec)
			ft_error("error strjoin");
		free(path_part);
		if (!access(exec, F_OK | X_OK))
			return (exec);
		free(exec);
		i++;
	}
	ft_free_splits(all_path);
	return (cmd);
}

int	open_file(char *file, int option)
{
	int	fd;
    int fd_i;
    
    if (option == 1)
	    fd = open(file, O_RDONLY | O_CREAT, 0644);
        fd_i = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (dup2(fd_i, STDIN_FILENO) == -1)
            ft_error("error: failed to redirect stdout");
    else
        fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
    if (fd == -1)
		    ft_error("error open file");
	return (fd);
}

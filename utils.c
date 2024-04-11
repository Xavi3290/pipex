/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xroca-pe <xroca-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 11:53:11 by xroca-pe          #+#    #+#             */
/*   Updated: 2024/04/11 10:59:43 by xroca-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_error(char *str)
{
	perror(str);
	exit(EXIT_FAILURE);
}

void	ft_free_splits(char **split)
{
	int	i;

	i = 0;
	if (split)
	{
		while (split[i])
		{
			free(split[i]);
			i++;
		}
		free(split);
	}
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
		ft_error("error in split");
	while (all_path[i])
	{
		path_part = ft_strjoin(all_path[i], "/");
		if (!path_part)
			ft_error("error in strjoin");
		exec = ft_strjoin(path_part, cmd);
		if (!exec)
			ft_error("error in strjoin");
		free(path_part);
		if (!access(exec, F_OK | X_OK))
			return (exec);
		free(exec);
		i++;
	}
	ft_free_splits(all_path);
	return (cmd);
}

int	open_file(char *file, int infile)
{
	int	fd;

	if (infile)
	{
		fd = open(file, O_RDONLY, 0644);
		if (fd == -1)
			ft_error("infile");
	}
	else
	{
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd == -1)
			ft_error("outfile");
	}
	return (fd);
}

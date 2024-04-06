#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <sys/wait.h>
# include <fcntl.h>  
# include <stdlib.h>
# include <errno.h>
# include <stdio.h>

void	ft_putstr_fd(char *s, int fd);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	**ft_split(char const *s, char c);
int	    ft_strncmp(const char *s1, const char *s2, size_t n);
size_t	ft_strlen(const char *s);
char	*ft_strjoin(char const *s1, char const *s2);

int     open_file_child(char *file);
int     open_file_parent(char *file);
void    ft_error(char *str);
char    *get_path(char *cmd, char **env);
void    ft_free_splits(char **split);

#endif
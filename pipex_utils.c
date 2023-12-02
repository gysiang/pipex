/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyong-si <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 17:15:57 by gyong-si          #+#    #+#             */
/*   Updated: 2023/12/01 17:32:00 by gyong-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <errno.h>
#include "ft_printf/ft_printf.h"
#include "ft_printf/libft/libft.h"

char	*add_slash(char *s)
{
	char	*res;
	int		len;
	int		j;
	int		i;

	len = 0;
	j = 0;
	i = 0;
	len = ft_strlen(s);
	res = malloc(sizeof(char) * (len + 2));
	if (!res)
		return (NULL);
	while (s[j])
	{
		res[i++] = s[j++];
	}
	res[i] = '/';
	res[i + 1] = '\0';
	return (res);
}

/**
This function will get a path from the envp that has PATH in its string
It looks something like this PATH=/bin/user:/local/sbin:/local/bin/....
Our next task is to ft_split by :
**/
char	*get_path(char **array)
{
	int			i;
	char		*path;

	i = 0;
	while (array[i] != NULL) 
	{
		if (ft_strncmp(array[i], "PATH=", 5) == 0)
		{
			path = array[i] + 5;
			break ;
		}
		i++;
	}
	return (path);
}

/**
This function frees all the strings before count. Used when mem allocation fails.
**/
void	ft_free_array(char **array, int count)
{
	while (count > 0)
		free(array[--count]);
	free(array);
}

char	*get_path_array(char *cmd, char *path)
{
	char	*tmp;
	char	**path_array;
	int		i;

	i = 0;
	path_array = ft_split(path, ':');
	while (path_array[i] != NULL)
	{
		tmp = add_slash(path_array[i]);
		if (tmp == NULL)
		{
			ft_free_array(path_array, i);
			return (NULL);
		}
		free(path_array[i]);
		path_array[i] = ft_strjoin(tmp, cmd);
		free(tmp);
		if (path_array[i] == NULL)
		{
			free_path_array(path_array, i);
			return (NULL);
		}
		i++;
	}
	return (path_array);
}

void	check_fd(int int_fd, int out_fd)
{
	if (int_fd != STDIN_FILENO)
	{
		dup2(int_fd, STDIN_FILENO);
		close(int_fd);
	}
	if (out_fd != STDOUT_FILENO)
	{
		dup2(out_fd, STDOUT_FILENO);
		close(out_fd);
	}
}

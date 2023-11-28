/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyong-si <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 17:15:57 by gyong-si          #+#    #+#             */
/*   Updated: 2023/11/28 17:17:11 by gyong-si         ###   ########.fr       */
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
	int	len = 0;
	int	j = 0;
	int	i = 0;
	char	*res;

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
This function opens a file and returns a fd. If read returns -1
print out a error message.
**/

int	open_file(char *filename, int flags, mode_t mode)
{
	int	fd = open(filename, flags, mode);

	if (fd == -1)
	{
		perror("open");
		if (errno == ENOENT)
			ft_printf("%s", "Error: No such file or directory\n");
		else if (errno == EACCES)
			ft_printf("%s", "Error: Permission Denied\n");
		else
			ft_printf("%s", "Error: Unable to open\n");
		exit(EXIT_FAILURE);
	}
	return (fd);
}

char	**get_path(char *cmd, char **array)
{
	char	*path;
	char	*tmp;
	char	**path_array;
	int	i = 0;

	while (array[i] != NULL) 
	{
        	if (ft_strncmp(array[i], "PATH=", 5) == 0)
		{
			path = array[i] + 5;
			break ;
		}
		i++;
    	}
	if (path != NULL)
	{
		path_array = ft_split(path, ':');
		i = 0;
		while (path_array[i] != NULL)
		{
			tmp = add_slash(path_array[i]);
			path_array[i] = ft_strjoin(tmp, cmd);
			//ft_printf("%s\n", path_array[i]);
			free(tmp);
			i++;
		}
	}
	return (path_array);
}

void	run_command(char *command, int	int_fd, int out_fd, char **envp)
{
	pid_t	current_pid;
	int	i;
	//int	j = 0;
	char	**mycmdargs;
	char	**mypaths;

	mycmdargs = ft_split(command, ' ');
	mypaths = get_path(mycmdargs[0], envp);

	/**
	while (mypaths[j] != NULL)
	{
		ft_printf("%s\n", mypaths[j++]);
	} **/
	current_pid = fork();
	// fork failed
	if (current_pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	// fork success
	if (current_pid == 0)
	{
		// connect the input of the pipe
		if (int_fd != STDIN_FILENO)
		{
			dup2(int_fd, STDIN_FILENO);
		// after assigning to 0 can free the fd by closing
			close(int_fd);
		}
		// connect the output of the pipe
		if (out_fd != STDOUT_FILENO)
		{	dup2(out_fd, STDOUT_FILENO);
			close(out_fd);
		}
		i = -1;
		while (mypaths[++i])
		{
			//ft_printf("%s\n", mypaths[i]);
			//ft_printf("%s\n", mycmdargs[0]);
			execve(mypaths[i], mycmdargs, envp);
			//perror("Error: Line 102 Execve");
		}
		exit(EXIT_FAILURE);
	}
}


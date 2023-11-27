/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyong-si <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 18:25:50 by gyong-si          #+#    #+#             */
/*   Updated: 2023/11/27 17:41:14 by gyong-si         ###   ########.fr       */
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

/**
This function opens a file and returns a fd. If read returns -1
print out a error message.
**/
/**
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

**/

/**
void	run_command(char *command, int	int_fd, int out_fd, char **envp)
{
	pid_t	current_pid;
	char	**cmd;

	cmd = ft_split(command, ' ');
	get_path(cmd[0], envp);

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
		execve(command, new_av, envp);
		perror("execve");
		exit(EXIT_FAILURE);
	}
} **/

void	get_path(char **array)
{
	char	*path;
	//char	*final_path;
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
			ft_printf("%s\n", path_array[i]);
			i++;
		}
	}
}

char	*get_command_args(char *command)
{
	char **mycmdargs;
	//char	*finalcmd;
	size_t len;
	char	*dst;

	mycmdargs = ft_split(command, ' ');
	
	len = ft_strlen(mycmdargs[0]);
	dst = malloc(sizeof(char) + (len + 1));
	if (!dst)
		return (NULL);
	dst[0] = '/';
	ft_strlcat(dst, mycmdargs[0], len + 1);
	return (dst);
}

int	main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	printf("%s", get_command_args(av[1]));
	get_path(envp);
	return (0);
}

/**
int	main(int ac, char **av, char **envp)
{
	int	pipe_fd[2];
	int	infile_fd;
	int	outfile_fd;
	int	i;
	char	*infile;
	char	*outfile;

	i = 2;
	if (ac < 5)
	{
		ft_printf("Usage: %s <infile> <cmd1> <cmd2> .. <outfile>\n", av[0]);
		exit(EXIT_FAILURE);
	}
	else if (ac >= 5) 
	{
		infile = av[1];
		outfile = av[ac - 1];
		infile_fd = open_file(infile, O_RDONLY, 0666);
		outfile_fd = open_file(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0666);
		// loop from first command to ac -1 command
		while (ac - 1 > i)
		{
			if (pipe(pipe_fd) == -1)
			{
				perror("pipe");
				exit(EXIT_FAILURE);
			}
			// run the argument with the command and input output fds
			run_command(av[i], infile_fd, pipe_fd[1], envp);
			close(infile_fd);
			close(pipe_fd[1]);
			infile_fd = pipe_fd[0];
			i++;
		}
		run_command(av[ac - 1], infile_fd, outfile_fd, NULL);
		close(infile_fd);
	}
	return (0);
} **/

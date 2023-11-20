/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyong-si <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 18:25:50 by gyong-si          #+#    #+#             */
/*   Updated: 2023/11/20 16:59:45 by gyong-si         ###   ########.fr       */
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

void	run_command(char *command, int	int_fd, int out_fd, char *const envp[])
{
	pid_t	current_pid;
	char *const new_av[] = {"/bin/sh", "-c", command, NULL};

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
}

int	main(int ac, char **av)
{
	int	pipe_fd[2];
	int	infile_fd;
	int	outfile_fd;
	int	i;
	char	*infile;
	char	*outfile;
	char *const envp[] = {NULL};

	printf("ac 1: %s\n", av[1]);
	printf("ac 2: %s\n", av[2]);
	printf("ac 3: %s\n", av[3]);
	printf("ac 4: %s\n", av[4]);
	printf("ac 5: %s\n", av[5]);
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
}

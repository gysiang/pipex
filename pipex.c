/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyong-si <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 18:25:50 by gyong-si          #+#    #+#             */
/*   Updated: 2023/11/16 17:31:41 by gyong-si         ###   ########.fr       */
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

char	*ft_strdup(const char *s)
{
	char	*p;
	size_t	len;
	size_t	i;

	i = 0;
	len = ft_strlen(s);
	p = (char *)malloc(len + 1);
	if (!p)
		return (NULL);
	while (s[i] != '\0')
	{
		p[i] = s[i];
		i++;
	}
	p[i] = '\0';
	return (p);
}

/**
have to find a way to make an array that stores all the cmd strings
something like ft_split
**/

/**
This function opens a file and returns a fd. If read returns -1
print out a error message.
**/
int	open_file(char *filename)
{
	int	fd = open(filename, 0_RDONLY);

	if (fd == -1)
	{
		perror("open");
		if (errno == ENOENT)
			ft_printf("%s", "Error: No such file or directory\n");
		else if (errno == EACCES)
			ft_printf("%s", "Error: Permission Denied\n");
		else
			ft_printf("%s", "Error: Unable to open file\n");
		return (-1);
	}
	return (fd);
}

void	first_child(pid_t pid[0], char *infile, int fd[2], char cmd1)
{
	pid[0] = fork();
	if (pid[0] < (pid) 0)
	{
		ft_printf("%s", "fork failed");
		return (EXIT_FAILURE);
	}
	infile_fd = open_file(infile, O_RDONLY);
	dup2(infile_fd, STDIN_FILENO);
	close(infile_fd);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[0]);
	close(fd[1]);
	execlp("sh", "sh", "-c", cmd1, NULL);
}

void	last_child(pid_t pid[num_pids], char *outfile, int fd[2], char *cmd_array[nums_pids - 1])
{
	pid[num_pids - 1] = fork();
	if (pid[num_pids - 1] < 0)
	{
		perror("pid2 forking failed");
		return (3);
	}
	if (pid[num_pids - 1] == 0)
	{
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		close(fd[1]);			
		outfile_fd = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0666);
		dup2(outfile_fd, STDOUT_FILENO);
		close(outfile_fd);
		execlp("sh", "sh" "-c", cmd_array[nums_pids - 1], NULL);
	}
}

int	child_process(pid_t pid, int num_pid, int fd[2])
{
	pid[0] = fork();
	if (pid[0] < (pid_t) 0)
	{
		printf("%s", "fork failed");
		return (EXIT_FAILURE);
	}
	
}
/**
This function will init right no of pids based on the no of arguments
**/
pid_t	init_pid_array(int num_pids)
{
	int	i;
	
	i = 1;
	if (num_pids <= 0)
	{
		ft_printf("%s", "invalid ac count");
		return (EXIT_FAILURE);
	}
	pid_t	*pids = malloc(num_pids * sizeof(pid_t));
	if (!pids)
	{
		perror("malloc failed");
		return (EXIT_FAILURE);
	}
	return (pids)
}

int	main(int ac, char **av)
{
	int	fd[2];
	int	infile_fd;
	int	outfile_fd;
	int	no_of_cmds;
	int	i = 0;
	int	j = 2;
	char	*infile;
	char	*outfile;
	char	*cmd1;
	char	*cmd2;
	char	**cmd_array;
	pid_t	pids = NULL:
	
	if (ac >= 5)
	{
		num_pids = ac - 3;
		i = num_pids;
		if (pipe(fd) == -1)
		{
			ft_printf("%s", "pipe failed");
			return (EXIT_FAILURE);
		}
		cmd_array = malloc(sizeof(char) + (nums_pids + 1);
		if (!cmd_array)
			return (NULL);
		
		while (nums_pid > i)
		{
			cmd_array[i++] = ft_strdup(av[j++]);
		}
		cmd_array[i] = 0;
		pids = init_child(num_pids);
		first_child(pids[0], infile, fd[2], cmd_array[0]);
		child_process();
		last_child(pids[nums_pid -1], outfile, fd[2], cmd_array[num_pids - 1]);
		
		close(fd[0]);
		close(fd[1]);
		waitpid(pid1, NULL, 0);
		waitpid(pid2, NULL, 0);
	}	
}

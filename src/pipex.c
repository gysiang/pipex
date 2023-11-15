/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyong-si <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 18:25:50 by gyong-si          #+#    #+#             */
/*   Updated: 2023/11/15 18:22:10 by gyong-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

int	main(int ac, char **av, char **envp)
{
	int	fd[2];
	int	infile_fd;
	int	outfile_fd;
	char	*infile;
	char	*outfile;
	char	*cmd1;
	char	*cmd2;

	if (ac < 5)
	{
		infile = av[1];
		cmd1 = av[2];
		cmd2 = av[3];
		outfile = av[4];
	
		if (pipe(fd) == -1)
			return (1);
		int pid1 = fork();
		if (pid1 < 0)
		{
			perror("pid1 Forking failed");
			return (2);
		}
		if (pid1 == 0)
		{
			infile_fd = open(infile, 0_RDONLY);
			dup2(infile_fd, STDIN_FILENO);
			close(infile_fd);

			dup2(fd[1], STDOUT_FILENO);
			close(fd[0]);
			close(fd[1]);

			execlp("sh", "sh", "-c", cmd1, NULL);
		}
		int pid2 = fork();
		if (pid2 < 0)
		{
			perror("pid2 forking failed");
			return (3);
		}
		if (pid2 == 0)
		{
			dup2(fd[0], STDIN_FILENO);
			close(fd[0]);
			close(fd[1]);
			
			outfile_fd = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0666);
			dup2(outfile_fd, STDOUT_FILENO);
			close(outfile_fd);

			execlp("sh", "sh", "-c",cmd2, NULL);
		}
		close(fd[0]);
		close(fd[1]);
		waitpid(pid1, NULL, 0);
		waitpid(pid2, NULL, 0);
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyong-si <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 18:25:50 by gyong-si          #+#    #+#             */
/*   Updated: 2023/11/28 17:06:31 by gyong-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_utils.h"

/**
int	main(int ac, char **av, char **envp)
{
	if (ac == 4)
	{
		char *infile = av[1];
		char *outfile = av[3];
		int infile_fd = open_file(infile, O_RDONLY, 0666);
		int outfile_fd = open_file(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0666);

		run_command(av[2], infile_fd, outfile_fd, envp);
		close(infile_fd);
		close(outfile_fd);
	}
	return (0);
} **/

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
		while (ac - 2 > i)
		{
			if (pipe(pipe_fd) == -1)
			{
				perror("pipe");
				exit(EXIT_FAILURE);
			}
			run_command(av[i], infile_fd, pipe_fd[1], envp);
			close(infile_fd);
			close(pipe_fd[1]);
			infile_fd = pipe_fd[0];
			i++;
		}
		run_command(av[ac - 2], infile_fd, outfile_fd, envp);
		close(infile_fd);
	}
	return (0);
}

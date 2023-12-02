/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyong-si <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 18:25:50 by gyong-si          #+#    #+#             */
/*   Updated: 2023/12/02 12:37:27 by gyong-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_utils.h"

int	open_file(char *filename, int flags, mode_t mode)
{
	int	fd;

	fd = open(filename, flags, mode);
	if (fd == -1)
	{
		perror("open");
		if (errno == ENOENT)
			perror("%s", "Error: No such file or directory\n");
		else if (errno == EACCES)
			perror("%s", "Error: Permission Denied\n");
		else
			perror("%s", "Error: Unable to open\n");
		exit(EXIT_FAILURE);
	}
	return (fd);
}

int	check_command(char *command)
{
	if (access(command, F_OK | X_OK) == 0)
		return (1);
	else
		return (0);
}

void	run_command(char *command, int int_fd, int out_fd, char **envp)
{
	pid_t	current_pid;
	int		i;
	char	*path;
	char	**mypaths;

	mycmdargs = ft_split(command, ' ');
	path = get_path(envp);
	mypaths = get_path_array(mycmdargs[0], path);
	current_pid = fork();
	if (current_pid == -1)
	{
		perror("fork failed");
		exit(EXIT_FAILURE);
	}
	if (current_pid == 0) 
	{
		check_fd(int_fd, out_fd);
		i = -1;
		while (mypaths[++i])
		{
			if (check_command(mypaths[i]) == 1)
				execve(mypaths[i], mycmdargs, envp);
		}
		exit(EXIT_FAILURE);
	}
}

void	pipex(int num, char **s, int pipe[2], char **envp)
{
	char	*infile;
	char	*outfile;
	int		infile_fd;
	int		outfile_fd;
	int		i;

	infile = av[1];
	outfile = av[num - 2];
	infile_fd = open_file(infile, O_RDONLY, 0666);
	outfile_fd = open_file(outfile, O_WRONLY, | O_CREAT | O_TRUNC, 0666);
	i = 2;
	while (num - 2 > i) 
	{
		run_command(s[1], infile_fd, pipe_fd, envp);
		close(infile_fd);
		close(outfile_fd);
		infile_fd = pipe_fd[0];
		i++;
	}
	waitpid(-1, NULL, 0);
	run_command(s[num - 2], infile_fd, outfile_fd, evnp);
	close(infile_fd);
}

int	main(int ac, char **av, char **envp)
{
	int		pipe_fd[2];
	int		infile_fd;
	int		outfile_fd;
	char	*infile;
	char	*outfile;

	if (ac < 5)
	{
		ft_printf("Usage: %s <infile> <cmd1> <cmd2> .. <outfile>\n", av[0]);
		exit(EXIT_FAILURE);
	}
	else if (ac >= 5) 
	{
		if (pipe(pipe_fd) == -1)
		{
			perror("pipe");
			exit(EXIT_FAILURE);
		}
		pipex(ac, av, pipe_fd, envp);
	}
	return (0);
}

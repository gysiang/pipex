/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyong-si <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 18:25:50 by gyong-si          #+#    #+#             */
/*   Updated: 2023/12/04 13:43:46 by gyong-si         ###   ########.fr       */
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
			perror("Error: No such file or directory\n");
		else if (errno == EACCES)
			perror("Error: Permission Denied\n");
		else
			perror("Error: Unable to open\n");
		exit(EXIT_FAILURE);
	}
	return (fd);
}

void	handle_child_process(pid_t child_pid, char **mypaths, char **mycmdargs)
{
	int	status;

	waitpid(child_pid, &status, 0);
	ft_free_array(mypaths);
	ft_free_array(mycmdargs);
	if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
	{
		ft_putstr_fd("Child process failed", 2);
		exit(EXIT_FAILURE);
	}
}

void	run_command(char *command, int int_fd, int out_fd, char **envp)
{
	pid_t	current_pid;
	int		i;
	char	*path;
	char	**mypaths;
	char	**mycmdargs;

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
			if (access(mypaths[i], F_OK | X_OK) == 0)
				execve(mypaths[i], mycmdargs, envp);
		}
		exit(EXIT_FAILURE);
	}
	else
		handle_child_process(current_pid, mypaths, mycmdargs);
}

void	pipex(int num, char **s, int pipes_fd[2], char **envp)
{
	char	*infile;
	char	*outfile;
	int		infile_fd;
	int		outfile_fd;
	int		i;

	infile = s[1];
	outfile = s[num - 1];
	infile_fd = open_file(infile, O_RDONLY, 0666);
	outfile_fd = open_file(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	i = 2;
	while (num - 2 > i) 
	{
		run_command(s[i], infile_fd, pipes_fd[1], envp);
		close(infile_fd);
		close(pipes_fd[1]);
		infile_fd = pipes_fd[0];
		i++;
	}
	waitpid(-1, NULL, 0);
	run_command(s[num - 2], infile_fd, outfile_fd, envp);
	close(infile_fd);
}

int	main(int ac, char **av, char **envp)
{
	int		pipe_fd[2];

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

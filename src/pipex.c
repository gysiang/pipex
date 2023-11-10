/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyong-si <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 18:25:50 by gyong-si          #+#    #+#             */
/*   Updated: 2023/11/10 17:50:30 by gyong-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int	main(int ac, char **av, char **envp)
{
	int	fd[2];

	if (ac < 5)
	{
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
			dup2(fd[1], STDOUT_FILENO);
			close(fd[0]);
			close(fd[1]);
			execlp("ping", "ping", "-c", "5", "google.com", NULL);
		}
		int pid2 = fork();
		if (pid2 < 0)
		{
			perror("pid2 forking failed");
			return (3);
		}
		if (pid2 == 0)
		{
			dup2(fd[0], STDINT_FILENO);
			close(fd[0]);
			close(fd[1]);
			execlp("grep", "grep", "rtt", NULL);
		}
		close(fd[0]);
		close(fd[1]);
		waitpid(pid1, NULL, 0);
		waitpid(pid2, NULL, 0);
	}
	return (0);
}

/**
ft_init_pipex();
ft_check_args();
ft_parse_cmd();
ft_parse_args()
while (cmd)
	ft_exec();
ft_cleanup();
**/

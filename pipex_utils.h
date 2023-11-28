/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyong-si <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 17:21:51 by gyong-si          #+#    #+#             */
/*   Updated: 2023/11/28 17:26:23 by gyong-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_UTILS_H
# define PIPEX_UTILS_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <errno.h>
#include "ft_printf/ft_printf.h"
#include "ft_printf/libft/libft.h"

char	*add_slash(char *s);
int		open_file(char *filename, int flags, mode_t mode);
char		**get_path(char *cmd, char **array);
void		run_command(char *command, int	int_fd, int out_fd, char **envp);

#endif

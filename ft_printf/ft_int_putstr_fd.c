/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_int_putstr_fd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyong-si <gyongsi@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 09:55:47 by gyong-si          #+#    #+#             */
/*   Updated: 2023/09/29 16:08:46 by gyong-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_int_putstr_fd(char *s, int fd)
{
	int	len;

	if (!s)
	{
		ft_putstr_fd("(null)", fd);
		return (6);
	}
	len = ft_strlen(s);
	write(fd, s, len);
	return (len);
}

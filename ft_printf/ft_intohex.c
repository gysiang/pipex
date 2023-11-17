/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_intohex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyong-si <gyongsi@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 09:59:07 by gyong-si          #+#    #+#             */
/*   Updated: 2023/10/02 16:53:14 by gyong-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_intohex(unsigned int s, char *base)
{
	unsigned int	c;
	int				i;
	int				len;
	char			hex[16];

	len = 0;
	i = 15;
	c = (unsigned int)s;
	if (c == 0)
		return (ft_int_putchar_fd('0', 1));
	while (c > 0)
	{
		hex[i] = base[c % 16];
		c /= 16;
		i--;
		len++;
	}
	while (i < 15)
	{
		i++;
		ft_putchar_fd(hex[i], 1);
	}
	return (len);
}

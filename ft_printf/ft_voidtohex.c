/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_voidtohex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyong-si <gyongsi@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 09:58:41 by gyong-si          #+#    #+#             */
/*   Updated: 2023/10/02 16:51:19 by gyong-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_voidtohex(void *p)
{
	unsigned long long	addr;
	int					i;
	int					len;
	char				hex[16];

	len = 0;
	i = 0;
	addr = (unsigned long long)p;
	if (!addr)
		return (ft_int_putstr_fd("(nil)", 1));
	while (addr > 0)
	{
		hex[i] = "0123456789abcdef"[addr % 16];
		addr /= 16;
		len++;
		i++;
	}
	ft_putstr_fd("0x", 1);
	while (i > 0)
	{
		i--;
		ft_putchar_fd(hex[i], 1);
	}
	return (len + 2);
}

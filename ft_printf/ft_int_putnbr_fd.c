/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_int_putnbr_fd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyong-si <gyongsi@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 09:56:29 by gyong-si          #+#    #+#             */
/*   Updated: 2023/09/29 16:20:47 by gyong-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_int_putnbr_fd(int n)
{
	int		len;
	char	*num;

	len = 0;
	num = ft_itoa(n);
	len += ft_int_putstr_fd(num, 1);
	free(num);
	return (len);
}

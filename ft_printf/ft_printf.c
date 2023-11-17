/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyong-si <gyongsi@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 14:11:08 by gyong-si          #+#    #+#             */
/*   Updated: 2023/09/29 14:32:02 by gyong-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_format(va_list args, char format)
{
	int	len;

	len = 0;
	if (format == 'c')
		len += ft_int_putchar_fd(va_arg(args, int), 1);
	else if (format == 's')
		len += ft_int_putstr_fd(va_arg(args, char *), 1);
	else if (format == 'p')
		len += ft_voidtohex(va_arg(args, void *));
	else if (format == 'd' || format == 'i')
		len += ft_int_putnbr_fd(va_arg(args, int));
	else if (format == 'u')
		len += ft_putnbr_unsigned((unsigned int)va_arg(args, int));
	else if (format == 'x')
		len += ft_intohex((unsigned int)va_arg(args, int), "0123456789abcdef");
	else if (format == 'X')
		len += ft_intohex((unsigned int)va_arg(args, int), "0123456789ABCDEF");
	else if (format == '%')
		len += ft_int_putchar_fd('%', 1);
	else
		return (-1);
	return (len);
}

int	ft_printf(const char *s, ...)
{
	int		i;
	int		printed_len;
	va_list	args;

	i = 0;
	printed_len = 0;
	va_start(args, s);
	while (s[i] != '\0')
	{
		if (s[i] != '%')
		{
			ft_putchar_fd(s[i], 1);
			printed_len++;
		}
		else
		{
			i++;
			if (s[i] != '\0')
				printed_len += ft_format(args, s[i]);
		}
		i++;
	}
	va_end(args);
	return (printed_len);
}

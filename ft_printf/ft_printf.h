/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyong-si <gyongsi@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 00:28:51 by gyong-si          #+#    #+#             */
/*   Updated: 2023/09/29 14:29:43 by gyong-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include "libft/libft.h"

int	ft_printf(const char *s, ...);
int	ft_int_putchar_fd(char c, int fd);
int	ft_int_putstr_fd(char *s, int fd);
int	ft_int_putnbr_fd(int n);
int	ft_putnbr_unsigned(unsigned int n);
int	ft_numlen(long num);
int	ft_voidtohex(void *p);
int	ft_intohex(unsigned int s, char *base);

#endif

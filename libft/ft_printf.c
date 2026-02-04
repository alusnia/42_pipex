/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alusnia <alusnia@student.42Warsaw.pl>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 15:10:33 by alusnia           #+#    #+#             */
/*   Updated: 2025/10/29 15:45:13 by alusnia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	rec_arg(char c, va_list p)
{
	if (c == 'c')
		return (ft_putchar_fd(va_arg(p, int), 1), 1);
	else if (c == 's')
		return (ft_putstr_fd(va_arg(p, char *), 1));
	else if (c == 'p')
		return (ft_putptr_fd(va_arg(p, void *), 1));
	else if (c == 'd' || c == 'i')
		return (ft_putnbr_fd(va_arg(p, int), 1));
	else if (c == 'u')
		return (ft_putunbr_fd(va_arg(p, unsigned int), 1));
	else if (c == 'x')
		return (ft_puthex_fd(va_arg(p, unsigned int), 1, 0));
	else if (c == 'X')
		return (ft_puthex_fd(va_arg(p, unsigned int), 1, 1));
	else if (c == '%')
		return (ft_putchar_fd('%', 1), 1);
	return (0);
}

int	ft_printf(const char *str, ...)
{
	int		count;
	va_list	p;

	count = 0;
	va_start(p, str);
	while (*str)
	{
		if (*str == '%' && str[1])
		{
			str++;
			count += rec_arg(*str, p);
		}
		else
		{
			ft_putchar_fd(*str, 1);
			count++;
		}
		str++;
	}
	va_end(p);
	return (count);
}

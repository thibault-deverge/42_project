/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeverge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 16:14:46 by tdeverge          #+#    #+#             */
/*   Updated: 2022/11/14 18:08:40 by tdeverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/libft.h"

int	ft_printf(const char *format, ...)
{
	va_list			args;
	unsigned int	len;
	unsigned int	i;

	i = 0;
	len = 0;
	va_start(args, format);
	while (format[i])
	{
		while (format[i] && format[i] != '%')
			i += ft_putchar_ui(format[i]);
		if (format[i] && format[i] == '%')
		{
			len += ft_check_specifier(args, format[i + 1]);
			len -= 2;
			i += 2;
		}
	}
	va_end(args);
	return (i + len);
}

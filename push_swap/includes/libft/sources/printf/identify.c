/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   identify.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeverge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 15:21:09 by tdeverge          #+#    #+#             */
/*   Updated: 2022/11/14 18:37:37 by tdeverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/libft.h"

static unsigned int	ft_handle_char(va_list arg, char specifier)
{
	unsigned int	len;
	char			*str;
	char			c;

	if (specifier == '%' || specifier == 'c')
	{
		if (specifier == '%')
			len = ft_putchar_ui(specifier);
		else
		{
			c = va_arg(arg, int);
			len = ft_putchar_ui(c);
		}
	}
	else
	{
		str = va_arg(arg, char *);
		len = ft_putstr_ui(str);
	}
	return (len);
}

static unsigned int	ft_handle_ui(va_list arg, char specifier)
{
	unsigned int	num;
	unsigned int	len;

	num = va_arg(arg, unsigned int);
	len = 0;
	if (specifier == 'u')
	{
		len = ft_ull_len_base(num, "0123456789");
		ft_putull_base(num, "0123456789");
	}
	else if (specifier == 'x')
	{
		len = ft_ull_len_base(num, "0123456789abcdef");
		ft_putull_base(num, "0123456789abcdef");
	}
	else if (specifier == 'X')
	{
		len = ft_ull_len_base(num, "0123456789ABCDEF");
		ft_putull_base(num, "0123456789ABCDEF");
	}
	return (len);
}

static unsigned int	ft_handle_int(va_list arg)
{	
	int		num;
	int		len;

	num = va_arg(arg, int);
	len = ft_countdigits(num);
	ft_putnbr(num);
	return (len);
}

static unsigned int	ft_handle_address(va_list arg)
{
	unsigned long long	num;
	unsigned int		len;

	num = va_arg(arg, unsigned long long);
	if (num == 0)
	{
		len = ft_putstr_ui("(nil)");
		return (len);
	}
	len = ft_putstr_ui("0x");
	len += ft_ull_len_base(num, "0123456789abcdef");
	ft_putull_base(num, "0123456789abcdef");
	return (len);
}

size_t	ft_check_specifier(va_list arg, char specifier)
{
	unsigned int	len;

	len = 0;
	if (specifier == '%' || specifier == 'c' || specifier == 's')
		len += ft_handle_char(arg, specifier);
	else if (specifier == 'u' || specifier == 'x' || specifier == 'X')
		len += ft_handle_ui(arg, specifier);
	else if (specifier == 'd' || specifier == 'i')
		len += ft_handle_int(arg);
	else if (specifier == 'p')
		len += ft_handle_address(arg);
	else
	{
		len += ft_putchar_ui('%');
		len += ft_putchar_ui(specifier);
	}
	return (len);
}

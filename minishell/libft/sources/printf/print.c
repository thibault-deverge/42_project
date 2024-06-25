/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeverge <tdeverge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 17:24:30 by tdeverge          #+#    #+#             */
/*   Updated: 2022/11/14 18:37:53 by tdeverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/libft.h"

size_t	ft_putchar_ui(char c)
{
	write(1, &c, 1);
	return (1);
}

size_t	ft_putstr_ui(char *str)
{
	int	len;

	len = 0;
	if (!str)
	{
		len = ft_putstr_ui("(null)");
		return (len);
	}
	while (str[len])
		len += ft_putchar_ui(str[len]);
	return (len);
}

void	ft_putnbr(int n)
{
	long int	n_long;

	n_long = n;
	if (n_long < 0)
	{
		ft_putchar_ui('-');
		n_long *= -1;
	}
	if (n_long < 10)
		ft_putchar_ui(n_long + '0');
	else
	{
		ft_putnbr(n_long / 10);
		ft_putchar_ui(n_long % 10 + '0');
	}
}

void	ft_putull_base(unsigned long int n, char *base)
{
	unsigned int	base_len;

	base_len = ft_strlen(base);
	if (n < base_len)
	{
		ft_putchar_ui(base[n % base_len]);
		return ;
	}
	ft_putull_base(n / base_len, base);
	ft_putchar_ui(base[n % base_len]);
}

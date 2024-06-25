/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeverge <tdeverge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 01:12:22 by tdeverge          #+#    #+#             */
/*   Updated: 2022/10/16 17:06:42 by tdeverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/libftprintf.h"

unsigned int	ft_strlen(char *str)
{
	int		len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}

unsigned int	ft_countdigits(long int n)
{
	long int	n_long;
	int			nb_digits;

	nb_digits = 1;
	n_long = n;
	if (n_long < 0)
	{
		n_long *= -1;
		nb_digits++;
	}
	while (n_long > 9)
	{
		nb_digits++;
		n_long /= 10;
	}
	return (nb_digits);
}

unsigned int	ft_ull_len_base(unsigned long int n, char *base)
{
	unsigned int	len;
	unsigned int	base_len;

	len = 0;
	base_len = ft_strlen(base);
	while (n >= base_len)
	{
		n /= base_len;
		len++;
	}
	len++;
	return (len);
}

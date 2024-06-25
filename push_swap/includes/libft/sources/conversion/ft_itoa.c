/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeverge <tdeverge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 18:00:32 by tdeverge          #+#    #+#             */
/*   Updated: 2022/11/13 17:17:29 by tdeverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/libft.h"

static size_t	count_digits(long int n)
{
	int	nb_digits;

	nb_digits = 1;
	if (n < 0)
	{
		n *= -1;
		nb_digits++;
	}
	while (n > 9)
	{
		nb_digits++;
		n /= 10;
	}
	return (nb_digits);
}

char	*ft_itoa(int n)
{
	size_t		str_len;
	size_t		is_neg;
	long int	n_long;
	char		*str;

	n_long = n;
	is_neg = 0;
	str_len = count_digits(n_long);
	str = (char *)malloc(sizeof(char) * (str_len + 1));
	if (!str)
		return (NULL);
	str[str_len] = '\0';
	if (n_long < 0)
	{
		is_neg = 1;
		n_long *= -1;
	}
	while (str_len-- > 0)
	{
		str[str_len] = (n_long % 10) + '0';
		n_long /= 10;
	}
	if (is_neg)
		str[0] = '-';
	return (str);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_rule.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeverge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 12:34:47 by tdeverge          #+#    #+#             */
/*   Updated: 2023/03/05 13:18:54 by tdeverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static int	ft_is_whitespace(char c);
static int	ft_is_digit(char c);

/*
 * @summary:
 * 		- Atoi modified to return an error if there is non-digit character
 * 		at any place in the string (other than '+') or if number is negative.
*/
int	ft_atoi_rule(const char *nptr)
{
	long long int	sum;
	size_t			i;

	i = 0;
	sum = 0;
	while (ft_is_whitespace(nptr[i]))
		i++;
	if (nptr[i] == '+')
		i++;
	if (!ft_is_digit(nptr[i]))
		return (-1);
	while (ft_is_digit(nptr[i]))
	{
		sum = (sum * 10) + (nptr[i] - '0');
		i++;
	}
	if (nptr[i] || sum > INT_MAX || sum < 0)
		return (-1);
	return (sum);
}

static int	ft_is_digit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

static int	ft_is_whitespace(char c)
{
	if (c == ' ' || (c >= 9 && c <= 13))
		return (1);
	return (0);
}

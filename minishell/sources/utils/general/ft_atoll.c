/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoll.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeverge <tdeverge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 01:00:13 by tdeverge          #+#    #+#             */
/*   Updated: 2023/02/13 01:09:31 by tdeverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <limits.h>

/*
 * @summary:
 * 		- Convert string received as parameter to a long long int
 * 		and return it.
*/
long long	ft_atoll(const char *nptr, int *limits)
{
	unsigned long long		sum;
	size_t					is_neg;
	size_t					i;

	i = 0;
	sum = 0;
	is_neg = 0;
	while (ft_is_whitespace(nptr[i]))
		i++;
	if (nptr[i] == '-')
		is_neg = 1;
	if (nptr[i] == '-' || nptr[i] == '+')
		i++;
	while (ft_isdigit(nptr[i]))
	{
		sum = (sum * 10) + (nptr[i] - '0');
		i++;
	}
	if ((is_neg && sum > 9223372036854775808ULL)
		|| (!is_neg && sum > LLONG_MAX))
		*limits = 1;
	if (is_neg)
		return ((sum * -1) % 256);
	return (sum % 256);
}

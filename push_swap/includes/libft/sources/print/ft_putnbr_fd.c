/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeverge <tdeverge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 22:25:39 by tdeverge          #+#    #+#             */
/*   Updated: 2022/11/13 17:27:35 by tdeverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	long int	n_long;

	n_long = n;
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		n_long *= (-1);
	}
	if (n_long < 10)
		ft_putchar_fd(n_long + '0', fd);
	else
	{
		ft_putnbr_fd(n_long / 10, fd);
		ft_putchar_fd(n_long % 10 + '0', fd);
	}
}

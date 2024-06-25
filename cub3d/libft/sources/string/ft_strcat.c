/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeverge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 15:30:07 by tdeverge          #+#    #+#             */
/*   Updated: 2023/03/24 15:46:39 by tdeverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/libft.h"

char	*ft_strcat(char *dest_str, char *src_str)
{
	int	dest_len;
	int	i;

	i = 0;
	dest_len = ft_strlen(dest_str);
	while (src_str[i])
	{
		dest_str[dest_len + i] = src_str[i];
		i++;
	}
	dest_str[dest_len + i] = '\0';
	return (dest_str);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeverge <tdeverge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 20:03:24 by tdeverge          #+#    #+#             */
/*   Updated: 2022/11/14 21:00:04 by tdeverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/libft.h"

#define INT_MAX 2147483647

void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t	i;
	void	*pt_memory;

	if (nmemb * size > INT_MAX || size > INT_MAX)
		return (NULL);
	pt_memory = malloc(nmemb * size);
	if (!pt_memory)
		return (NULL);
	i = 0;
	while (i < nmemb * size)
	{
		((char *)pt_memory)[i] = 0;
		i++;
	}
	return (pt_memory);
}

char	*add_to_stock(char *stock, char *buffer)
{
	char	*new_stock;
	size_t	total_len;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	total_len = str_len(stock) + str_len(buffer);
	new_stock = (char *)ft_calloc(1, total_len + 2);
	if (!new_stock)
		return (NULL);
	while (stock[i])
	{
		new_stock[i] = stock[i];
		i++;
	}
	while (buffer[j])
	{
		new_stock[i] = buffer[j];
		i++;
		j++;
	}
	new_stock[i] = '\0';
	return (new_stock);
}

size_t	search_newline(char *stock)
{
	size_t	i;

	i = 0;
	while (stock && stock[i])
	{
		if (stock[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

size_t	str_len(char *str)
{
	size_t	len;

	len = 0;
	while (str && str[len] != '\0')
		len++;
	return (len);
}

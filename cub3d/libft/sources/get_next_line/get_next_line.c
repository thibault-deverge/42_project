/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeverge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 18:10:02 by tdeverge          #+#    #+#             */
/*   Updated: 2023/03/29 23:51:09 by tdeverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/libft.h"

/*
 * @summary 
 *		- Read a file via its file descriptor 'fd' and return the first one found.
 *		- It first reads the file until it found a new line, extracts the line and
 *		update stock to keep trace of the characters read after the line.
 * @params: fd -> file descriptor of the file
 * @return: line -> the first line reads in the file
*/
char	*get_next_line(int fd)
{
	static char	*stock[1024];	
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd > 1024)
		return (NULL);
	stock[fd] = read_file(stock[fd], fd);
	if (!stock[fd])
		return (NULL);
	line = extract_line(stock[fd]);
	stock[fd] = update_stock(stock[fd]);
	if (!stock[fd])
		free(stock[fd]);
	return (line);
}

/*
 * @summary: Extract until it found a '\n' or EOF from the 'stock' variable.
 * @params: stock -> the static variable who keeps trace of the characters read.
 * @return: line -> the line extract.
*/
char	*extract_line(char *stock)
{
	char	*line;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (stock[i] && stock[i] != '\n')
		i++;
	i++;
	line = (char *)ft_calloc(1, i + 1);
	if (!line)
		return (NULL);
	while (j < i)
	{
		line[j] = stock[j];
		j++;
	}
	line[j] = '\0';
	return (line);
}

/*
 * @summary: Reallocate the 'stock' variable to fit its new size without the line
 * @params: stock -> the static variable who keeps trace of the characters read.
 * @return: new_stock -> the stock updated to fit its content.
*/
char	*update_stock(char *stock)
{
	char	*new_stock;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (stock[i] && stock[i] != '\n')
		i++;
	new_stock = (char *)ft_calloc(1, str_len(stock) - i + 1);
	if (!new_stock)
		return (NULL);
	i++;
	while (stock[i])
		new_stock[j++] = stock[i++];
	new_stock[j] = '\0';
	free(stock);
	if (new_stock[0] == '\0')
	{
		free(new_stock);
		new_stock = NULL;
	}
	return (new_stock);
}

/*
 * @summary: read file on a loop until it found a new line character.
 * @params:	stock -> the static variable who keeps trace of the character read.
 * 			fd	  -> the file descriptor of the file read.
 * @return: stock -> the 'stock' updated with the content read.
*/
char	*read_file(char *stock, int fd)
{
	char	*buffer;
	int		count_read;

	count_read = 1;
	buffer = (char *)ft_calloc(1, BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	while (!search_newline(stock) && count_read != 0)
	{	
		count_read = read(fd, buffer, BUFFER_SIZE);
		if (count_read <= 0)
		{
			free(buffer);
			return (stock);
		}
		buffer[count_read] = 0;
		stock = save_buffer(stock, buffer);
	}
	free(buffer);
	return (stock);
}

/*
 * @summary: add buffer to stock every time it reads on the file.
 * @params:	stock  -> the variable who keeps trace of all the characters reads.
 * 			buffer -> the place where last read characteris are stored.
 * @stock:  stock  -> the 'stock' updated with the buffer.
*/
char	*save_buffer(char *stock, char *buffer)
{
	char	*new_stock;

	if (!stock)
	{
		stock = (char *)malloc(1);
		if (!stock)
			return (NULL);
		stock[0] = '\0';
	}
	new_stock = add_to_stock(stock, buffer);
	free(stock);
	return (new_stock);
}

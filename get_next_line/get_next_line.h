/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeverge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 18:10:18 by tdeverge          #+#    #+#             */
/*   Updated: 2022/10/24 17:30:50 by tdeverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 4
# endif

char	*get_next_line(int fd);
char	*read_file(char *stock, int fd);
char	*save_buffer(char *stock, char *buffer);
char	*extract_line(char *stock);
char	*update_stock(char	*stock);
char	*add_to_stock(char *stock, char *buffer);
void	*ft_calloc(size_t nmemb, size_t size);
size_t	search_newline(char *stock);
size_t	str_len(char *str);

#endif

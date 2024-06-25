/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeverge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 14:33:42 by tdeverge          #+#    #+#             */
/*   Updated: 2023/04/18 13:13:28 by tdeverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

typedef struct s_link
{
	char			*content;
	struct s_link	*next;
}	t_link;

typedef struct s_list
{
	int		size;
	t_link	*first;
}	t_list;

int		ft_atoi(const char *nptr);
void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t nmemb, size_t size);
int		ft_is_all_whitespace(char *str);
int		ft_is_whitespace(char c);
int		ft_isalnum(int c);
int		ft_isalpha(int c);
int		ft_isascii(int c);
int		ft_isdigit(int c);
int		ft_isprint(int c);
char	*ft_itoa(int n);
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t n);
void	*ft_memset(void *s, int c, size_t n);
char	**ft_split(char const *s, char c);
char	*ft_strchr(const char *s, int c);
char	*ft_strdup(const char*s);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strjoin_safe(char *s1, char *s2);
char	*ft_strcat(char *dest_str, char *src_str);
size_t	ft_strlcat(char *dest, const char *src, size_t size);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
size_t	ft_strlen(const char *s);
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int		ft_strcmp(const char *s1, const char *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strnstr(const char *big, const char *little, size_t len);
char	*ft_strrchr(const char *s, int c);
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_substr(char const *s, unsigned int start, size_t len);
int		ft_tolower(int c);
int		ft_toupper(int c);
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
int		ft_printf(const char *format, ...);
size_t	ft_check_specifier(va_list args, char specifier);
size_t	ft_countdigits(long int n);
size_t	ft_ull_len_base(unsigned long int n, char *base);
size_t	ft_putchar_ui(char c);
size_t	ft_putstr_ui(char *str);
void	ft_putnbr(int n);
void	ft_putull_base(unsigned long int n, char *base);
char	*get_next_line(int fd);
char	*ft_get_line(int fd);
char	*read_file(char *stock, int fd);
char	*save_buffer(char *stock, char *buffer);
char	*extract_line(char *stock);
char	*update_stock(char *stock);
char	*add_to_stock(char *stock, char *buffer);
void	*ft_calloc(size_t nmemb, size_t size);
size_t	search_newline(char *stock);
size_t	str_len(char *str);

#endif

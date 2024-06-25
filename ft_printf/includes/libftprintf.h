/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeverge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 16:17:59 by tdeverge          #+#    #+#             */
/*   Updated: 2022/10/16 01:30:16 by tdeverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef LIBFTPRINTF_H
# define LIBFTPRINTF_H

# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>

int				ft_printf(const char *format, ...);
unsigned int	ft_check_specifier(va_list args, char specifier);
unsigned int	ft_strlen(char *str);
unsigned int	ft_countdigits(long int n);
unsigned int	ft_ull_len_base(unsigned long int n, char *base);
unsigned int	ft_putchar_ui(char c);
unsigned int	ft_putstr_ui(char *str);
void			ft_putnbr(int n);
void			ft_putull_base(unsigned long int n, char *base);

#endif

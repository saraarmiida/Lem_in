/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_hex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spentti <spentti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 11:55:50 by spentti           #+#    #+#             */
/*   Updated: 2020/01/30 16:16:17 by spentti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	get_length(unsigned long long *num, va_list ap, t_menu *menu)
{
	if (menu->length == 0)
		*num = (unsigned int)va_arg(ap, unsigned int);
	else if (menu->length == 1)
		*num = (unsigned char)va_arg(ap, unsigned int);
	else if (menu->length == 2)
		*num = (unsigned short)va_arg(ap, unsigned int);
	else if (menu->length == 3)
		*num = (unsigned long long)va_arg(ap, unsigned long long);
	else if (menu->length == 4)
		*num = (unsigned long)va_arg(ap, unsigned long);
}

void	get_width(t_menu *menu, char **s)
{
	char	c;
	int		n;
	char	*temp;

	if (menu->width && menu->width > (int)ft_strlen(*s))
	{
		c = ' ';
		if (menu->minus == 0 && menu->zero != 0 && menu->precision == -1)
			c = '0';
		n = menu->width - ft_strlen(*s);
		if (menu->precision != -1 && menu->precision > (int)ft_strlen(*s))
			n = menu->width - menu->precision;
		temp = ft_memset(ft_strnew(n), c, n);
		if (menu->minus == 0)
			*s = join_free(temp, *s);
		else if (menu->minus == 1)
			*s = join_free(*s, temp);
	}
}

char	*hex_modifiers(t_menu *menu, char *s, unsigned long long num)
{
	char	*temp;
	int		n;

	if (menu->precision != -1 && menu->precision > (int)ft_strlen(s))
	{
		n = menu->precision - ft_strlen(s);
		temp = ft_memset(ft_strnew(n), '0', n);
		s = join_free(temp, s);
	}
	if (num == 0 && menu->precision == 0)
		s = ft_memset(ft_strnew(0), '0', 0);
	if (menu->hash == 1 && !(menu->width != 0 && menu->zero\
	!= 0 && menu->precision == -1 && menu->minus == 0) && num != 0)
	{
		temp = ft_strdup("0x");
		s = join_free(temp, s);
	}
	if (menu->width && menu->width > (int)ft_strlen(s))
		get_width(menu, &s);
	if (menu->hash == 1 && (menu->width != 0 && menu->zero\
	!= 0 && menu->precision == -1))
		s[1] = 'x';
	return (s);
}

void	c_hex(t_menu *menu, va_list ap, char **str, char x)
{
	int					n;
	char				*s;
	unsigned long long	integer;

	if (menu->width == -2)
		menu->width = (int)va_arg(ap, int);
	if (menu->precision == -2)
		menu->precision = (int)va_arg(ap, int);
	get_length(&integer, ap, menu);
	if (integer < 0)
		integer = 4294967296 + integer;
	s = ft_itoa_base(integer, 16);
	s = hex_modifiers(menu, s, integer);
	if (x == 'X')
	{
		n = 0;
		while (s[n] != '\0')
		{
			s[n] = ft_toupper(s[n]);
			n++;
		}
	}
	*str = ft_strdup(s);
	free(s);
}

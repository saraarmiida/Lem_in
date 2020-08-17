/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_binary.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spentti <spentti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/31 17:49:32 by spentti           #+#    #+#             */
/*   Updated: 2020/01/31 18:08:17 by spentti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

char	*bin_modifiers(t_menu *menu, char *s, unsigned long long num)
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

void	c_binary(t_menu *menu, va_list ap, char **str, char x)
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
	s = ft_itoa_base(integer, 2);
	s = bin_modifiers(menu, s, integer);
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

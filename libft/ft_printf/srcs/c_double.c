/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_double.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spentti <spentti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 13:01:25 by spentti           #+#    #+#             */
/*   Updated: 2020/01/30 16:26:19 by spentti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	double_plus(t_menu *menu, char **s, long double num)
{
	char	*temp;

	if ((menu->plus || menu->space) && num >= 0)
	{
		temp = ft_memset(ft_strnew(1), (menu->plus == 1 ? '+' : ' '), 1);
		*s = join_free(temp, *s);
	}
}

void	double_width(t_menu *menu, char **s, long double num)
{
	char	*str;
	char	*str2;
	char	c;
	int		n;

	c = (menu->minus == 0 && menu->zero != 0 ? '0' : ' ');
	n = menu->width - ft_strlen(*s);
	str = ft_memset(ft_strnew(n), c, n);
	str2 = (menu->minus == 0 ? join_free(str, *s) : join_free(*s, str));
	if (menu->zero != 0 && menu->minus == 0)
	{
		if (((menu->plus == 1 || menu->space == 1) && num >= 0) || num < 0)
		{
			if ((menu->plus == 1 || menu->space == 1) && num >= 0)
				c = (menu->plus == 0 ? ' ' : '+');
			else if (num < 0)
				c = '-';
			str2[0] = c;
			str2[n] = '0';
		}
	}
	*s = str2;
}

void	c_double(t_menu *menu, va_list ap, char **str)
{
	char		*s;
	long double	num;

	if (menu->width == -2)
		menu->width = (int)va_arg(ap, int);
	if (menu->precision == -2)
		menu->precision = (int)va_arg(ap, int);
	if (menu->length == 5)
		num = (long double)va_arg(ap, long double);
	else
		num = (long double)va_arg(ap, double);
	menu->precision = (menu->precision == -1 ? 6 : menu->precision);
	s = ft_ftoa(num, menu->precision, menu->hash);
	double_plus(menu, &s, num);
	if (menu->width > (int)ft_strlen(s))
		double_width(menu, &s, num);
	*str = ft_strdup(s);
	free(s);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_int.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spentti <spentti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 13:37:31 by spentti           #+#    #+#             */
/*   Updated: 2020/01/30 16:34:14 by spentti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	get_int_length(long long *integer, va_list ap, t_menu *menu)
{
	if (menu->length == 0)
		*integer = (int)va_arg(ap, int);
	else if (menu->length == 1)
		*integer = (signed char)va_arg(ap, int);
	else if (menu->length == 2)
		*integer = (short)va_arg(ap, int);
	else if (menu->length == 3)
		*integer = (unsigned long long)va_arg(ap, unsigned long long);
	else if (menu->length == 4)
		*integer = (long)va_arg(ap, long);
}

void	int_precision(int precision, char **s, long long num, int n)
{
	char	*temp;
	char	*temp2;

	if (precision != -1 && precision > ((int)ft_strlen(*s) - (num < 0 ? 1 : 0)))
	{
		if (num < 0)
		{
			temp = ft_memset(ft_strnew(n + 2), '0', n + 2);
			temp[0] = '-';
			temp2 = ft_strjoin(temp, *s + 1);
			free(temp);
			free(*s);
			*s = temp2;
		}
		else
		{
			temp = ft_memset(ft_strnew(n), '0', n);
			*s = join_free(temp, *s);
		}
	}
	if (precision == 0 && num == 0)
	{
		free(*s);
		*s = ft_strnew(0);
	}
}

void	int_plus(t_menu *menu, char **s, long long integer)
{
	char	*temp;
	char	*temp2;

	if ((menu->plus || menu->space) && integer >= 0)
	{
		temp2 = (menu->plus == 1 ? "+" : " ");
		temp = ft_strjoin(temp2, *s);
		free(*s);
		*s = temp;
	}
}

void	int_width(t_menu *menu, char **s, long long integer)
{
	char	*temp;
	char	*temp2;
	char	c;
	int		n;

	c = ' ';
	if (menu->minus == 0 && menu->zero != 0 && menu->precision == -1)
		c = '0';
	n = menu->width - ft_strlen(*s);
	if (menu->precision != -1 && menu->precision > (int)ft_strlen(*s))
		n = menu->width - menu->precision;
	temp = ft_memset(ft_strnew(n), c, n);
	temp2 = (menu->minus == 0 ? ft_strjoin(temp, *s) : ft_strjoin(*s, temp));
	free(temp);
	free(*s);
	*s = temp2;
	if (c == '0' && (integer < 0 || (menu->plus == 1 && integer >= 0)))
	{
		temp = *s;
		temp[0] = (integer < 0 ? '-' : '+');
		temp[n] = '0';
		*s = temp;
	}
}

void	c_integer(t_menu *menu, va_list ap, char **str)
{
	char			*s;
	long long		integer;

	if (menu->width == -2)
		menu->width = (int)va_arg(ap, int);
	if (menu->precision == -2)
		menu->precision = (int)va_arg(ap, int);
	get_int_length(&integer, ap, menu);
	if (integer < -9223372036854775807)
		s = ft_strdup("-9223372036854775808");
	else
	{
		if (menu->length == 3)
			integer = (long long)integer;
		s = ft_itoa(integer);
	}
	int_precision(menu->precision, &s, integer, menu->precision - ft_strlen(s));
	int_plus(menu, &s, integer);
	if (menu->width && menu->width > (int)ft_strlen(s))
		int_width(menu, &s, integer);
	*str = ft_strdup(s);
	free(s);
}

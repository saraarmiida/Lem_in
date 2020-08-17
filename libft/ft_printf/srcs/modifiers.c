/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modifiers.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spentti <spentti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/10 13:30:29 by spentti           #+#    #+#             */
/*   Updated: 2020/01/31 17:43:14 by spentti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	flags(const char *format, t_menu *menu)
{
	while (ft_strchr("-+ #0", format[menu->i]) && format[menu->i])
	{
		if (format[menu->i] == '-')
			menu->minus = 1;
		else if (format[menu->i] == '+')
			menu->plus = 1;
		else if (format[menu->i] == ' ')
			menu->space = 1;
		else if (format[menu->i] == '#')
			menu->hash = 1;
		else if (format[menu->i] == '0')
			menu->zero = 1;
		menu->i++;
	}
	if (menu->plus == 1)
		menu->space = 0;
}

void	width(const char *format, t_menu *menu)
{
	if (format[menu->i] == '*')
	{
		menu->width = -2;
		menu->i++;
		while (format[menu->i] >= '0' && format[menu->i] <= '9')
			menu->i++;
	}
	if (format[menu->i] >= '0' && format[menu->i] <= '9')
	{
		menu->width = ft_atoi(&format[menu->i]);
		while (format[menu->i] >= '0' && format[menu->i] <= '9')
			menu->i++;
	}
}

void	precision(const char *format, t_menu *menu)
{
	if (format[menu->i] == '.')
	{
		menu->i++;
		if (format[menu->i] == '*')
		{
			menu->precision = -2;
			menu->i++;
		}
		else
		{
			menu->precision = ft_atoi(&format[menu->i]);
			while (format[menu->i] >= '0' && format[menu->i] <= '9')
				menu->i++;
		}
	}
}

void	length(const char *format, t_menu *menu)
{
	if ((format[menu->i] == 'l' && format[menu->i + 1] == 'l'))
	{
		menu->length = 3;
		menu->i += 2;
	}
	if (format[menu->i] == 'l')
	{
		menu->length = 4;
		menu->i += 1;
	}
	if (format[menu->i] == 'L')
	{
		menu->length = 5;
		menu->i += 1;
	}
	if (format[menu->i] == 'h' && format[menu->i + 1] == 'h')
	{
		menu->length = 1;
		menu->i += 2;
	}
	if (format[menu->i] == 'h')
	{
		menu->length = 2;
		menu->i += 1;
	}
}

void	modifiers(const char *format, t_menu *menu)
{
	while (ft_strchr("jz", format[menu->i]) && format[menu->i])
		menu->i++;
	while (ft_strchr("*#-+ .0123456789hLl", format[menu->i]) && format[menu->i])
	{
		flags(format, menu);
		width(format, menu);
		precision(format, menu);
		if (ft_strchr("hlL", format[menu->i]))
			length(format, menu);
	}
}

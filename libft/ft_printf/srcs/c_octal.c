/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_octal.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spentti <spentti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 11:00:23 by spentti           #+#    #+#             */
/*   Updated: 2020/01/30 16:09:40 by spentti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

char	*ft_itoa_base(unsigned long long n, int base)
{
	char	*str;
	int		i;
	int		len;

	len = ft_baselen(n, base);
	if (!(str = (char *)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	i = len - 1;
	if (n == 0)
		str[0] = 48;
	while (n > 0)
	{
		str[i] = (n % base < 10) ? '0' + n % base : n % base + 'a' - 10;
		n = n / base;
		i--;
	}
	str[len] = '\0';
	return (str);
}

void	oct_modifiers(t_menu *menu, char **s, int num)
{
	char	*temp;
	int		n;

	if (menu->precision != -1 && menu->precision > (int)ft_strlen(*s))
	{
		n = menu->precision - ft_strlen(*s);
		temp = ft_memset(ft_strnew(n), '0', n);
		*s = join_free(temp, *s);
	}
	if (menu->hash == 1 && *s[0] != '0')
	{
		temp = ft_strdup("0");
		*s = join_free(temp, *s);
	}
	if (menu->hash != 1 && menu->precision == 0 && num == 0)
	{
		free(*s);
		*s = ft_strnew(0);
	}
}

void	c_octal(t_menu *menu, va_list ap, char **str)
{
	char				*s;
	unsigned long long	integer;

	if (menu->width == -2)
		menu->width = (int)va_arg(ap, int);
	if (menu->precision == -2)
		menu->precision = (int)va_arg(ap, int);
	get_length(&integer, ap, menu);
	if (integer < 0)
		integer = 4294967296 + integer;
	s = ft_itoa_base(integer, 8);
	oct_modifiers(menu, &s, integer);
	get_width(menu, &s);
	*str = ft_strdup(s);
	free(s);
}

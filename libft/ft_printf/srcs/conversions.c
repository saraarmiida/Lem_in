/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversions.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spentti <spentti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/10 13:45:01 by spentti           #+#    #+#             */
/*   Updated: 2020/01/31 18:11:12 by spentti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	conversions(char c, t_menu *menu, va_list ap)
{
	if (!(menu->link->next = (t_link *)malloc(sizeof(t_link))))
		return ;
	menu->link = menu->link->next;
	menu->link->nul = 0;
	menu->link->next = NULL;
	if (c == 'c')
		c_char(menu, ap, &menu->link->str);
	else if (c == 's')
		c_string(menu, ap, &menu->link->str);
	else if (c == 'p')
		c_pointer(menu, ap, &menu->link->str);
	else if (c == 'i' || c == 'd')
		c_integer(menu, ap, &menu->link->str);
	else if (c == 'u')
		c_unsigned(menu, ap, &menu->link->str);
	else if (c == 'o')
		c_octal(menu, ap, &menu->link->str);
	else if (c == 'x' || c == 'X')
		c_hex(menu, ap, &menu->link->str, c);
	else if (c == 'f')
		c_double(menu, ap, &menu->link->str);
	else if (c == '%')
		percent_sign(menu, &menu->link->str);
	else if (c == 'b')
		c_binary(menu, ap, &menu->link->str, c);
}

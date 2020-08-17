/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_format.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spentti <spentti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 16:14:52 by spentti           #+#    #+#             */
/*   Updated: 2020/01/31 18:09:43 by spentti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int	create_link(t_menu *menu, const char *form, char delim)
{
	int		i;

	i = menu->i;
	if (menu->head != NULL)
	{
		if (!(menu->link->next = (t_link *)malloc(sizeof(t_link))))
			return (1);
		menu->link = menu->link->next;
	}
	else if (!(menu->link = (t_link *)malloc(sizeof(t_link))))
		return (1);
	if (!(menu->link->str = ft_strndup(&form[i], ft_strclen(form, i, delim))))
		return (1);
	menu->link->nul = 0;
	menu->link->next = NULL;
	if (menu->head == NULL)
		menu->head = menu->link;
	i += ft_strlen(menu->link->str);
	menu->i = i;
	return (0);
}

int	parse_format(const char *format, t_menu *menu, va_list ap)
{
	while (format[menu->i] != '\0')
	{
		if (create_link(menu, format, '%'))
			return (1);
		else if (format[menu->i] == '%')
		{
			menu->i++;
			if (ft_strchr(menu->symbols, format[menu->i]))
			{
				if (!(ft_strchr(menu->conversions, format[menu->i])))
					modifiers(format, menu);
				if (ft_strchr(menu->conversions, format[menu->i]) != NULL)
				{
					conversions(format[menu->i], menu, ap);
					menu->i++;
					zero_menu(menu);
				}
			}
		}
	}
	return (0);
}

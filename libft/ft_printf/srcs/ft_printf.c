/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spentti <spentti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/09 14:34:25 by spentti           #+#    #+#             */
/*   Updated: 2020/01/31 17:48:05 by spentti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

t_menu	*create_menu(void)
{
	t_menu	*menu;

	if (!(menu = (t_menu *)malloc(sizeof(t_menu))))
		return (NULL);
	menu->symbols = "cspdiouxXfb%#-+ .*0123456789hLljz";
	menu->conversions = "cspdiouxXfb%";
	menu->i = 0;
	menu->head = NULL;
	zero_menu(menu);
	return (menu);
}

int		ft_printf(const char *format, ...)
{
	int				printed;
	va_list			ap;
	t_menu			*menu;
	int				mode;
	char			*str;

	va_start(ap, format);
	if (ft_strlen(format) == 1 && format[0] == '%')
		return (0);
	menu = create_menu();
	if (ft_strchr(format, '%') == NULL)
	{
		str = ft_strdup(format);
		menu->len = ft_strlen(str);
	}
	else if ((mode = parse_format(format, menu, ap)) == 1)
		return (0);
	else
		str = joinlist(menu->head, menu);
	ft_putmem(str, menu->len);
	va_end(ap);
	printed = menu->len;
	free(menu);
	free(str);
	return (printed);
}

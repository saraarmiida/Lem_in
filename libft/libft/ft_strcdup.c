/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcdup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spentti <spentti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/18 17:21:37 by spentti           #+#    #+#             */
/*   Updated: 2020/08/18 17:23:38 by spentti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcdup(const char *str, char c)
{
	char	*dup;
	size_t	i;

	i = 0;
	if (!(dup = ft_strnew(ft_strclen(str, i, c))))
		return (NULL);
	while (str[i] && str[i] != c)
	{
		dup[i] = str[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

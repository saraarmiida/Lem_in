/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spentti <spentti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 10:37:54 by spentti           #+#    #+#             */
/*   Updated: 2020/08/07 16:54:31 by spentti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcjoin(char const *s1, char const *s2, char const c)
{
	char	*new;
	size_t	len;

	if (!s1 || !s2)
		return (NULL);
	len = ft_strlen(s1);
	if (!(new = (char *)(ft_memalloc(len + ft_strclen(s2, 0, c) + 1))))
		return (NULL);
	new = ft_strcpy(new, s1);
	new = ft_strccpy(new + len, s2, c);
	return (new);
}

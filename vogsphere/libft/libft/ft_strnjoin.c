/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spentti <spentti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 17:12:17 by spentti           #+#    #+#             */
/*   Updated: 2020/08/12 12:57:31 by spentti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnjoin(char const *s1, char const *s2, size_t n)
{
	char	*new;

	if (!s1 || !s2)
		return (NULL);
	if (!(new = (char *)(ft_memalloc(ft_strlen(s1) + n + 1))))
		return (NULL);
	new = ft_strcpy(new, s1);
	new = ft_strncat(new, s2, n);
	return (new);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spentti <spentti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 18:17:59 by spentti           #+#    #+#             */
/*   Updated: 2020/08/12 12:57:41 by spentti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s)
{
	int		i;
	int		len;
	int		j;
	char	*trim;

	i = 0;
	if (s == NULL)
		return (NULL);
	len = ft_strlen(s);
	while (s[len - 1] == ' ' || s[len - 1] == '\n' || s[len - 1] == '\t')
		len--;
	while (s[i] == ' ' || s[i] == '\n' || s[i] == '\t')
	{
		len--;
		i++;
	}
	if (len <= 0)
		len = 0;
	if (!(trim = (char *)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	j = -1;
	while (j++ < len - 1)
		trim[j] = s[i++];
	trim[j++] = '\0';
	return (trim);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spentti <spentti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 13:16:48 by spentti           #+#    #+#             */
/*   Updated: 2020/08/12 12:55:21 by spentti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_itoa(long long int n)
{
	char	*str;
	int		i;
	int		len;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	len = ft_intlen(n);
	if (!(str = (char *)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	if (n < 0)
	{
		str[0] = '-';
		n = n * -1;
	}
	i = len - 1;
	if (n == 0)
		str[0] = 48;
	while (n > 0)
	{
		str[i] = 48 + n % 10;
		n = n / 10;
		i--;
	}
	str[len] = '\0';
	return (str);
}

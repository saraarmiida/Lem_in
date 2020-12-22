/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ftoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spentti <spentti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 15:05:07 by spentti           #+#    #+#             */
/*   Updated: 2020/01/30 16:35:33 by spentti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

char		*get_int_part(long long inum, int prec, long double n, int hash)
{
	char	*str1;
	char	*temp;

	str1 = ft_itoa(inum);
	if (prec != 0 || hash == 1)
	{
		temp = ft_strjoin(str1, ".");
		free(str1);
		str1 = temp;
	}
	if (n < 0)
	{
		temp = ft_strjoin("-", str1);
		free(str1);
		str1 = temp;
	}
	return (str1);
}

long double	rounding(int precision)
{
	long double	roundup;
	int			n;

	roundup = 0.5;
	n = 0;
	while (n++ < precision)
		roundup /= 10.0;
	return (roundup);
}

char		*get_float_part(long long inum, int precision, long double fnum)
{
	char		*str2;
	int			i;

	i = 0;
	fnum = precision ? (fnum - inum) : 0;
	if (!(str2 = ft_strnew(precision + 1)))
		return (NULL);
	while (i < precision)
	{
		fnum *= 10;
		inum = fnum;
		fnum -= inum;
		str2[i++] = inum + '0';
	}
	return (str2);
}

char		*ft_ftoa(long double fnum, int precision, int hash)
{
	long long	inum;
	char		*strint;
	char		*strfloat;
	long double	fnum2;

	fnum2 = (fnum < 0 ? -fnum : fnum);
	fnum2 += rounding(precision);
	inum = fnum2;
	strint = get_int_part(inum, precision, fnum, hash);
	strfloat = get_float_part(inum, precision, fnum2);
	return (join_free(strint, strfloat));
}

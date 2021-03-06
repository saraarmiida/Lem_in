/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spentti <spentti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 11:57:02 by spentti           #+#    #+#             */
/*   Updated: 2020/08/12 12:54:36 by spentti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr(int n)
{
	if (n < 0)
	{
		ft_putchar('-');
		if (n == -2147483648)
			ft_putstr("2147483648");
		else
			n = n * -1;
	}
	if (n >= 10)
		ft_putnbr(n / 10);
	if (n != -2147483648)
		ft_putchar(n % 10 + 48);
}

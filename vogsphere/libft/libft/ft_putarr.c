/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putarr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spentti <spentti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/20 17:19:33 by spentti           #+#    #+#             */
/*   Updated: 2019/12/20 17:20:19 by spentti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

void	ft_putarr(char **arr)
{
	int i;

	i = 0;
	while (arr[i])
	{
		ft_putendl(arr[i]);
		i++;
	}
}

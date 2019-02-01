/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_log.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbatz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/26 17:48:48 by kbatz             #+#    #+#             */
/*   Updated: 2019/02/01 10:17:36 by kbatz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

double		ft_log(double n)
{
	int		i;
	double	res;
	double	x;
	char	sign;

	sign = 1;
	if (n > 1)
	{
		n = 1 / n;
		sign = -1;
	}
	n--;
	x = n;
	res = x;
	i = 0;
	while (++i < LOG_ADD_PR && (x > 0 ? x : -x) > LOG_PR)
	{
		x *= -n;
		res += x / i;
	}
	return (res * sign);
}

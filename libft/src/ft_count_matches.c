/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_matches.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbatz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 09:21:23 by kbatz             #+#    #+#             */
/*   Updated: 2019/02/01 10:58:02 by kbatz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_count_matches(const char *str, const char *match)
{
	int		k;

	k = 0;
	while ((str = ft_strstr(str, match)))
	{
		k++;
		str++;
	}
	return (k);
}

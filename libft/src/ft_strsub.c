/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbatz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 00:52:12 by kbatz             #+#    #+#             */
/*   Updated: 2018/12/22 19:15:09 by kbatz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*res;

	res = ft_strnew(len);
	if (!res || !s)
		return (NULL);
	res += len;
	s += start + len;
	while (len-- > 0)
		*--res = *--s;
	return (res);
}

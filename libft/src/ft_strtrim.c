/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbatz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 20:30:14 by kbatz             #+#    #+#             */
/*   Updated: 2018/12/22 20:28:00 by kbatz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s)
{
	size_t	len;
	char	*res;
	char	*start;
	char	*end;

	if (!s)
		return (NULL);
	while (*s && (*s == ' ' || *s == '\n' || *s == '\t'))
		s++;
	start = (char *)s;
	while (*++s)
		if (*s != ' ' && *s != '\n' && *s != '\t')
			end = (char *)s + 1;
	len = end - start;
	res = ft_strnew(len);
	if (!res)
		return (NULL);
	res += len;
	while (len-- > 0)
		*--res = *--end;
	return (res);
}

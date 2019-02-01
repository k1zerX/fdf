/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbatz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 21:41:15 by kbatz             #+#    #+#             */
/*   Updated: 2018/12/22 18:59:48 by kbatz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		split_len(char const *s, char c)
{
	size_t	i;
	size_t	k;

	k = 0;
	i = 0;
	if (!s)
		return (-1);
	while (s[i])
	{
		if (s[i] != c)
		{
			k++;
			while (s[i] && s[i] != c)
				i++;
			i--;
		}
		i++;
	}
	return (k);
}

static size_t	split_find(char const *s, char c, size_t *i, size_t *prev)
{
	while (s[*i] == c)
		(*i)++;
	*prev = *i;
	return (1);
}

static char		ft_check(char ***res, size_t k)
{
	size_t	i;

	if ((*res)[k])
		return (0);
	i = -1;
	while (++i < k)
		free((*res)[i]);
	free(*res);
	*res = NULL;
	return (1);
}

char			**ft_strsplit(char const *s, char c)
{
	size_t	i;
	size_t	k;
	size_t	prev;
	char	**res;

	res = (char **)ft_memalloc(sizeof(*res) * (split_len(s, c) + 1));
	i = 0;
	k = 0;
	if (!s || !res)
		return (NULL);
	split_find(s, c, &i, &prev);
	i--;
	while (s[++i])
		if (s[i] == c)
		{
			if (i - prev > 0)
				res[k++] = ft_strsub(s, prev, i - prev);
			if (ft_check(&res, k - 1))
				return (NULL);
			if (split_find(s, c, &i, &prev) && s[i] == 0)
				i--;
		}
	if (i - prev > 0)
		res[k++] = ft_strsub(s, prev, i - prev);
	return (res);
}

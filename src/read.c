/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbatz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 17:21:08 by kbatz             #+#    #+#             */
/*   Updated: 2019/04/24 20:16:47 by kbatz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	fill_map_elem(int *elem, char **str)
{
	char	sign;

	sign = 1;
	if (**str == '-' || **str == '+')
		sign = 44 - *(*str)++;
	while (ft_isdigit(**str))
		elem[0] = elem[0] * 10 + *(*str)++ - '0';
	elem[0] *= sign;
	while (ft_isspace(**str))
		(*str)++;
	if (*(*str) != ',')
		return ;
	(*str)++;
	while (ft_isspace(**str))
		(*str)++;
	(*str) += 2;
	while (ft_isdigit(*(++*str)) || \
			(ft_tolower(**str) >= 'a' && ft_tolower(**str) <= 'f'))
	{
		elem[1] <<= 4;
		if (ft_isdigit(**str))
			elem[1] |= **str - '0';
		else
			elem[1] |= **str - 'a' + 10;
	}
}

int		ft_fill(t_params *prms, char *str, int *min, int *max)
{
	int		k;

	k = 0;
	while (*str)
	{
		while (ft_isspace(*str))
			str++;
		if (*str == '-' || *str == '+' || ft_isdigit(*str))
		{
			prms->map[prms->y] = ft_realloc(prms->map[prms->y], \
					sizeof(**(prms->map)) * k, 1);
			prms->map[prms->y][k] = ft_memalloc(sizeof(***(prms->map)) * 2);
			fill_map_elem(prms->map[prms->y][k++], &str);
			if (!prms->y && !(k - 1))
			{
				*min = prms->map[prms->y][k - 1][0];
				*max = *min;
			}
			else if (prms->map[prms->y][k - 1][0] < *min)
				*min = prms->map[prms->y][k - 1][0];
			else if (prms->map[prms->y][k - 1][0] > *max)
				*max = prms->map[prms->y][k - 1][0];
		}
	}
	return (k);
}

void	ft_fill_color(t_params *prms, int min, int max)
{
	int		i;
	int		j;

	j = prms->y;
	while (j-- > 0)
	{
		i = prms->x;
		while (i-- > 0)
		{
			if (!prms->map[j][i][1])
				ft_fill_one(prms->map[j][i] + 1, min, max);
			else
				prms->map[j][i][1] &= 0x00ffffff;
			prms->map[j][i][0] -= min;
		}
	}
	prms->z = max - min;
}

int		read_help_me_pls_tool(t_params *prms, char *str, int *min, int *max)
{
	int		k;

	prms->map = ft_realloc(prms->map, sizeof(*(prms->map)) * prms->y, 1);
	k = ft_fill(prms, str, min, max);
	prms->y++;
	free(str);
	return (k);
}

void	ft_read(int fd, t_params *prms)
{
	char	*str;
	char	b;
	int		min;
	int		max;
	int		k;

	while ((b = get_next_line(fd, &str)) > 0)
	{
		k = read_help_me_pls_tool(prms, str, &min, &max);
		if (!prms->x)
			prms->x = k;
		else if (prms->x != k)
		{
			--prms->y;
			close(fd);
			while (--k >= 0)
				free(prms->map[prms->y][k]);
			free(prms->map[prms->y]);
			ft_exit(READ_ERROR, prms);
		}
	}
	close(fd);
	if (b == -1)
		ft_exit(READ_ERROR, prms);
	ft_fill_color(prms, min, max);
}

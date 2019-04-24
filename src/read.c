/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbatz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 17:21:08 by kbatz             #+#    #+#             */
/*   Updated: 2019/04/24 18:48:31 by kbatz            ###   ########.fr       */
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

void	ft_read(int fd, t_params *prms)
{
	char	*str;
	char	*buf;
	char	b;
	int		***map;
	int		len;
	int		k;
	int		min;
	int		max;
	int		i;
	int		j;
	double	bk;

	map = NULL;
	len = 0;
	while ((b = get_next_line(fd, &buf)) > 0)
	{
		str = buf;
		map = ft_realloc(map, sizeof(*map) * len, 1);
		k = 0;
		while (*str)
		{
			while (ft_isspace(*str))
				str++;
			if (*str == '-' || *str == '+' || ft_isdigit(*str))
			{
				map[len] = ft_realloc(map[len], sizeof(**map) * k, 1);
				map[len][k] = ft_memalloc(sizeof(***map) * 2);
				fill_map_elem(map[len][k++], &str);
				if (!len && !(k - 1))
				{
					min = map[len][k - 1][0];
					max = min;
				}
				else if (map[len][k - 1][0] < min)
					min = map[len][k - 1][0];
				else if (map[len][k - 1][0] > max)
					max = map[len][k - 1][0];
			}
		}
		len++;
		free(buf);
		if (!prms->x)
			prms->x = k;
		else if (prms->x != k)
		{
			prms->map = map;
			prms->y = len - 1;
			close(fd);
			while (k-- > 0)
				free(map[prms->y][k]);
			free(map[prms->y]);
			ft_exit(READ_ERROR, prms);
		}
	}
	close(fd);
	prms->map = map;
	prms->y = len;
	if (b == -1)
		ft_exit(READ_ERROR, prms);
	j = len;
	while (j-- > 0)
	{
		i = k;
		while (i-- > 0)
		{
			if (!map[j][i][1])
			{
				if (!map[j][i][0])
					map[j][i][1] = ZERO;
				else if (map[j][i][0] > 0)
				{
					bk = (double)map[j][i][0] / (double)max;
					map[j][i][1] = (int)round(((TOP >> 16) & 0xff) * bk + ((ZERO >> 16) & 0xff) * (1 - bk)) << 16;
					map[j][i][1] |= (int)round(((TOP >> 8) & 0xff) * bk + ((ZERO >> 8) & 0xff) * (1 - bk)) << 8;
					map[j][i][1] |= (int)round((TOP & 0xff) * bk + (ZERO & 0xff) * (1 - bk));
				}
				else if (map[j][i][0] < 0)
				{
					bk = (double)map[j][i][0] / (double)min;
					map[j][i][1] = (int)round(((BOT >> 16) & 0xff) * bk + ((ZERO >> 16) & 0xff) * (1 - bk)) << 16;
					map[j][i][1] |= (int)round(((BOT >> 8) & 0xff) * bk + ((ZERO >> 8) & 0xff) * (1 - bk)) << 8;
					map[j][i][1] |= (int)round((BOT & 0xff) * bk + (ZERO & 0xff) * (1 - bk));
				}
			}
			else
				map[j][i][1] &= 0x00ffffff;
			map[j][i][0] -= min;
		}
	}
	max -= min;
	prms->z = max;
}

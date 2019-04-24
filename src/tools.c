/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbatz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 17:34:30 by kbatz             #+#    #+#             */
/*   Updated: 2019/04/24 20:12:44 by kbatz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	free_map(t_params *prms)
{
	int		i;

	while (prms->y-- > 0)
	{
		i = prms->x;
		while (i-- > 0)
			free(prms->map[prms->y][i]);
		free(prms->map[prms->y]);
	}
	free(prms->map);
}

void	ft_exit(int status, t_params *prms)
{
	if (status == USAGE)
		write(1, "usage:\n\t./fdf [file_name]\n\t./fdf [file_name] " \
				"[size_x > 0] [size_y > 0]\n", 71);
	else if (status == CLOSE || status == ERROR || status == READ_ERROR)
	{
		free_map(prms);
		if (status == CLOSE || status == ERROR)
		{
			mlx_destroy_window(prms->mlx, prms->win);
			free(prms->deep_map);
		}
		if (status == ERROR || status == READ_ERROR)
			write(2, "Error\n", 6);
	}
	exit(0);
}

int		ft_close(t_params *prms)
{
	ft_exit(CLOSE, prms);
	return (0);
}

void	ft_initialize(t_params *prms)
{
	if (!prms->n || !prms->m)
	{
		prms->n = 1000;
		prms->m = 1000;
	}
	if (!prms->deep_map)
		prms->deep_map = ft_memalloc(prms->n * prms->m \
				* sizeof(*prms->deep_map));
	prms->q = get_qtrn(get_vector(1, 0, 0), M_PI * 2 / 3);
	prms->q = mul_qtrn(prms->q, get_qtrn(get_vector(0, 1, 0), M_PI * 2 / 3));
	prms->q = get_qtrn(get_vector(1, 0, 0), 0);
	ft_bzero(&prms->shift, sizeof(prms->shift));
	prms->start.x = -(double)(prms->x - 1) / 2;
	prms->start.y = -(double)(prms->y - 1) / 2;
	prms->start.z = -(double)prms->z / 2;
	prms->delta = prms->z + 1;
	prms->d = -prms->delta * K;
}

void	ft_fill_one(int *color, int min, int max)
{
	double	bk;

	if (!*(color - 1))
		*color = ZERO;
	else if (*(color - 1) > 0)
	{
		bk = (double)*(color - 1) / (double)max;
		*color = (int)round(((TOP >> 16) & 0xff) * bk + \
				((ZERO >> 16) & 0xff) * (1 - bk)) << 16;
		*color |= (int)round(((TOP >> 8) & 0xff) * bk + \
				((ZERO >> 8) & 0xff) * (1 - bk)) << 8;
		*color |= (int)round((TOP & 0xff) * bk + \
				(ZERO & 0xff) * (1 - bk));
	}
	else if (*(color - 1) < 0)
	{
		bk = (double)*(color - 1) / (double)min;
		*color = (int)round(((BOT >> 16) & 0xff) * bk + \
				((ZERO >> 16) & 0xff) * (1 - bk)) << 16;
		*color |= (int)round(((BOT >> 8) & 0xff) * bk + \
				((ZERO >> 8) & 0xff) * (1 - bk)) << 8;
		*color |= (int)round((BOT & 0xff) * bk + \
				(ZERO & 0xff) * (1 - bk));
	}
}

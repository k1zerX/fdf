/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbatz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/15 19:06:59 by kbatz             #+#    #+#             */
/*   Updated: 2019/02/18 21:36:10 by kbatz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void		ft_put_2pixel(t_params *prms, int x, int y, t_gradient gr)
{
	int		color;
	int		i;

	x += prms->n / 2;
	y += prms->m / 2;
	if (gr.inv)
		ft_swap(&x, &y, sizeof(x));
	color = (int)round((1 - gr.opacity) * 255);
	i = -1;
	while (++i < 3)
	{
		color <<= 8;
		color |= (int)round((gr.to & 0xff) * gr.k + (gr.from & 0xff) * (1 - gr.k));
		gr.to >>= 8;
		gr.from >>= 8;
	}
	mlx_pixel_put(prms->mlx, prms->win, x, y, color);
	color &= 0x00ffffff;
	color |= (int)round(gr.opacity * 255) << 24;
	if (gr.inv)
		mlx_pixel_put(prms->mlx, prms->win, x + 1, y, color);
	else
		mlx_pixel_put(prms->mlx, prms->win, x, y + 1, color);
}

void		ft_put_line2(t_params *prms, t_vector from, t_vector to, t_gradient gr)
{
	double	x;
	double	y;
	double	grk;
	double	k;

	grk = 1 / (to.x - from.x);
	gr.k = 1;
	gr.opacity = modf(to.y, &y) * modf(to.x, &x); 
	ft_put_2pixel(prms, (int)x, (int)y, gr);
	gr.k = 0;
	k = 1 - modf(from.x, &x);
	gr.opacity = modf(from.y, &y) * k;
	ft_put_2pixel(prms, (int)x, (int)y, gr);
	gr.k = grk * k; 
	k = (to.y - from.y) * grk;
	from.y = y;
	while (++x < to.x)
	{
		from.y += k;
		gr.opacity = 1 - modf(from.y, &y);
		ft_put_2pixel(prms, (int)x, (int)y, gr);
		gr.k += grk;
	}
}

void		ft_put_line(t_params *prms, t_vector from, t_vector to, t_gradient gr)
{
	if (prms->d > 0)
		return ;
	from = turn_vector(add_vector(from, prms->start), prms->q, 1);
	from = add_vector(from, prms->shift);
	if (from.z + prms->d > 0)
		return ;
	else if (from.z + prms->d == 0)
	{
		from.x = from.x * prms->d / (from.z + prms->d - 1);
		from.y = from.y * prms->d / (from.z + prms->d - 1);
	}
	else
	{
		from.x = from.x * prms->d / (from.z + prms->d);
		from.y = from.y * prms->d / (from.z + prms->d);
	}
//	printf("%f, %d\n", prms->shift.z, prms->d);
	to = turn_vector(add_vector(to, prms->start), prms->q, 1);
	to = add_vector(to, prms->shift);
	if (to.z + prms->d > 0)
		return ;
	else if (to.z + prms->d == 0)
	{
		to.x = to.x * prms->d / (from.z + prms->d - 1);
		to.y = to.y * prms->d / (from.z + prms->d - 1);
	}
	else
	{
		to.x = to.x * prms->d / (to.z + prms->d);
		to.y = to.y * prms->d / (to.z + prms->d);
	}
	//printf("%f, %f, %f to %f, %f, %f\n", from.x, from.y, from.z, to.x, to.y, to.z);
	k_vector(&from, prms->k);
	k_vector(&to, prms->k);
	if ((gr.inv = (fabs(to.y - from.y) > fabs(to.x - from.x))))
	{
		ft_swap(&from.x, &from.y, sizeof(from.x));
		ft_swap(&to.x, &to.y, sizeof(to.x));
	}
	if (from.x > to.x)
	{
		ft_swap(&from.x, &to.x, sizeof(from.x));
		ft_swap(&from.y, &to.y, sizeof(from.y));
		ft_swap(&gr.from, &gr.to, sizeof(gr.from));
	}/*
	if (from.x < 0)
	{
		from.y += (to.y - from.y) / (to.x - from.x) * (0 - from.x);
		from.x = 0;
	}
	if (to.x > prms->x)
	{
		to.y -= (to.y - from.y) / (to.x - from.x) * (to.x - prms->x);
		to.x = prms->x;
	}
	if (from.y < 0)
	{
		from.x += (to.x - from.x) / (to.y - from.y) * (0 - from.y);
		from.y = 0;
	}
	if (to.y < 0)
	{
		to.x -= (to.x - from.x) / (to.y - from.y) * (0 - to.y);
		to.y = 0;
	}
	if (from.y > prms->y)
	{
		from.x += (to.x - from.x) / (to.y - from.y) * (from.y - prms->y);
		from.y = prms->y;
	}
	if (to.y > prms->y)
	{
		to.x -= (to.x - from.x) / (to.y - from.y) * (to.y - prms->y);
		to.y = prms->y;
	}*/
	ft_put_line2(prms, from, to, gr);
}

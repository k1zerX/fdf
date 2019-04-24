/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbatz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/15 19:06:59 by kbatz             #+#    #+#             */
/*   Updated: 2019/04/24 18:52:42 by kbatz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void		get_color(int *dst, int new, char bl)
{
	int		i;
	int		prev;
	double	a;
	double	b;

	if (bl)
	{
		prev = new;
		new = *dst;
	}
	else
		prev = *dst;
	a = (double)((prev >> 24) & 0xff) / 255;
	b = (double)((new >> 24) & 0xff) / 255;
	*dst = (int)round((a * b) * 0xff) << 24;
	i = 0;
	while (i <= 16)
	{
		*dst |= (int)round((((prev >> i) & 255) * b * (1 - a) + ((new >> i) \
						& 255) * (1 - b)) / (1 - a * b)) << i;
		i += 8;
	}
}

void		ft_put_pixel(t_params *prms, t_vector p, int color)
{
	if (p.x < 0 || p.y < 0 || p.x >= prms->n || p.y >= prms->m)
		return ;
	if (p.z > prms->deep_map[(int)p.x * prms->n + (int)p.y])
	{
		get_color((int *)prms->img + (int)p.x * prms->n + (int)p.y, color, 0);
		prms->deep_map[(int)p.x * prms->n + (int)p.y] = p.z;
	}
	else
		get_color((int *)prms->img + (int)p.x * prms->n + (int)p.y, color, 1);
}

void		ft_put_2pixel(t_params *prms, t_vector p, t_gradient gr)
{
	int		color;
	int		i;

	color = (int)round((1 - (1 - gr.opacity_y) * gr.opacity_x) * 255);
	i = 16;
	while (i >= 0)
	{
		color <<= 8;
		color |= (int)round((gr.to & (0xff << i)) * gr.k \
				+ (gr.from & (0xff << i)) * (1 - gr.k)) >> i;
		i -= 8;
	}
	if (!gr.inv)
		ft_swap(&p.x, &p.y, sizeof(p.x));
	ft_put_pixel(prms, p, color);
	if (gr.inv)
		++p.y;
	else
		++p.x;
	color &= 0x00ffffff;
	color |= (int)round((1 - gr.opacity_y * gr.opacity_x) * 255) << 24;
	ft_put_pixel(prms, p, color);
}

void		ft_put_line2(t_params *prms, t_vector from, \
		t_vector to, t_gradient gr)
{
	t_vector	p;
	double		grk;
	double		k;
	double		kz;

	grk = 1 / (to.x - from.x);
	kz = (to.z - from.z) * grk;
	gr.k = 1;
	gr.opacity_x = modf(to.x, &p.x);
	gr.opacity_y = modf(to.y, &p.y);
	p.z = to.z;
//	ft_put_2pixel(prms, p, gr);
	gr.k = 0;
	gr.opacity_x = 1 - modf(from.x, &p.x);
	gr.opacity_y = modf(from.y, &p.y);
	p.z = from.z;
//	ft_put_2pixel(prms, p, gr);
	gr.k = grk * gr.opacity_x;
	k = (to.y - from.y) * grk;
	gr.opacity_x = 1;
	from.y += (gr.opacity_x - 1) * k;
	while (++p.x <= to.x)
	{
		p.z += kz;
		from.y += k;
		gr.opacity_y = modf(from.y, &p.y);
		ft_put_2pixel(prms, p, gr);
		gr.k += grk;
	}
}

void		ft_put_line(t_params *prms, t_vector from, t_vector to)
{
	t_gradient	gr;

	gr.from = prms->map[(int)from.y][(int)from.x][1];
	gr.to = prms->map[(int)to.y][(int)to.x][1];
	from = turn_vector(add_vector(from, prms->start), prms->q, 1);
	from = add_vector(from, prms->shift);
	to = turn_vector(add_vector(to, prms->start), prms->q, 1);
	to = add_vector(to, prms->shift);
	if (from.z >= -prms->d || to.z >= -prms->d)
		return ;
	from.x = from.x * prms->d / (from.z + prms->d);
	from.y = from.y * prms->d / (from.z + prms->d);
	to.x = to.x * prms->d / (to.z + prms->d);
	to.y = to.y * prms->d / (to.z + prms->d);
	if ((gr.inv = (fabs(to.y - from.y) > fabs(to.x - from.x))))
	{
		ft_swap(&from.x, &from.y, sizeof(from.x));
		ft_swap(&to.x, &to.y, sizeof(to.x));
	}
	if (from.x > to.x)
	{
		ft_swap(&from, &to, sizeof(from));
		ft_swap(&gr.from, &gr.to, sizeof(gr.from));
	}
	k_vector(&from, K);
	k_vector(&to, K);
	from.x += prms->n / 2;
	from.y += prms->m / 2;
	to.x += prms->n / 2;
	to.y += prms->m / 2;
	ft_put_line2(prms, from, to, gr);
}

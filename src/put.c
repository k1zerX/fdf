/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbatz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/15 19:06:59 by kbatz             #+#    #+#             */
/*   Updated: 2019/04/24 20:18:41 by kbatz            ###   ########.fr       */
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbatz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/15 19:06:59 by kbatz             #+#    #+#             */
/*   Updated: 2019/02/23 05:11:32 by kbatz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void		ft_put_2pixel(t_params *prms, int x, int y, t_gradient gr)
{
	int		color;
	int		i;

	//printf("%d, %d\n", x, y);
	//if (x < 0 || y < 0 || x > prms->n || y > prms->m)
	//	return (1);
	color = (int)round((1 - (1 - gr.opacity_y) * gr.opacity_x) * 255);
	i = 16;
	while (i >= 0)
	{
		color <<= 8;
		color |= (int)round((gr.to & (0xff << i)) * gr.k \
			   	+ (gr.from & (0xff << i)) * (1 - gr.k)) >> i;
		i -= 8;
	}
	if (gr.inv)
		mlx_pixel_put(prms->mlx, prms->win, y, x, color);
	else
		mlx_pixel_put(prms->mlx, prms->win, x, y, color);
	color &= 0x00ffffff;
	color |= (int)round((1 - gr.opacity_y * gr.opacity_x) * 255) << 24;
	if (gr.inv)
		mlx_pixel_put(prms->mlx, prms->win, y + 1, x, color);
	else
		mlx_pixel_put(prms->mlx, prms->win, x, y + 1, color);
//	return (0);
}

void		ft_put_line2(t_params *prms, t_vector from, t_vector to, t_gradient gr)
{
	double	x;
	double	y;
	double	grk;
	double	k;

	grk = 1 / (to.x - from.x);
	gr.k = 1;
	gr.opacity_x = modf(to.x, &x);
	gr.opacity_y = modf(to.y, &y);
	ft_put_2pixel(prms, (int)x, (int)y, gr);
	gr.k = 0;
	gr.opacity_x = 1 - modf(from.x, &x);
	gr.opacity_y = modf(from.y, &y);
	ft_put_2pixel(prms, (int)x, (int)y, gr);
	gr.k = grk * gr.opacity_x; 
	k = (to.y - from.y) * grk;
	gr.opacity_x = 1;
	from.y = y + k;
//	printf("%f, %f, %f ---> %f, %f, %f\n", from.x, from.y, from.z, to.x, to.y, to.z);
	while ((++x <= to.x && !gr.inf) || gr.inf)
	//while (++x <= to.x)
	{
		//if (gr.inf)
		//	printf("%f\n", from.z + prms->d);
		from.z += (to.z - from.z) / (to.x - from.x) ;
		gr.opacity_y = modf(from.y, &y);
		//if (ft_put_2pixel(prms, (int)x, (int)y, gr) && gr.inf)
		//	break ;
		ft_put_2pixel(prms, (int)x, (int)y, gr);
		gr.k += grk;
		from.y += k;
		if (gr.inf)
			if (x < 0 || y < 0 || x > prms->n || y > prms->m)
				break ;
		if (gr.inf)
		{
//			printf("ALERT\n");
//			printf("%f to %f\n", x, to.x);
			//if (from.z >= to.z)
			//	printf("%f to %f\n", from.z, to.z);
//			break ;
		}
	}
}

void		ft_put_line(t_params *prms, t_vector from, t_vector to, t_gradient gr)
{
	//printf("d = %f, sh.z = %f\n", prms->d, prms->shift.z);
	from = turn_vector(add_vector(from, prms->start), prms->q, 1);
	from = add_vector(from, prms->shift);
	to = turn_vector(add_vector(to, prms->start), prms->q, 1);
	to = add_vector(to, prms->shift);
	gr.inf = 0;
	//printf("%f, %f, %f ---> %f, %f, %f\n", from.x, from.y, from.z, to.x, to.y, to.z);
//	if (from.z >= -prms->d && to.z >= -prms->d)
	if (from.z >= -prms->d || to.z >= -prms->d)
		return;
	if (from.z >= -prms->d)
	{
//		printf("%f ||| %f, %f, %f\n", -prms->d, from.x, from.y, from.z);
		//return ;
//		from.x -= (from.z - (-prms->d + to.z) / 2) * (to.x - from.x) / (to.z - from.z);
//		from.y -= (from.z - (-prms->d + to.z) / 2) * (to.y - from.y) / (to.y - from.z);
//		from.z = (-prms->d + to.z) / 2;
		from.x -= (from.z - (-prms->d - 1)) * (to.x - from.x) / (to.z - from.z);
		from.y -= (from.z - (-prms->d - 1)) * (to.y - from.y) / (to.y - from.z);
		from.z = (-prms->d - 1);
//		printf("%f ||| %f, %f, %f\n", -prms->d, from.x, from.y, from.z);
		gr.inf = 1;
	}
	else if (to.z >= -prms->d)
	{
//		printf("%f ||| %f, %f, %f\n", -prms->d, to.x, to.y, to.z);
		//return ;
//		to.x -= (to.z - (-prms->d + from.z) / 2) * (to.x - from.x) / (to.z - from.z);
//		to.y -= (to.z - (-prms->d + from.z) / 2) * (to.y - from.y) / (to.y - from.z);
//		to.z = (-prms->d + from.z) / 2;
		to.x -= (to.z - (-prms->d - 1)) * (to.x - from.x) / (to.z - from.z);
		to.y -= (to.z - (-prms->d - 1)) * (to.y - from.y) / (to.y - from.z);
		to.z = (-prms->d - 1);
//		printf("%f ||| %f, %f, %f\n", -prms->d, to.x, to.y, to.z);
		gr.inf = 1;
	}
//	printf("%f & %f\n", from.z + prms->d, to.z + prms->d);
	from.x = from.x * prms->d / (from.z + prms->d);
	from.y = from.y * prms->d / (from.z + prms->d);
	to.x = to.x * prms->d / (to.z + prms->d);
	to.y = to.y * prms->d / (to.z + prms->d);
//	if (gr.inf)
//		printf("%f ||| %f, %f, %f ---> %f, %f, %f\n", prms->d, from.x, from.y, from.z, to.x, to.y, to.z);
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
	if (to.x < -prms->n / 2 || from.x > prms->n / 2)
		return ;
	if (to.x > prms->n / 2)
	{
		to.y -= (to.x - prms->n / 2) * (to.y - from.y) / (to.x - from.x);
		to.x = prms->n / 2;
	}
	if (to.y < -prms->m / 2)
	{
		to.x -= (to.y + prms->m / 2) * (to.x - from.x) / (to.y - from.y);
		to.y = -prms->m / 2;
	}
	if (to.y > prms->m / 2)
	{
		to.x -= (to.y - prms->m / 2) * (to.x - from.x) / (to.y - from.y);
		to.y = prms->m / 2;
	}
	if (from.x < -prms->n / 2)
	{
		from.y -= (from.x + prms->n / 2) * (to.y - from.y) / (to.x - from.x);
		from.x = -prms->n / 2;
	}
	if (from.y < -prms->m / 2)
	{
		from.x -= (from.y + prms->m / 2) * (to.x - from.x) / (to.y - from.y);
		from.y = -prms->m / 2;
	}
	if (from.y > prms->m / 2)
	{
		from.x -= (from.y - prms->m / 2) * (to.x - from.x) / (to.y - from.y);
		from.y = prms->m / 2;
	}
	k_vector(&from, K);
	k_vector(&to, K);
	from.x += prms->n / 2;
	from.y += prms->m / 2;
	to.x += prms->n / 2;
	to.y += prms->m / 2;
	ft_put_line2(prms, from, to, gr);
}

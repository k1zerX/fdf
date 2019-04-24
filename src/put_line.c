/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_line.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbatz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 20:18:22 by kbatz             #+#    #+#             */
/*   Updated: 2019/04/24 20:21:29 by kbatz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void		ft_put_line3(t_params *prms, t_vector from, \
		t_vector to, t_gradient gr)
{
	t_vector	p;
	double		grk;
	double		k;
	double		kz;

	grk = 1 / (to.x - from.x);
	kz = (to.z - from.z) * grk;
	gr.k = 1;
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

void		ft_put_line2(t_params *prms, t_vetor from, \
		t_vector to, t_gradient gr)
{
	k_vector(&from, K);
	k_vector(&to, K);
	from.x += prms->n / 2;
	from.y += prms->m / 2;
	to.x += prms->n / 2;
	to.y += prms->m / 2;
	gr.opacity_x = modf(to.x, &p.x);
	gr.opacity_y = modf(to.y, &p.y);
	ft_put_line3(prms, from, to, gr);
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
	ft_put_line2(prms, from, to, gr);
}

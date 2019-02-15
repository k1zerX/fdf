/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbatz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/15 19:20:04 by kbatz             #+#    #+#             */
/*   Updated: 2019/02/15 19:21:26 by kbatz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

#include "fdf.h"

typedef struct		s_point
{
	int				x;
	int				y;
}					t_point;

typedef struct		s_gradient
{
	int				from;
	int				to;
	double			opacity;
	double			k;
	char			inv;
}					t_gradient;

typedef struct		s_vector
{
	double			x;
	double			y;
	double			z;
}					t_vector;

typedef struct		s_qtrn
{
	t_vector		v;
	double			w;
}					t_qtrn;

typedef struct		s_params
{
	void			*mlx;
	void			*win;
	int				x;
	int				y;
	t_point			shift;
	t_qtrn			q;
	char			alt;
	char			xturn;
	char			yturn;
	char			zturn;
	int				***map;
	int				n;
	int				m;
}					t_params;

typedef struct		s_draw
{
	t_vector		from;
	t_vector		v;
	int				color;
}					t_draw;

#endif

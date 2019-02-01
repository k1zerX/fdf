/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbatz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/06 08:41:58 by kbatz             #+#    #+#             */
/*   Updated: 2019/02/01 16:08:27 by kbatz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <mlx.h>
# include <libc.h>
# include <math.h>
# include "libft.h"

# define CLOSE 0
# define USAGE 1
# define ERROR 2
# define ANGLE 0.1

typedef struct		s_point
{
	double			x;
	double			y;
}					t_point;

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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbatz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/06 08:41:58 by kbatz             #+#    #+#             */
/*   Updated: 2019/02/01 08:27:31 by kbatz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <mlx.h>
# include <math.h>
# include "libft.h"

# define CLOSE 0
# define USAGE 1
# define ERROR 2
# define SHIFT 25
# define X_ANGLE 0.063
# define Y_ANGLE 0.063

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
	int				n;
	int				m;
	t_point			shift;
	t_qtrn			q;
	char			alt;
}					t_params;
/*
typedef struct		s_matrix
{
	size_t			n;
	size_t			m;
	double			**mtrx;
}					t_matrix;
*/
#endif

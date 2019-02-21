/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbatz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/06 08:41:58 by kbatz             #+#    #+#             */
/*   Updated: 2019/02/21 05:00:10 by kbatz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <mlx.h>
# include <libc.h>
# include <math.h>
# include "libft.h"
# include "structs.h"
# include "vector.h"
# include "qtrn.h"
# include "put.h"

# define CLOSE 0
# define USAGE 1
# define ERROR 2
# define READ_ERROR 3
# define ANGLE M_PI / 13
# define K 10
# define TOP 0xc26910
# define ZERO 0xc0c0c0
# define BOT 0x77c4ff
# define RED 0xff0000
# define GREEN 0x00ff00
# define BLUE 0x0000ff

#endif

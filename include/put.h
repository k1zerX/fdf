/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbatz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/15 19:17:19 by kbatz             #+#    #+#             */
/*   Updated: 2019/02/23 08:15:54 by kbatz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUT_H
# define PUT_H

# include "fdf.h"

void		ft_put_2pixel(t_params *prms, t_vector p, t_gradient gr);
void		ft_put_line2(t_params *prms, t_vector from, t_vector to, t_gradient gr);
void		ft_put_line(t_params *prms, t_vector from, t_vector to, t_gradient gr);

#endif

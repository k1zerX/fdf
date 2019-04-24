/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbatz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 17:34:11 by kbatz             #+#    #+#             */
/*   Updated: 2019/04/24 20:12:36 by kbatz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOOLS_H
# define TOOLS_H

void	ft_exit(int status, t_params *prms);
int		ft_close(t_params *prms);
void	ft_initialize(t_params *prms);
void	ft_fill_one(int *color, int min, int max);

#endif

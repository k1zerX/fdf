/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbatz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/06 08:41:09 by kbatz             #+#    #+#             */
/*   Updated: 2019/04/24 17:58:10 by kbatz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	put_sector(t_params *prms, int i, int j)
{
	t_vector from;
	t_vector to;

	from = get_vector(i, j, prms->map[j][i][0]);
	if (i + 1 < prms->x)
	{
		to = get_vector(i + 1, j, prms->map[j][i + 1][0]);
		ft_put_line(prms, from, to);
	}
	if (j + 1 < prms->y)
	{
		to = get_vector(i, j + 1, prms->map[j + 1][i][0]);
		ft_put_line(prms, from, to);
	}
}

void	ft_draw(t_params *prms)
{
	int			i;
	int			j;

	mlx_clear_window(prms->mlx, prms->win);
	j = -1;
	while (++j < prms->m)
	{
		i = -1;
		while (++i < prms->n)
		{
			prms->img[(j * prms->n + i) * 4 + A] = 0xff;
			prms->deep_map[j * prms->n + i] = -1.0 / 0.0;
		}
	}
	j = -1;
	while (++j < prms->y)
	{
		i = -1;
		while (++i < prms->x)
			put_sector(prms, i, j);
	}
	mlx_put_image_to_window(prms->mlx, prms->win, prms->img_ptr, 0, 0);
}

void	get_img(t_params *prms)
{
	int			bits_per_pixel;
	int			size_line;
	int			endian;

	prms->mlx = mlx_init();
	prms->win = mlx_new_window(prms->mlx, prms->n, prms->m, "mlx 42");
	prms->img_ptr = mlx_new_image(prms->mlx, prms->n, prms->m);
	prms->img = mlx_get_data_addr(prms->img_ptr, &bits_per_pixel, \
			&size_line, &endian);
}

int		main(int ac, char **av)
{
	t_params	prms;

	ft_bzero(&prms, sizeof(prms));
	if (ac != 2 && ac != 4)
		ft_exit(1, NULL);
	if (ac == 4)
	{
		prms.n = ft_atoi(av[2]);
		prms.m = ft_atoi(av[3]);
		if (!prms.n || !prms.m)
			ft_exit(1, NULL);
	}
	ft_read(open(av[1], O_RDONLY), &prms);
	ft_initialize(&prms);
	get_img(&prms);
	ft_draw(&prms);
	mlx_hook(prms.win, 2, 0, &ft_key_press, &prms);
	mlx_hook(prms.win, 4, 0, &ft_mouse_press, &prms);
	mlx_hook(prms.win, 5, 0, &ft_mouse_release, &prms);
	mlx_hook(prms.win, 6, 0, &ft_mouse_move, &prms);
	mlx_hook(prms.win, 17, 0, &ft_close, &prms);
	mlx_loop(prms.mlx);
	return (0);
}

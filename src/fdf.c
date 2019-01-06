/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbatz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/06 08:41:09 by kbatz             #+#    #+#             */
/*   Updated: 2019/01/06 18:07:33 by kbatz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_swap(double *a, double *b)
{
	double	buf;

	buf = *a;
	*a = *b;
	*b = buf;
}

#include <stdio.h>

unsigned int	ft_color(int prev, int new, double k)
{
	int				i;
	unsigned char	*a;
	unsigned char	*b;

	a = (unsigned char *)&new;
	b = (unsigned char *)&prev;
	i = -1;
	while (++i < 4)
	{
		*a = round(*b * (1 - k) + *a * (k));
		a++;
		b++;
	}
	return (new);
}

void		ft_put_pixel(void *mlx, void *win, int x, int y, unsigned int color, double opacity, char is)
{
	int		prev;

	prev = 0;
	//prev = get_color(x, y);
	if (is)
		mlx_pixel_put(mlx, win, y, x, ft_color(prev, color, opacity));
	else
		mlx_pixel_put(mlx, win, x, y, ft_color(prev, color, opacity));
}

void		ft_put_line(void *mlx, void *win, double x0, double y0, double x1, double y1, unsigned int color)
{
	double	k;
	double	yend;
	double	a;
	double	b;
	double	intery;
	int		x;
	int		xend;
	char	is;

	if ((is = fabs(y1 - y0) > fabs(x1 - x0)))
	{
		ft_swap(&x0, &y0);
		ft_swap(&x1, &y1);
	}
	if (x0 > x1)
	{
		ft_swap(&x0, &x1);
		ft_swap(&y0, &y1);
	}
	k = (y1 - y0) / (x1 - x0);
	x = round(x0);
	yend = y0 + k * (x - x0);
	x0 = 1 - modf(x0 + 0.5, &x0);
	a = modf(yend, &y0);
	ft_put_pixel(mlx, win, x, y0, color, (1 - a) * x0, is);
	ft_put_pixel(mlx, win, x, y0 + 1, color, a * x0, is);
	intery = yend + k;
	xend = round(x1);
	yend = y1 + k * (xend - x1);
	x1 = modf(x1 + 0.5, &x1);
	a = modf(yend, &y1);
	ft_put_pixel(mlx, win, xend, y1, color, (1 - a) * x1, is);
	ft_put_pixel(mlx, win, xend, y1 + 1, color, a * x1, is);
	while (++x < xend)
	{
		a = modf(intery, &b);
		ft_put_pixel(mlx, win, x, b, color, 1 - a, is);
		ft_put_pixel(mlx, win, x, b + 1, color, a, is);
		intery += k;
	}
}

void		ft_put_rectangle(void *mlx, void *win, double x0, double y0, double x1, double y1, unsigned int color)
{
	int		i;

	if (y0 > y1)
		ft_swap(&y0, &y1);
	if (x0 > x1)
		ft_swap(&x0, &x1);
	while (y0 <= y1)
	{
		i = x0 - 1;
		while (++i <= x1)
			mlx_pixel_put(mlx, win, i, y0, color);
		y0++;
	}
}

int			ft_close(void *param)
{
	(void)param;
	exit(0);
	return (0);
}

int			main(int ac, char **av)
{
	void			*mlx;
	void			*win;
	void			*img;
	void			*param;
	int				x0;
	int				y0;
	int				x1;
	int				y1;
	int				len;
	int				size;
	int				endian;
	unsigned int	color;
	char			*buf;

	(void)ac;
	(void)av;
	param = NULL;
	x0 = 30;
	y0 = 30;
	x1 = 200;
	y1 = 200;
	color = 0x00ffffff;
	mlx = mlx_init();
	win = mlx_new_window(mlx, 500, 500, "mlx 42");
	img = mlx_new_image(mlx, 100, 100);
	buf = mlx_get_data_addr(img, &len, &size, &endian);
	mlx_put_image_to_window(mlx, win, img, 50, 50);
	//mlx_string_put(mlx, win, x, y, color, ft_itoa(len));
	//y += 50;
	//mlx_string_put(mlx, win, x, y, color, ft_itoa(size));
	//y += 50;
	//mlx_string_put(mlx, win, x, y, color, ft_itoa(endian));
	//mlx_pixel_put(mlx, win, 50, 50, 0x00ffffff);
	ft_put_rectangle(mlx, win, x0, y0, x1, y1, 0x00ffffff);
	ft_put_line(mlx, win, 60, 75, 83, 80, 0x00000000);
	ft_put_line(mlx, win, 250, 100, 273, 105, 0x00ffffff);
	ft_put_line(mlx, win, 160, 70, 160, 20, 0x000000ff);
	ft_put_rectangle(mlx, win, 30, 200, 150, 180, 0x000000);
	mlx_hook(win, 17, 0, &ft_close, param);
	mlx_loop(mlx);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbatz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/06 08:41:09 by kbatz             #+#    #+#             */
/*   Updated: 2019/02/01 18:02:05 by kbatz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_qtrn			*g_qx = NULL;
t_qtrn			*g_qy = NULL;
t_qtrn			*g_qz = NULL;
int				g_shift = 0;

void		ft_draw(t_params *prms);
void		k_qtrn(t_qtrn *q, double k);

void		ft_put_pixel(t_params *prms, int x, int y, int color, double opacity, char is)
{
	color |= (int)round((1 - opacity) * 255) << 24;
	if (is)
		mlx_pixel_put(prms->mlx, prms->win, y + prms->shift.x, x + prms->shift.y, color);
	else
		mlx_pixel_put(prms->mlx, prms->win, x + prms->shift.x, y + prms->shift.y, color);
}

void		ft_put_line_fast(t_params *prms, t_point p0, t_point p1, int color)
{
	char	is;
	int		x;
	int		xend;
	double	k;

	if ((is = fabs(p1.y - p0.y) > fabs(p1.x - p0.x)))
	{
		ft_swap(&p0.x, &p0.y, sizeof(p0.x));
		ft_swap(&p1.x, &p1.y, sizeof(p1.x));
	}
	if (p0.x > p1.x)
	{
		ft_swap(&p0.x, &p1.x, sizeof(p0.x));
		ft_swap(&p0.y, &p1.y, sizeof(p0.y));
	}
	k = (p1.y - p0.y) / (p1.x - p0.x);
	xend = round(p1.x);
	p1.y = k * modf(p0.x, (&p1.x));
	x = (int)p1.x;
	if (round(p1.y))
		p0.y += p1.y;
	else
		p0.y -= p1.y;
	while (x <= xend)
	{
		ft_put_pixel(prms, x, round(p0.y), color, 1, is);
		p0.y += k;
		x++;
	}
}

void		ft_put_line(t_params *prms, t_point p0, t_point p1, int color)
{
	double	k;
	double	yend;
	double	a;
	double	b;
	double	intery;
	int		x;
	int		xend;
	char	is;
	void *mlx, *win;
	double x0, y0, x1, y1;
	mlx = prms->mlx;
	win = prms->win;
	x0 = p0.x;
	y0 = p0.y;
	x1 = p1.x;
	y1 = p1.y;

	if ((is = fabs(y1 - y0) > fabs(x1 - x0)))
	{
		ft_swap(&x0, &y0, sizeof(x0));
		ft_swap(&x1, &y1, sizeof(x1));
	}
	if (x0 > x1)
	{
		ft_swap(&x0, &x1, sizeof(x0));
		ft_swap(&y0, &y1, sizeof(y0));
	}
	k = (y1 - y0) / (x1 - x0);
	x = round(x0);
	yend = y0 + k * (x - x0);
	x0 = 1 - modf(x0 + 0.5, &x0);
	a = modf(yend, &y0);
	ft_put_pixel(prms, x, y0, color, (1 - a) * x0, is);
	ft_put_pixel(prms, x, y0 + 1, color, a * x0, is);
	intery = yend + k;
	xend = round(x1);
	yend = y1 + k * (xend - x1);
	x1 = modf(x1 + 0.5, &x1);
	a = modf(yend, &y1);
	ft_put_pixel(prms, xend, y1, color, (1 - a) * x1, is);
	ft_put_pixel(prms, xend, y1 + 1, color, a * x1, is);
	while (++x < xend)
	{
		a = modf(intery, &b);
		ft_put_pixel(prms, x, b, color, 1 - a, is);
		ft_put_pixel(prms, x, b + 1, color, a, is);
		intery += k;
	}
}

void		ft_put_rectangle(void *mlx, void *win, double x0, double y0, double x1, double y1, int color)
{
	int		i;

	if (y0 > y1)
		ft_swap(&y0, &y1, sizeof(y0));
	if (x0 > x1)
		ft_swap(&x0, &x1, sizeof(x0));
	while (y0 <= y1)
	{
		i = x0 - 1;
		while (++i <= x1)
			mlx_pixel_put(mlx, win, i, y0, color);
		y0++;
	}
}

double		mod_vector(t_vector v)
{
	return (sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
}

void		k_vector(t_vector *v, double k)
{
	v->x *= k;
	v->y *= k;
	v->z *= k;
}

double		mod_qtrn(t_qtrn q)
{
	return (sqrt(q.v.x * q.v.x + q.v.y * q.v.y + q.v.z * q.v.z + q.w * q.w));
}

t_qtrn		rev_qtrn(t_qtrn q)
{
	k_vector(&q.v, -1);
	return (q);
}

void		k_qtrn(t_qtrn *q, double k)
{
	q->v.x *= k;
	q->v.y *= k;
	q->v.z *= k;
	q->w *= k;
}

void		norm_qtrn(t_qtrn *q)
{
	k_qtrn(q, 1 / mod_qtrn(*q));
}

t_vector	add_vector(t_vector a, t_vector b)
{
	t_vector	res;

	res.x = a.x + b.x;
	res.y = a.y + b.y;
	res.z = a.z + b.z;
	return (res);
}

t_qtrn		get_qtrn(t_vector axis, double alpha)
{
	t_qtrn	q;

	k_vector(&axis, sin(alpha) / 2);
	q.v = axis;
	q.w = cos(alpha / 2);
	norm_qtrn(&q);
	return (q);
}

t_qtrn		mul_qtrn(t_qtrn a, t_qtrn b)
{
	t_qtrn	res;

	res.w = a.w * b.w - a.v.x * b.v.x - a.v.y * b.v.y - a.v.z * b.v.z;
	res.v.x = a.w * b.v.x + a.v.x * b.w + a.v.y * b.v.z - a.v.z * b.v.y;
	res.v.y = a.w * b.v.y + a.v.y * b.w + a.v.z * b.v.x - a.v.x * b.v.z;
	res.v.z = a.w * b.v.z + a.v.z * b.w + a.v.x * b.v.y - a.v.y * b.v.x;
	return (res); 
}

t_vector	turn_vector(t_vector v, t_qtrn q, char clockwise)
{
	t_qtrn	tmp;

	tmp.w = 0;
	tmp.v = v;
	if (clockwise)
		tmp = mul_qtrn(mul_qtrn(q, tmp), rev_qtrn(q));
	else
		tmp = mul_qtrn(mul_qtrn(rev_qtrn(q), tmp), q);
	return (tmp.v);
}

void		ft_put_vector(t_params *prms, t_vector from, t_vector v, int color, char fast)
{
	t_point		p0;
	t_point		p1;
	t_point		tmp;
	t_vector	to;
	int			new_color;

	tmp.x = 0;
	tmp.y = 0;
	to = add_vector(from, v);
	from = turn_vector(from, prms->q, 1);
	p0.x = from.x;
	p0.y = from.y;
	to = turn_vector(to, prms->q, 1);
	p1.x = to.x;
	p1.y = to.y;
	if (!fast)
		ft_put_line_fast(prms, p0, p1, color);
	else
		ft_put_line(prms, p0, p1, color);
}

void	ft_exit(int status, t_params *prms)
{
	int		i;

	if (status == USAGE)
		write(1, "usage:\n\t./fdf [file_name]\n\t./fdf [file_name] [size_x > 0] [size_y > 0]\n", 71);
	else if (status == CLOSE || status == ERROR)
	{
		while (prms->m-- > 0)
		{
			i = prms->n;
			while (i-- > 0)
				free(prms->map[prms->m][i]);
			free(prms->map[prms->m]);
		}
		free(prms->map);
		prms->map = NULL;
		free(g_qx);
		free(g_qy);
		mlx_destroy_window(prms->mlx, prms->win);
		if (status == ERROR)
			write(2, "Error\n", 6);
	}
	exit(0);
}

int			ft_close(t_params *prms)
{
	ft_exit(CLOSE, prms);
	return (0);
}

void		ft_initialize(t_params *prms)
{
	t_vector		axis;

	if (!(g_qx = malloc(sizeof(*g_qx))))
		ft_exit(ERROR, prms);
	axis.x = 1;
	axis.y = 0;
	axis.z = 0;
	*g_qx = get_qtrn(axis, ANGLE);
	if (!(g_qy = malloc(sizeof(*g_qy))))
		ft_exit(ERROR, prms);
	axis.x = 0;
	axis.y = 1;
	axis.z = 0;
	*g_qy = get_qtrn(axis, ANGLE);
	if (!(g_qz = malloc(sizeof(*g_qz))))
		ft_exit(ERROR, prms);
	axis.x = 0;
	axis.y = 0;
	axis.z = 1;
	*g_qz = get_qtrn(axis, ANGLE);
	if (!prms->x || !prms->y)
	{
		prms->x = 1000;
		prms->y = 1000;
	}
	prms->shift.x = prms->x / 2;
	prms->shift.y = prms->y / 2;
	prms->q.w = 1;
	ft_bzero(&prms->q.v, sizeof(prms->q.v));
	g_shift = (int)sqrt(prms->x * prms->y) / 40;
	k_qtrn(&prms->q, 10);
}

int			ft_alt_key_press(int keycode, t_params *prms)
{
	if (keycode == 123)
		prms->q = mul_qtrn(prms->q, rev_qtrn(*g_qx));
	else if (keycode == 124)
		prms->q = mul_qtrn(prms->q, *g_qx);
	else if (keycode == 125)
		prms->q = mul_qtrn(prms->q, rev_qtrn(*g_qy));
	else if (keycode == 126)
		prms->q = mul_qtrn(prms->q, *g_qy);
	return (0);
}

int			ft_x_press(int keycode, t_params *prms)
{
	if (keycode == 69)
		prms->q = mul_qtrn(prms->q, *g_qx);
	else if (keycode == 78)
		prms->q = mul_qtrn(prms->q, rev_qtrn(*g_qx));
	return (0);
}

int			ft_y_press(int keycode, t_params *prms)
{
	if (keycode == 69)
		prms->q = mul_qtrn(prms->q, *g_qy);
	else if (keycode == 78)
		prms->q = mul_qtrn(prms->q, rev_qtrn(*g_qy));
	return (0);
}

int			ft_z_press(int keycode, t_params *prms)
{
	if (keycode == 69)
		prms->q = mul_qtrn(prms->q, *g_qz);
	else if (keycode == 78)
		prms->q = mul_qtrn(prms->q, rev_qtrn(*g_qz));
	return (0);
}

int			ft_key_press(int keycode, t_params *prms)
{
	if (prms->alt)
		ft_alt_key_press(keycode, prms);
	else if (prms->xturn)
		ft_x_press(keycode, prms);
	else if (prms->yturn)
		ft_y_press(keycode, prms);
	else if (prms->zturn)
		ft_z_press(keycode, prms);
	else if (keycode == 53)
		ft_close(prms);
	else if (keycode == 259)
		prms->alt = 1;
	else if (keycode == 123)
		prms->shift.x -= g_shift;
	else if (keycode == 124)
		prms->shift.x += g_shift;
	else if (keycode == 125)
		prms->shift.y += g_shift;
	else if (keycode == 126)
		prms->shift.y -= g_shift;
	else if (keycode == 7)
		prms->xturn = 1;
	else if (keycode == 16)
		prms->yturn = 1;
	else if (keycode == 6)
		prms->zturn = 1;
	ft_draw(prms);
	return (0);
}

int			ft_key_release(int keycode, t_params *prms)
{
	if (keycode == 7)
		prms->xturn = 0;
	else if (keycode == 16)
		prms->yturn = 0;
	else if (keycode == 6)
		prms->zturn = 0;
	else if (prms->xturn || prms->yturn || prms->zturn)
		return (0);
	else if (keycode == 259)
		prms->alt = 0;
	else if (keycode == 69)
		k_qtrn(&prms->q, 1.25);
	else if (keycode == 78)
		k_qtrn(&prms->q, 0.8);
	ft_draw(prms);
	return (0);
}

int		ft_mouse_press(int button, int x, int y, t_params *prms)
{
	if (prms->xturn)
	{
		if (button == 5)
			prms->q = mul_qtrn(prms->q, *g_qx);
		else if (button == 4)
			prms->q = mul_qtrn(prms->q, rev_qtrn(*g_qx));
	}
	else if (prms->yturn)
	{
		if (button == 5)
			prms->q = mul_qtrn(prms->q, *g_qy);
		else if (button == 4)
			prms->q = mul_qtrn(prms->q, rev_qtrn(*g_qy));
	}
	else if (prms->zturn)
	{
		if (button == 5)
			prms->q = mul_qtrn(prms->q, *g_qz);
		else if (button == 4)
			prms->q = mul_qtrn(prms->q, rev_qtrn(*g_qz));
	}
	else if (button == 4)
	{
		prms->shift.x = prms->shift.x + (prms->shift.x - x) / 10;
		prms->shift.y = prms->shift.y + (prms->shift.y - y) / 10;
		k_qtrn(&prms->q, 1.25);
	}
	else if (button == 5)
	{
		prms->shift.x = prms->shift.x - (prms->shift.x - x) / 10;
		prms->shift.y = prms->shift.y - (prms->shift.y - y) / 10;
		k_qtrn(&prms->q, 0.8);
	}
	ft_draw(prms);
	return (0);
}

void	ft_cube(t_params *prms, t_vector from, t_vector v, int color)
{
	t_vector	vx, vy, vz;
	t_vector	beg;

	vx.x = v.x;
	vx.y = 0;
	vx.z = 0;
	vy.x = 0;
	vy.y = v.y;
	vy.z = 0;
	vz.x = 0;
	vz.y = 0;
	vz.z = v.z;


	beg.x = from.x + 0;
	beg.y = from.y + 0;
	beg.z = from.z + 0;
	ft_put_vector(prms, beg, vx, color, 1);
	ft_put_vector(prms, beg, vy, color, 1);
	ft_put_vector(prms, beg, vz, color, 1);
	beg.x = from.x + v.x;
	beg.y = from.y + 0;
	beg.z = from.z + 0;
	ft_put_vector(prms, beg, vy, color, 1);
	ft_put_vector(prms, beg, vz, color, 1);
	beg.x = from.x + 0;
	beg.y = from.y + v.y;
	beg.z = from.z + 0;
	ft_put_vector(prms, beg, vx, color, 1);
	ft_put_vector(prms, beg, vz, color, 1);
	beg.x = from.x + 0;
	beg.y = from.y + 0;
	beg.z = from.z + v.z;
	ft_put_vector(prms, beg, vx, color, 1);
	ft_put_vector(prms, beg, vy, color, 1);
	beg.x = from.x + 0;
	beg.y = from.y + v.y;
	beg.z = from.z + v.z;
	ft_put_vector(prms, beg, vx, color, 1);
	beg.x = from.x + v.x;
	beg.y = from.y + 0;
	beg.z = from.z + v.z;
	ft_put_vector(prms, beg, vy, color, 1);
	beg.x = from.x + v.x;
	beg.y = from.y + v.y;
	beg.z = from.z + 0;
	ft_put_vector(prms, beg, vz, color, 1);
}

void	ft_put_axis(t_params *prms)
{
	t_vector	x;
	t_vector	y;
	t_vector	z;
	t_vector	start;
	double		alpha;
	double		step;
	t_vector	v;

	step = 0.1;
	ft_bzero(&x, sizeof(t_vector));
	ft_bzero(&y, sizeof(t_vector));
	ft_bzero(&z, sizeof(t_vector));
	x.x = 2;
	y.y = 2;
	z.z = 2;
	ft_bzero(&start, sizeof(t_vector));
	ft_put_vector(prms, start, x, 0x00ff0000, 0);
	alpha = 0;
	while (alpha < M_PI * 2)
	{
		v.x = -3;
		v.z = sin(alpha);
		v.y = cos(alpha);
		k_vector(&v, 0.1);
		ft_put_vector(prms, x, v, 0x00ff0000, 0);
		alpha += step;
	}
	ft_put_vector(prms, start, y, 0x0000ff00, 0);
	alpha = 0;
	while (alpha < M_PI * 2)
	{
		v.x = sin(alpha);
		v.y = -3;
		v.z = cos(alpha);
		k_vector(&v, 0.1);
		ft_put_vector(prms, y, v, 0x0000ff00, 0);
		alpha += step;
	}
	ft_put_vector(prms, start, z, 0x000000ff, 0);
	alpha = 0;
	while (alpha < M_PI * 2)
	{
		v.x = sin(alpha);
		v.y = cos(alpha);
		v.z = -3;
		k_vector(&v, 0.1);
		ft_put_vector(prms, z, v, 0x000000ff, 0);
		alpha += step;
	}
}

void	ft_draw_map(t_params *prms, t_vector from, int i, int j)
{
	t_vector	v;
	int			color;

	int k = 0;
	while (k < 200000000)
		k++;
	v.x = i;
	v.y = j;
	v.z = prms->map[j][i][0];
	printf("%d, %d\n", i, j);
	color = prms->map[j][i][1];
	ft_put_vector(prms, from, v, color, 1);
	from = add_vector(from, v);
	if (i + 1 < prms->n)
		ft_draw_map(prms, v, i + 1, j);
	if (j + 1 < prms->m)
		ft_draw_map(prms, v, i, j + 1);
}

t_draw	*new_draw(t_params *prms, t_vector from, int i, int j)
{
	t_draw	*tmp;

	tmp = malloc(sizeof(*tmp));
	tmp->from = from;
	tmp->v.x = i;
	tmp->v.y = j;
	tmp->v.z = prms->map[j][i][0];
	tmp->color = prms->map[j][i][1];
	if (!tmp->color)
		tmp->color = 0x00ffffff;
	return (tmp);
}

void	ft_draw(t_params *prms)
{
	int			color;
	t_vector	axis;
	t_vector	v;
	t_vector	from;
	t_qtrn		q;
	t_draw		*tmp;
	t_elem		*elem;
	t_queue		*queue;
	t_draw		*buf;

	mlx_clear_window(prms->mlx, prms->win);
	ft_put_axis(prms);
	from.x = 0.5;
	from.y = 0.5;
	from.z = 0.5;
	v.x = 1;
	v.y = 1;
	v.z = 1;
	ft_cube(prms, from, v, 0x00ffffff);
	queue = ft_queue_new();
	from.x = 0;
	from.y = 0;
	from.z = 0;
	buf = new_draw(prms, from, 0, 0);
/*	ft_queue_push(queue, ft_new_elem(&buf, sizeof(buf), 0));
	while (queue->len)
	{
		elem = ft_queue_pop(queue);
		tmp = (t_draw *)elem->content;
		tmp->v.x++;
		if (tmp->v.x < prms->n)
		{
			ft_put_vector(prms, from, tmp->v, color, 1);
			tmp->from = add_vector(tmp->from, tmp->v);
			buf = new_draw(prms, tmp->from, tmp->v.x, tmp->v.y);
			ft_queue_push(queue, ft_new_elem(&buf, sizeof(buf), 0));
		}
		tmp->v.x--;
		tmp->v.y++;
		if (tmp->v.y < prms->m)
		{
			ft_put_vector(prms, from, tmp->v, color, 1);
			tmp->from = add_vector(tmp->from, tmp->v);
			buf = new_draw(prms, tmp->from, tmp->v.x, tmp->v.y);
			ft_queue_push(queue, ft_new_elem(&buf, sizeof(buf), 0));
		}
		tmp->v.y--;
		free(tmp);
		free(elem);
	}
	free(queue);/*/
}

void	fill_map_elem(int *elem, char **str)
{
	char	sign;

	sign = 1;
	if (**str == '-' || **str == '+')
		sign = 44 - *(*str)++;
	while (ft_isdigit(**str))
		elem[0] = elem[0] * 10 + *(*str)++ - '0';
	elem[0] *= sign;
	if (*(*str) == ',')
	{
		(*str)++;
		while (ft_isdigit(*(++*str)) || \
				(ft_tolower(**str) >= 'a' && ft_tolower(**str) <= 'f'))
		{
			if (ft_isdigit(**str))
				elem[1] |= **str - '0';
			else
				elem[1] |= **str - 'a' + 10;
			elem[1] <<= 4;
		}
	}
}

void	ft_read(char *file, t_params *prms)
{
	int		fd;
	char	*str;
	char	b;
	int		***map;
	int		len;
	int		k;

	map = NULL;
	len = 0;
	fd = open(file, O_RDONLY);
	while ((b = get_next_line(fd, &str) > 0))
	{
		map = ft_realloc(map, sizeof(*map) * len, 1);
		k = 0;
		while (*str)
		{
			while (ft_isspace(*str))
				str++;
			if (*str == '-' || *str == '+' || ft_isdigit(*str))
			{
				map[len] = ft_realloc(map[len], sizeof(**map) * k, 1);
				map[len][k] = ft_memalloc(sizeof(***map) * 2);
				fill_map_elem(map[len][k++], &str);
			}
		}
		len++;
		//free(str);
		if (!prms->n)
			prms->n = k;
		else if (prms->n != k)
		{
			prms->m = len - 1;
			close(fd);
			while (k-- > 0)
				free(map[prms->m][k]);
			free(map[prms->m]);
			ft_exit(ERROR, prms);
		}
	}
	prms->m = len;
	close(fd);
	prms->map = map;
	if (b == -1)
		ft_exit(ERROR, prms);
}

int		main(int ac, char **av)
{
	t_params	prms;
	int			**map;

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
	ft_read(av[1], &prms);
	int j = -1;
	if (prms.map)
		while (++j < prms.m)
		{
			int i = -1;
			while (++i < prms.n)
				printf("%d ", prms.map[j][i][0]);
			printf("\n");
		}
	ft_initialize(&prms);
	prms.mlx = mlx_init();
	prms.win = mlx_new_window(prms.mlx, prms.x, prms.y, "mlx 42");
	ft_draw(&prms);
	mlx_hook(prms.win, 2, 0, &ft_key_press, &prms);
	mlx_hook(prms.win, 3, 0, &ft_key_release, &prms);
	mlx_hook(prms.win, 17, 0, &ft_close, &prms);
	mlx_hook(prms.win, 4, 0, &ft_mouse_press, &prms);
	mlx_loop(prms.mlx);
	return (0);
}

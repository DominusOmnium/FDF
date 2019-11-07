/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkathlee <dkathlee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 13:04:27 by dkathlee          #+#    #+#             */
/*   Updated: 2019/11/07 14:21:06 by dkathlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	put_pixel_img(t_point2d s, t_point2d p, t_point2d e, t_view *view)
{
	int			i;

	if (p.x >= MENU_WIDTH && p.x < WIDTH && p.y >= 0 && p.y < HEIGHT)
	{
		calc_pixel_color(s, e, &p);
		i = (p.x) + (p.y * view->line_size / 4);
		(view->data_addr)[i].r = p.color.r;
		(view->data_addr)[i].g = p.color.g;
		(view->data_addr)[i].b = p.color.b;
	}
}

static void	draw_line(t_point2d p1, t_point2d p2, t_view *view)
{
	t_point2d	delta;
	t_point2d	sign;
	t_point2d	cur;
	int			error[2];

	delta.x = (ABS((p1.x - p2.x)));
	delta.y = (ABS((p2.y - p1.y)));
	sign.x = p1.x < p2.x ? 1 : -1;
	sign.y = p1.y < p2.y ? 1 : -1;
	error[0] = delta.x - delta.y;
	cur = p1;
	while (cur.x != p2.x || cur.y != p2.y)
	{
		put_pixel_img(p1, cur, p2, view);
		if ((error[1] = error[0] * 2) > -delta.y)
		{
			error[0] -= delta.y;
			cur.x += sign.x;
		}
		if (error[1] < delta.x)
		{
			error[0] += delta.x;
			cur.y += sign.y;
		}
	}
}

static void	draw_background(t_view *view)
{
	int	*image;
	int	i;

	image = (int *)(view->data_addr);
	i = 0;
	while (i < HEIGHT * WIDTH)
	{
		if (i % WIDTH <= MENU_WIDTH)
			image[i] = COLOR_MENU;
		else
			image[i] = COLOR_BGR;
		i++;
	}
}

static void	draw_menu(t_view *v)
{
	print_rotation(v);
	print_translation(v);
	print_scale(v);
	mlx_string_put(v->mlx, v->win, 10, 465, COLOR_TEXT_DEF,
											"Projection (I and P keys)");
	if (v->projection == ISO)
		mlx_string_put(v->mlx, v->win, 10, 500, COLOR_TEXT_DEF, "I: Isometric");
	else
		mlx_string_put(v->mlx, v->win, 10, 500, COLOR_TEXT_DEF, "Parallel");
	print_controls(v);
}

void		draw_map(t_view *v)
{
	int			i;
	int			j;
	t_point3d	**p;
	t_point2d	p2d;

	draw_background(v);
	i = 0;
	p = v->map->points3d;
	while (i < v->map->h)
	{
		j = 0;
		while (j < v->map->w)
		{
			p2d = project(p[i][j], v);
			if (j < v->map->w - 1)
				draw_line(p2d, project(p[i][j + 1], v), v);
			if (i < v->map->h - 1)
				draw_line(p2d, project(p[i + 1][j], v), v);
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(v->mlx, v->win, v->img, 0, 0);
	draw_menu(v);
}

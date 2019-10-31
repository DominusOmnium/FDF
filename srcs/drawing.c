/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkathlee <dkathlee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 13:04:27 by dkathlee          #+#    #+#             */
/*   Updated: 2019/10/31 17:40:50 by dkathlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	put_pixel_img(t_point2d *p, t_view *view)
{
	int i;

	if (p->x >= 0 && p->x < WIDTH && p->y >= 0 && p->y < HEIGHT)
	{
		i = (p->x) + (p->y * view->line_size / 4);
		(view->data_addr)[i].r = p->color.r;
		(view->data_addr)[i].g = p->color.g;
		(view->data_addr)[i].b = p->color.b;
		(view->data_addr)[i].a = p->color.a;
		(view->data_addr)[i].b = 255;
	}
}

static void	draw_line(t_point2d *p1, t_point2d *p2, t_view *view)
{
	int dx;
	int dy;
	int sign_x;
	int sign_y;
	int error[2];

	dx = (ABS((p1->x - p2->x)));
	dy = (ABS((p2->y - p1->y)));
	sign_x = p1->x < p2->x ? 1 : -1;
	sign_y = p1->y < p2->y ? 1 : -1;
	error[0] = dx - dy;
	while (p1->x != p2->x || p1->y != p2->y)
	{
		put_pixel_img(p1, view);
		if ((error[1] = error[0] * 2) > -dy)
		{
			error[0] -= dy;
			p1->x += sign_x;
		}
		if (error[1] < dx)
		{
			error[0] += dx;
			p1->y += sign_y;
		}
	}
}

static void	draw_line_f(t_point2d *p1, t_point2d *p2, t_view *view)
{
	draw_line(p1, p2, view);
	ft_memdel((void**)&p1);
	ft_memdel((void**)&p2);
}

static void	draw_background(t_view *view)
{
	int	*image;
	int	i;

	ft_bzero(view->data_addr, WIDTH * HEIGHT * (view->bpp / 8));
	image = (int *)(view->data_addr);
	i = 0;
	while (i < HEIGHT * WIDTH)
	{
		image[i] = 0;
		i++;
	}
}

void		draw_map(t_view *v)
{
	int			i;
	int			j;
	t_point2d	*p1;
	t_point2d	*p2;

	draw_background(v);
	i = 0;
	while (i < v->map->height)
	{
		j = 0;
		while (j < v->map->width)
		{
			if (j < v->map->width - 1)
				draw_line_f(project((v->map->points3d)[i][j], v),
							project((v->map->points3d)[i][j + 1], v), v);
			if (i < v->map->height - 1)
				draw_line_f(project((v->map->points3d)[i][j], v),
							project((v->map->points3d)[i + 1][j], v), v);
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(v->mlx, v->win, v->img, 0, 0);
}

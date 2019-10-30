/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: celva <celva@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 13:04:27 by dkathlee          #+#    #+#             */
/*   Updated: 2019/10/31 02:43:51 by celva            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	put_pixel_img(t_point2D *p, t_view *view)
{
	int i;
	
	if (p->X >= 0 && p->X < WIDTH && p->Y >= 0 && p->Y < HEIGHT)
	{
		i = (p->X) + (p->Y * view->line_size/8);
		(view->data_addr)[i].r = p->color.r;
		(view->data_addr)[i].g = p->color.g;
		(view->data_addr)[i].b = p->color.b;
		(view->data_addr)[i].a = p->color.a;
	}
}

void drawLine(t_point2D *p1, t_point2D *p2, t_view *view)
{
    int dx;
    int dy;
    int signX;
    int signY;
    int error[2];

	dx = (ABS((p1->X - p2->X)));
	dy = (ABS((p2->Y - p1->Y)));
	signX = p1->X < p2->X ? 1 : -1;
	signY = p1->Y < p2->Y ? 1 : -1;
	error[0] = dx - dy;
	while (p1->X != p2->X || p1->Y != p2->Y) 
	{
		p1->color.r = 100;
		p1->color.g = 0;
		p1->color.b = 0;
		p1->color.a = 0;
		put_pixel_img(p1, view);
		//mlx_pixel_put(view->mlx, view->win, p1->X, p1->Y, 255)
		if ((error[1] = error[0] * 2) > -dy) 
		{
			error[0] -= dy;
			p1->X += signX;
		}
		if (error[1] < dx) 
		{
			error[0] += dx;
			p1->Y += signY;
		}
	}
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
		image[i] = 255;
		i++;
	}
}

void		draw_map(t_view *v)
{
	int i;
	int j;
	t_point2D	*p1;
	t_point2D	*p2;

	draw_background(v);
	i = 0;
	while (i < v->map->Height)
	{
		j = 0;
		while (j < v->map->Width)
		{
			if (j < v->map->Width - 1)
				drawLine(iso((v->map->points3D)[i] + j),
							iso((v->map->points3D)[i] + j + 1), v);
			if (i < v->map->Height - 1)
				drawLine(iso((v->map->points3D)[i] + j),
							iso((v->map->points3D)[i + 1] + j), v);
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(v->mlx, v->win, v->img, 0, 0);
}

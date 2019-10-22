/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkathlee <dkathlee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 02:39:25 by marvin            #+#    #+#             */
/*   Updated: 2019/10/22 15:28:08 by dkathlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		prepare_points(t_point *p1, t_point *p2)
{
	int tmp;
	int ret;
	
	ret = 0;
	if (ABS(((p2->Y) - (p1->Y))) > ABS(((p2->X) - (p1->X))))
	{
		tmp = p1->X;
		p1->X = p1->Y;
		p1->Y = tmp;
		tmp = p2->X;
		p2->X = p2->Y;
		p2->Y = tmp;
		ret = 1;
	}
	if (p1->X > p2->X)
	{
		tmp = p1->X;
		p1->X = p2->X;
		p2->X = tmp;
		tmp = p1->Y;
		p1->Y = p2->Y;
		p2->Y = tmp;
	}
	return (ret);
}

void	draw_line(t_point *p, t_view *param)
{
	int	error;
	int	derr;
	int	dir;
	int	dx;
	int flag;
	
	flag = prepare_points(param->prev_p, p);
	dx = (ABS((p->X - param->prev_p->X)));
	dir = p->Y - param->prev_p->Y;
	derr = (ABS(dir));
	dir = dir > 0 ? 1 : -1;
	error = 0;
	while (++(param->prev_p->X) < p->X)
	{
		if (flag == 1)
			mlx_pixel_put(param->mlx_ptr, param->win_ptr, param->prev_p->Y, param->prev_p->X, 255);
		else
			mlx_pixel_put(param->mlx_ptr, param->win_ptr, param->prev_p->X, param->prev_p->Y, 255);	
		error += derr;
		if (2 * error >= derr)
		{
			param->prev_p->Y += dir;
			error -= dx;
		}
	}
}

int mouse_hook(int button, int X, int Y, t_view *param)
{
	t_point	p;
	
	p.X = X;
	p.Y = Y;
	if (param->prev_p->X != 0 && param->prev_p->Y != 0)
		draw_line(&p, param);
	param->prev_p->X = X;
	param->prev_p->Y = Y;
	mlx_pixel_put(param->mlx_ptr, param->win_ptr, X, Y, 255);
}

int	main(int ac, char **av)
{
	t_view *v;

	v = ft_memalloc(sizeof(t_view));
	v->prev_p = ft_memalloc(sizeof(t_point));
	v->mlx_ptr = mlx_init();
	v->win_ptr = mlx_new_window(v->mlx_ptr, WIDTH, HEIGHT, "FdF");
	mlx_mouse_hook(v->win_ptr, &mouse_hook, v);
	mlx_loop(v->mlx_ptr);
	return (0);
}

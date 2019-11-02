/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkathlee <dkathlee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 14:36:01 by dkathlee          #+#    #+#             */
/*   Updated: 2019/11/02 16:23:09 by dkathlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void		free_all(t_view *view)
{
	ft_memdel((void**)&view);
	ft_memdel((void**)&(view->map));
	ft_memdel((void**)&(view->zbuff));
	if (view->img != NULL)
		mlx_destroy_image(view->mlx, view->img);
	if (view->win != NULL)
		mlx_destroy_window(view->mlx, view->win);
}

static t_map	*new_map(void)
{
	t_map *m;

	if ((m = (t_map*)ft_memalloc(sizeof(t_map))) == NULL)
		return (NULL);
	m->min_z = INT_MAX;
	m->max_z = INT_MIN;
	m->min_color = rand_color();
	m->max_color = rand_color();
	return (m);
}

t_view			*new_view(void)
{
	t_view	*view;

	if ((view = ft_memalloc(sizeof(t_view))) == NULL ||
		(view->map = new_map()) == NULL ||
		(view->mlx = mlx_init()) == NULL ||
		(view->zbuff = ft_memalloc(sizeof(float) * WIDTH * HEIGHT)) == NULL ||
		(view->win = mlx_new_window(view->mlx, WIDTH, HEIGHT, "FdF")) == NULL ||
		(view->img = mlx_new_image(view->mlx, WIDTH, HEIGHT)) == NULL ||
		(view->data_addr = (t_color*)mlx_get_data_addr(view->img, &(view->bpp),
		&(view->line_size), &(view->endian))) == NULL)
	{
		free_all(view);
		return (NULL);
	}
	view->tr_type = tr_scale_ALL;
	view->projection = ISO;
	return (view);
}

static int		wind_close(void *param)
{
	(void)param;
	exit(0);
}

void			setup_hooks(t_view *v)
{
	mlx_mouse_hook(v->win, &mouse_press, v);
	mlx_hook(v->win, 5, 0, &mouse_release, v);
	mlx_hook(v->win, 6, 0, &mouse_move, v);
	mlx_key_hook(v->win, &key_press, v);
	mlx_hook(v->win, 17, 0, &wind_close, v);
}

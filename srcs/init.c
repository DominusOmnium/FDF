/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkathlee <dkathlee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 14:36:01 by dkathlee          #+#    #+#             */
/*   Updated: 2019/11/01 18:19:18 by dkathlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	free_all(t_view *view)
{
	printf("Error\n");
	ft_memdel((void**)&view);
	ft_memdel((void**)&(view->transform));
	ft_memdel((void**)&(view->map));
	ft_memdel((void**)&(view->zbuff));
	if (view->img != NULL)
		mlx_destroy_image(view->mlx, view->img);
	if (view->win != NULL)
		mlx_destroy_window(view->mlx, view->win);
}

t_view		*new_view(void)
{
	t_view	*view;

	if ((view = ft_memalloc(sizeof(t_view))) == NULL ||
		(view->transform = ft_memalloc(sizeof(t_transform))) == NULL ||
		(view->map = (t_map*)ft_memalloc(sizeof(t_map))) == NULL ||
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
	view->transform->scale.x = 1;
	view->transform->scale.y = 1;
	view->transform->scale.z = 1;
	view->tr_type = tr_scale_ALL;
	view->projection = ISO;
	view->map->min_z = INT_MAX;
	view->map->max_z = INT_MIN;
	view->map->min_color = rand_color();
	view->map->max_color = rand_color();
	return (view);
}

static int	wind_close(void *param)
{
	(void)param;
	exit(0);
}

void		setup_hooks(t_view *v)
{
	mlx_mouse_hook(v->win, &mouse_press, v);
	mlx_hook(v->win, 5, 0, &mouse_release, v);
	mlx_hook(v->win, 6, 0, &mouse_move, v);
	mlx_key_hook(v->win, &key_press, v);
	mlx_hook(v->win, 17, 0, &wind_close, v);
}

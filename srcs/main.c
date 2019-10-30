/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: celva <celva@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 02:39:25 by marvin            #+#    #+#             */
/*   Updated: 2019/10/31 02:46:12 by celva            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_point2D	*iso(t_point3D *p)
{
	t_point2D	*newP;

	newP = ft_memalloc(sizeof(t_point2D));
	newP->color = p->color;
	newP->X = (p->X - p->Y) * cos(RAD(30)) + WIDTH/2;
	newP->Y = -(p->Z) - (p->X + p->Y) * sin(RAD(30)) + HEIGHT/2;
	return (newP);
}

void	free_all(t_view *view)
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

t_view	*new_view()
{
	t_view	*view;

	if ((view = ft_memalloc(sizeof(t_view))) == NULL ||
		(view->transform = ft_memalloc(sizeof(t_transform))) == NULL ||
		(view->map = ft_memalloc(sizeof(t_map))) == NULL ||
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
}

int	main(int ac, char **av)
{
	t_view *v;

	printf("%d\n", sizeof(t_color));
	v = new_view();
	if (read_map(av[1], v->map) != 1)
		ft_putendl("Error reading");
	draw_map(v);
	mlx_mouse_hook(v->win, &mouse_hook, v);
	mlx_key_hook(v->win, &key_hook, v);
	mlx_loop(v->mlx);
	return (0);
}

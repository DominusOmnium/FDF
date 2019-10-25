/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkathlee <dkathlee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 02:39:25 by marvin            #+#    #+#             */
/*   Updated: 2019/10/25 17:41:51 by dkathlee         ###   ########.fr       */
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


int	main(int ac, char **av)
{
	t_view *v;

	v = ft_memalloc(sizeof(t_view));
	v->mlx_ptr = mlx_init();
	v->win_ptr = mlx_new_window(v->mlx_ptr, WIDTH, HEIGHT, "FdF");
	v->map = ft_memalloc(sizeof(t_map));
	v->tr_type = tr_scale_ALL;
	if (read_map(av[1], v->map) != 1)
		ft_putendl("Error reading");
	draw_map(v);
	mlx_mouse_hook(v->win_ptr, &mouse_hook, v);
	mlx_key_hook(v->win_ptr, &key_hook, v);
	mlx_loop(v->mlx_ptr);
	return (0);
}

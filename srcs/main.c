/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: celva <celva@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 02:39:25 by marvin            #+#    #+#             */
/*   Updated: 2019/11/01 02:19:33 by celva            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int			main(int ac, char **av)
{
	t_view *v;

	v = new_view();
	if (read_map(av[1], v->map) != 1)
		ft_putendl("Error reading");
	draw_map(v);
	mlx_mouse_hook(v->win, &mouse_press, v);
	mlx_key_hook(v->win, &key_press, v);
	mlx_loop(v->mlx);
	return (0);
}

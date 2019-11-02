/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkathlee <dkathlee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 02:39:25 by marvin            #+#    #+#             */
/*   Updated: 2019/11/02 16:24:51 by dkathlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	set_scale(t_view *v)
{
	float	scale;
	
	scale = MIN(WIDTH / (v->map->w * 2.0), HEIGHT / (v->map->h * 2.0));
	v->transform.scale.x = scale;
	v->transform.scale.y = scale;
	v->transform.scale.z = scale;
}

int			main(int ac, char **av)
{
	t_view	*v;

	v = new_view();
	if (read_map(av[1], v->map) != 1)
		ft_putendl("Error reading");
	set_scale(v);
	draw_map(v);
	setup_hooks(v);
	mlx_loop(v->mlx);
	return (0);
}

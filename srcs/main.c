/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkathlee <dkathlee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 02:39:25 by marvin            #+#    #+#             */
/*   Updated: 2019/11/07 14:15:47 by dkathlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	return_mes(char *s)
{
	ft_putendl(s);
	return (0);
}

int			main(int ac, char **av)
{
	t_view	*v;

	if (ac != 2)
		return (return_mes("Usage:\t./fdf FILENAME"));
	if ((v = new_view()) == NULL)
		return (return_mes("Memory allocation error"));
	if (read_map(av[1], v->map) != 1)
		return (return_mes("Reading map error"));
	set_scale(v);
	draw_map(v);
	setup_hooks(v);
	mlx_loop(v->mlx);
	return (0);
}

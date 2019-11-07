/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkathlee <dkathlee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 12:44:13 by dkathlee          #+#    #+#             */
/*   Updated: 2019/11/07 14:35:53 by dkathlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	print_rotation(t_view *v)
{
	char	*str;

	mlx_string_put(v->mlx, v->win, 10, 15, COLOR_TEXT_DEF,
										"Rotation (right mouse button)");
	mlx_string_put(v->mlx, v->win, 25, 50, COLOR_TEXT_DEF, "X:");
	str = ft_itoa(v->transform.rotation.x);
	mlx_string_put(v->mlx, v->win, 150, 50, COLOR_TEXT_DEF, str);
	ft_memdel((void**)&str);
	mlx_string_put(v->mlx, v->win, 25, 75, COLOR_TEXT_DEF, "Y:");
	str = ft_itoa(v->transform.rotation.y);
	mlx_string_put(v->mlx, v->win, 150, 75, COLOR_TEXT_DEF, str);
	ft_memdel((void**)&str);
	mlx_string_put(v->mlx, v->win, 25, 100, COLOR_TEXT_DEF, "Z:");
	str = ft_itoa(v->transform.rotation.z);
	mlx_string_put(v->mlx, v->win, 150, 100, COLOR_TEXT_DEF, str);
	ft_memdel((void**)&str);
}

void	print_translation(t_view *v)
{
	char	*str;

	mlx_string_put(v->mlx, v->win, 10, 165, COLOR_TEXT_DEF,
										"Translation (left mouse button)");
	mlx_string_put(v->mlx, v->win, 25, 200, COLOR_TEXT_DEF, "X:");
	str = ft_itoa(v->transform.translation.x);
	mlx_string_put(v->mlx, v->win, 150, 200, COLOR_TEXT_DEF, str);
	ft_memdel((void**)&str);
	mlx_string_put(v->mlx, v->win, 25, 225, COLOR_TEXT_DEF, "Y:");
	str = ft_itoa(v->transform.translation.y);
	mlx_string_put(v->mlx, v->win, 150, 225, COLOR_TEXT_DEF, str);
	ft_memdel((void**)&str);
	mlx_string_put(v->mlx, v->win, 25, 250, COLOR_TEXT_DEF, "Z:");
	str = ft_itoa(v->transform.translation.z);
	mlx_string_put(v->mlx, v->win, 150, 250, COLOR_TEXT_DEF, str);
	ft_memdel((void**)&str);
}

void	print_scale(t_view *v)
{
	char	*str;

	mlx_string_put(v->mlx, v->win, 10, 315, COLOR_TEXT_DEF,
										"Scale (mouse wheel)");
	mlx_string_put(v->mlx, v->win, 25, 350, COLOR_TEXT_DEF, "X:");
	str = ft_itoa((int)v->transform.scale.x);
	mlx_string_put(v->mlx, v->win, 150, 350, COLOR_TEXT_DEF, str);
	ft_memdel((void**)&str);
	mlx_string_put(v->mlx, v->win, 25, 375, COLOR_TEXT_DEF, "Y:");
	str = ft_itoa((int)v->transform.scale.y);
	mlx_string_put(v->mlx, v->win, 150, 375, COLOR_TEXT_DEF, str);
	ft_memdel((void**)&str);
	mlx_string_put(v->mlx, v->win, 25, 400, COLOR_TEXT_DEF, "Z:");
	str = ft_itoa((int)v->transform.scale.z);
	mlx_string_put(v->mlx, v->win, 150, 400, COLOR_TEXT_DEF, str);
	ft_memdel((void**)&str);
}

void	print_controls(t_view *v)
{
	mlx_string_put(v->mlx, v->win, 10, 565, COLOR_TEXT_DEF, "Controls:");
	mlx_string_put(v->mlx, v->win, 10, 600, COLOR_TEXT_DEF, "A: scale only X");
	mlx_string_put(v->mlx, v->win, 10, 625, COLOR_TEXT_DEF, "S: scale only Y");
	mlx_string_put(v->mlx, v->win, 10, 650, COLOR_TEXT_DEF, "D: scale only Z");
	mlx_string_put(v->mlx, v->win, 10, 675, COLOR_TEXT_DEF, "F: scale all");
	mlx_string_put(v->mlx, v->win, 10, 700, COLOR_TEXT_DEF,
													"I: ISO projection");
	mlx_string_put(v->mlx, v->win, 10, 725, COLOR_TEXT_DEF,
													"P: Parallel projection");
	mlx_string_put(v->mlx, v->win, 10, 750, COLOR_TEXT_DEF,
													"R: reset transform");
}

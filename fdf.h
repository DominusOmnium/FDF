/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkathlee <dkathlee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 02:39:56 by marvin            #+#    #+#             */
/*   Updated: 2019/10/23 12:07:56 by dkathlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <math.h>
# include "libft.h"
# include "mlx.h"
# define HEIGHT	1080
# define WIDTH	1920

typedef struct	s_point3D
{
	int	X;
	int Y;
	int Z;
	int	color;
}				t_point3D;

typedef struct	s_point2D
{
	int	X;
	int Y;
	int	color;
}				t_point2D;

typedef struct	s_map
{
	t_point3D	**points3D;
	t_point2D	**points;
}				t_map;


typedef struct	s_view
{
	void	*mlx_ptr;
	void	*win_ptr;
	t_point2D	*prev_p;
}				t_view;
#endif

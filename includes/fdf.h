/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkathlee <dkathlee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 02:39:56 by marvin            #+#    #+#             */
/*   Updated: 2019/10/24 16:33:12 by dkathlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <mlx.h>
# include <math.h>
# include "libft.h"
# define HEIGHT	1080
# define WIDTH	1920
# define RAD(Value) ((Value) * 0.0174533)

enum AXIS { X, Y, Z	};

typedef struct	s_point3D
{
	float	X;
	float	Y;
	float	Z;
	int		color;
}				t_point3D;

typedef struct	s_point2D
{
	float	X;
	float	Y;
	int		color;
}				t_point2D;

typedef struct	s_map
{
	float		minZ;
	float		maxZ;
	int			Width;
	int			Height;		
	t_point3D	**points3D;
}				t_map;


typedef struct	s_view
{
	void	*mlx_ptr;
	void	*win_ptr;
	void	*img;
	t_point2D *prevP;
	t_map	*map;
}				t_view;

int		read_map(char *fname, t_map *map);
#endif

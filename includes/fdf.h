/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkathlee <dkathlee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 02:39:56 by marvin            #+#    #+#             */
/*   Updated: 2019/10/25 14:07:21 by dkathlee         ###   ########.fr       */
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
# include "buttons.h"
# define HEIGHT	1080
# define WIDTH	1920
# define RAD(Value) ((Value) * 0.0174533)

typedef enum	e_transform_type
{
	tr_rot_X, tr_rot_Y, tr_rot_Z,
	tr_translate_X, tr_translate_Y, tr_translate_Z,
	tr_scale_X, tr_scale_Y, tr_scale_Z, tr_scale_ALL 
}				t_transform_type;

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

typedef struct	s_transform
{
	t_point3D	rotation;
	t_point3D	translation;
	t_point3D	scale;
}				t_transform;

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
	void				*mlx_ptr;
	void				*win_ptr;
	void				*img;
	t_transform_type	tr_type;
	t_point2D			*prevP;
	t_map				*map;
}				t_view;

int			read_map(char *fname, t_map *map);
void		p3D_transform(t_map *map, float value, t_transform_type type,
						void (tr)(t_point3D*, float, t_transform_type));
void		p3D_rotate(t_point3D *p, float angle, t_transform_type t);
void		p3D_scale(t_point3D *p, float value, t_transform_type t);
void		p3D_translate(t_point3D *p, float value, t_transform_type t);
int			mouse_hook(int button, int X, int Y, t_view *param);
int			key_hook(int keycode, t_view *v);
void		draw_map(t_view *v);
void		draw_line(t_point2D *p1, t_point2D *p2, t_view *param);
t_point2D	*iso(t_point3D *p);
#endif

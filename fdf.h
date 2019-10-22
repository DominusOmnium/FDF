/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkathlee <dkathlee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 02:39:56 by marvin            #+#    #+#             */
/*   Updated: 2019/10/22 23:36:14 by dkathlee         ###   ########.fr       */
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
typedef struct	s_point
{
	int	X;
	int Y;
	int Z;
	int	color;
}				t_point;

typedef struct	s_view
{
	void	*mlx_ptr;
	void	*win_ptr;
	int		**points;
	t_point	*prev_p;
}				t_view;
#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkathlee <dkathlee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 22:54:22 by dkathlee          #+#    #+#             */
/*   Updated: 2019/10/24 15:47:30 by dkathlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	read_map(char *fname, t_map *map)
{
	int		fd;
	int		i;
	int		wc;
	char	*line;
	char	**splited_line;
	
	if ((fd = open(fname, O_RDONLY)) == -1)
		return (0);
	map->points3D = ft_memalloc(sizeof(t_point3D*));
	i = 0;
	while (get_next_line(fd, &line) == 1)
	{
		map->points3D = ft_realloc(map->points3D, sizeof(t_point3D*) * i, sizeof(t_point3D*) * (i + 1));
		splited_line = ft_strsplit(line, ' ');
		map->Width = ft_word_count(line, ' ');
		(map->points3D)[i] = ft_memalloc(sizeof(t_point3D) * map->Width);
		wc = map->Width;
		while (--wc >= 0)
		{
			(map->points3D)[i][wc].Z = ft_atoi(splited_line[wc]) * 5;
			(map->points3D)[i][wc].X = i * 20 + 500;
			(map->points3D)[i][wc].Y = wc * 20;
		}
		ft_memdel((void**)&line);
		i++;
	}
	map->Height = i;
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkathlee <dkathlee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 22:54:22 by dkathlee          #+#    #+#             */
/*   Updated: 2019/10/22 15:18:32 by dkathlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	read_map(char *fname, t_view *view)
{
	int	fd;
	
	if ((fd = open(fname, O_RDONLY)) == -1)
		return (0);
	if ((view->points = ft_memalloc(sizeof(int*))) == NULL)
}

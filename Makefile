# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dkathlee <dkathlee@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/21 16:29:10 by dkathlee          #+#    #+#              #
#    Updated: 2019/10/22 10:58:39 by dkathlee         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= fdf

all: $(NAME)

$(NAME):
	gcc -o q main.c -I libft -I mlx_linux libft/libft.a mlx_linux/libmlx_Linux.a -lXext -lX11

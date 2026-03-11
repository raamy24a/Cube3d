/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: radib <radib@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 14:35:28 by radib             #+#    #+#             */
/*   Updated: 2026/03/11 00:28:01 by radib            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

static int angle_calculator(char angle)
{
	if (angle == 'N')
		return (0);
	else if (angle == 'E')
		return (90);
	else if (angle == 'S')
		return (180);
	else if (angle == 'W')
		return (270);
	return (0);
}

t_img	*init_image(t_c *p, int height, int width)
{
	t_img	*img;

	img = malloc(sizeof(t_img));
	img->img = mlx_new_image(p->m_ptr, height, width);
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel,
			&img->line_length, &img->endian);
	return (img);
}

void	init_cube(t_c **c, char angle, char **map)
{
	t_c	*p;

	p = (*c);
	p->width = 1000;
	p->height = 1000;
	p->angle = angle_calculator(angle);
	p->fps = 60;
	p->m_ptr = mlx_init();
	p->pos_x = 1.5;
	p->pos_y = 1.5;
	p->w_ptr = mlx_new_window(p->m_ptr, p->width, p->height, "Cube");
	p->raydata = malloc(sizeof(t_r *) * p->width);
	p->map = map;
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: radib <radib@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 14:35:28 by radib             #+#    #+#             */
/*   Updated: 2026/03/16 01:55:45 by radib            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

static int	angle_calculator(char angle)
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
t_img	*init_image_xpm(t_c **c, char *path_to_image)
{
	t_img	*img;
	int		height;
	int		width;
	t_c		*p;

	p = (*c);
	height = 128;
	width = 128;
	img = malloc(sizeof(t_img));
	img->img = mlx_xpm_file_to_image(p->m_ptr, path_to_image, &width, &height);
	if (!img->img)
	{
		free(img);
		return (NULL);
	}
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel,
			&img->line_length, &img->endian);
	return (img);
}

void	put_wall_images_to_struct(t_c **c)
{
	t_c	*p;

	p = (*c);
	p->wall_e = init_image_xpm(c, "xpm/Bricks_e.xpm");
	p->wall_s = init_image_xpm(c, "xpm/Bricks_s.xpm");
	p->wall_w = init_image_xpm(c, "xpm/Bricks_w.xpm");
	p->wall_n = init_image_xpm(c, "xpm/Bricks_n.xpm");
}

void	init_cube(t_c **c, char angle, char **map)
{
	t_c	*p;

	p = (*c);
	p->width = 1000;
	p->height = 1000;
	p->angle = angle_calculator(angle);
	p->m_ptr = mlx_init();
	put_wall_images_to_struct(c);
	p->pos_x = 2.5;
	p->pos_y = 2.5;
	p->w_ptr = mlx_new_window(p->m_ptr, p->width, p->height, "Cube");
	p->raydata = malloc(sizeof(t_ray *) * p->width);
	p->fov = 66.00f;
	p->map = map;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: radib <radib@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 14:35:49 by radib             #+#    #+#             */
/*   Updated: 2026/03/16 03:10:15 by radib            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

#include "../cube3d.h"

float	deg_to_rad(float deg)
{
	return (deg * M_PI / 180.0);
}

float	rad_to_deg(float rad)
{
	return (rad * 180.0f / M_PI);
}

static void	init_deltas(t_ray *r)
{
	if (r->ray_dir_x == 0)
		r->delta_x = 1e30;
	else
		r->delta_x = fabs(1.0f / r->ray_dir_x);
	if (r->ray_dir_y == 0)
		r->delta_y = 1e30;
	else
		r->delta_y = fabs(1.0f / r->ray_dir_y);
}

static void	init_step_x(t_c *p, t_ray *r)
{
	if (r->ray_dir_x < 0)
	{
		r->step_x = -1;
		r->side_dist_x = (p->pos_x - r->map_x) * r->delta_x;
	}
	else
	{
		r->step_x = 1;
		r->side_dist_x = (r->map_x + 1.0f - p->pos_x) * r->delta_x;
	}
}

static void	init_step_y(t_c *p, t_ray *r)
{
	if (r->ray_dir_y < 0)
	{
		r->step_y = -1;
		r->side_dist_y = (p->pos_y - r->map_y) * r->delta_y;
	}
	else
	{
		r->step_y = 1;
		r->side_dist_y = (r->map_y + 1.0f - p->pos_y) * r->delta_y;
	}
}

static void	dda_walk(t_c **c, t_ray *r)
{
	while (1)
	{
		if (r->side_dist_x < r->side_dist_y)
		{
			r->side_dist_x += r->delta_x;
			r->map_x += r->step_x;
			r->side = 0;
		}
		else
		{
			r->side_dist_y += r->delta_y;
			r->map_y += r->step_y;
			r->side = 1;
		}
		if ((*c)->map[r->map_y][r->map_x] == '1')
			break ;
	}
}

static void	fill_ray_result(t_ray *r, t_c *c)
{
	if (r->side == 0)
	{
		r->dist = r->side_dist_x - r->delta_x;
		r->wall_x = c->pos_y + r->dist * r->ray_dir_y;
		if (r->ray_dir_x > 0)
			r->wall = c->wall_e;
		else
			r->wall = c->wall_w;
	}
	else
	{
		r->dist = r->side_dist_y - r->delta_y;
		r->wall_x = c->pos_x + r->dist * r->ray_dir_x;
		if (r->ray_dir_y > 0)
			r->wall = c->wall_s;
		else
			r->wall = c->wall_n;
	}
	r->wall_x = r->wall_x - floor(r->wall_x);
}

static t_ray	*dda(t_c **c, float ray_dir_x, float ray_dir_y)
{
	t_ray	*r;

	r = malloc(sizeof(t_ray));
	if (!r)
		return (NULL);
	r->ray_dir_x = ray_dir_x;
	r->ray_dir_y = ray_dir_y;
	r->map_x = (int)(*c)->pos_x;
	r->map_y = (int)(*c)->pos_y;
	init_deltas(r);
	init_step_x(*c, r);
	init_step_y(*c, r);
	dda_walk(c, r);
	fill_ray_result(r, (*c));
	return (r);
}

int	get_pixel_from_image(t_img *img, int x, int y)
{
	char	*pixel;

	pixel = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	return (*(int *)pixel);
}

static void	init_cam(t_c *p, t_cam *cam)
{
	cam->dir_x = sin(deg_to_rad(p->angle));
	cam->dir_y = -cos(deg_to_rad(p->angle));
	cam->plane_x = cos(deg_to_rad(p->angle)) * tan(deg_to_rad(p->fov / 2));
	cam->plane_y = sin(deg_to_rad(p->angle)) * tan(deg_to_rad(p->fov / 2));
}

static void	cast_rays(t_c **c)
{
	t_c		*p;
	t_cam	cam;
	int		i;

	p = *c;
	init_cam(p, &cam);
	i = 0;
	while (i < p->width)
	{
		cam.camera_x = 2.0f * i / p->width - 1.0f;
		cam.ray_x = cam.dir_x + cam.plane_x * cam.camera_x;
		cam.ray_y = cam.dir_y + cam.plane_y * cam.camera_x;
		p->raydata[i] = dda(c, cam.ray_x, cam.ray_y);
		i++;
	}
}

static void	draw_wall_height_line(t_ray *r, t_img **img, t_c *p, int x)
{
	float	y;
	int		y_end;
	int		wall_size;
	int		color;

	wall_size = p->height / r->dist;
	y = (float)(p->height - wall_size) / 2.0f;
	y_end = y + wall_size;
	if (y < 0)
		y = 0;
	while (y < y_end && y < p->height)
	{
		color = get_pixel_from_image(r->wall, 128 * r->wall_x, (int)((128.00f / wall_size) * (y - (p->height - wall_size) / 2)));
		put_pixel_to_image(*img, x, (int)y, color);
		y++;
	}
}

static void	render_walls(t_c **c)
{
	t_c	*p;
	int	i;

	p = *c;
	i = 0;
	while (i < p->width)
	{
		draw_wall_height_line(p->raydata[i], &p->displayed_img, p, i);
		i++;
	}
}

void	raycast(t_c **c, int i, float angles)
{
	(void)i;
	(void)angles;
	cast_rays(c);
	render_roof(10000 * 0 + 100 * 20 + 20, c);
	render_floor(300 * 10000 + 100 * 100 + 50, c);
	(*c)->displayed_img = (*c)->roof_and_ground;
	render_walls(c);
	mlx_clear_window((*c)->m_ptr, (*c)->w_ptr);
	mlx_put_image_to_window((*c)->m_ptr, (*c)->w_ptr,
		(*c)->displayed_img->img, 0, 0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: radib <radib@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 16:03:09 by radib             #+#    #+#             */
/*   Updated: 2026/03/16 01:35:59 by radib            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
# define CUBE3D_H

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <math.h>
# include "../minilibx/mlx.h"
# include "../libft/libft.h"

# ifndef M_PI
#  define M_PI 3.14159265358979323846
# endif

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_img;


typedef struct s_ray
{
	float	ray_dir_x;
	float	ray_dir_y;
	float	delta_x;
	float	delta_y;
	float	side_dist_x;
	float	side_dist_y;
	int		step_x;
	int		step_y;
	int		map_x;
	int		map_y;
	int		side;
	t_img	*wall;
	float	wall_x;
	float	dist;
}	t_ray;

typedef struct s_cam
{
	float	dir_x;
	float	dir_y;
	float	plane_x;
	float	plane_y;
	float	camera_x;
	float	ray_x;
	float	ray_y;
}	t_cam;

typedef struct s_cube
{
	float	pos_x;
	float	pos_y;
	float	angle;
	char	**map;
	int		width;
	int		height;
	float	fov;
	void	*m_ptr;
	void	*w_ptr;
	t_ray	**raydata;
	t_img	*displayed_img;
	t_img	*roof_and_ground;
	t_img	*wall_n;
	t_img	*wall_s;
	t_img	*wall_e;
	t_img	*wall_w;
}	t_c;

void	init_cube(t_c **c, char angle, char **map);
void	moving(t_c **c, int key);
void	render_roof(int color, t_c **c);
void	render_floor(int color, t_c **c);
t_img	*init_image(t_c *p, int height, int width);
void	put_pixel_to_image(t_img *img, int x, int y, int color);
void	raycast(t_c **c, int i, float angles);
float	deg_to_rad(float deg);

#endif
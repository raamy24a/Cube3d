/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: radib <radib@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 16:03:09 by radib             #+#    #+#             */
/*   Updated: 2026/03/11 00:43:17 by radib            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
# define CUBE3D_H

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include "../minilibx/mlx.h"
# include "math.h"

// temp include
#include <string.h>

# define M_PI           3.14159265358979323846
typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_img;

typedef struct raydata
{
	int		wall;
	float	dist;
}	t_r;

typedef struct cube
{
	float	pos_x;
	float	pos_y;
	double	angle;
	char	**map;
	int		width;
	int		height;
	int		fps;
	void	*m_ptr;
	void	*w_ptr;
	t_r		**raydata;
	t_img	*displayed_img;
	t_img	*roof_and_ground;
}			t_c;
// init
void	init_cube(t_c **c, char angle, char **map);
void	moving(t_c **c, int key);
void	render_roof(int color, t_c **c);
void	render_floor(int color, t_c **c);
t_img	*init_image(t_c *p, int height, int width);
void	put_pixel_to_image(t_img *img, int x, int y, int color);
void	raycast(t_c **c, int i, double angles);

#endif

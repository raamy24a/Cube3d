/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: radib <radib@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 16:03:09 by radib             #+#    #+#             */
/*   Updated: 2026/03/04 14:56:41 by radib            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
# define CUBE3D_H

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include "../minilibx/mlx.h"

typedef struct cube
{
	float	pos_x;
	float	pos_y;
	float	angle;
	char	**map;
	int		width;
	int		height;
	int		fps;
	void	*m_ptr;
	void	*w_ptr;
	void	*roof;
	void	*floor;
}			t_c;
// init
void	init_cube(t_c **c, char angle);
void	moving(t_c **c, int key);
void	render_roof(int color, t_c **c);
void	render_floor(int color, t_c **c);

#endif

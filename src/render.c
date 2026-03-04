/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: radib <radib@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 14:35:41 by radib             #+#    #+#             */
/*   Updated: 2026/03/04 15:01:59 by radib            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

void	render_roof(int color, t_c **c)
{
	int	x;
	int	y;
	t_c	*p;

	p = *c;
	p->roof = mlx_new_image(p->m_ptr, p->height / 2, p->width);
	mlx_get_data_addr(p->roof, 8, )
	y = 0;
	while (y < p->height / 2)
	{
		x = 0;
		while (x < p->width)
		{
			mlx_pixel_put(p->roof, p->w_ptr, x, y, color);
			x++;

		}
		y++;
	}
}

void	render_floor(int color, t_c **c)
{
	int	x;
	int	y;
	t_c	*p;

	p = *c;
	p->floor = mlx_new_image(p->m_ptr, p->height / 2, p->width);
	y = 0;
	while (y < p->height / 2)
	{
		x = 0;
		while (x < p->width)
		{
			mlx_pixel_put(p->floor, p->w_ptr, x, y, color);
			x++;
		}
		y++;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: radib <radib@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 14:35:41 by radib             #+#    #+#             */
/*   Updated: 2026/03/09 02:27:35 by radib            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

void	put_pixel_to_image(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}
void	render_roof(int color, t_c **c)
{
	int	x;
	int	y;
	t_c	*p;

	p = *c;
	p->roof_and_ground = mlx_new_image(p->m_ptr, p->height , p->width);
	y = 0;
	while (y < p->height / 2)
	{
		x = 0;
		while (x < p->width)
		{
			mlx_pixel_put(p->roof_and_ground, NULL, x, y, color);
			(void)color;
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
	y = p->height;
	while (y > p->height / 2)
	{
		x = 0;
		while (x < p->width)
		{
			mlx_pixel_put(p->roof_and_ground, NULL, x, y, color);
			x++;
		}
		y--;
	}
}

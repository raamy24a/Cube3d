/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: radib <radib@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 14:35:41 by radib             #+#    #+#             */
/*   Updated: 2026/03/09 11:39:51 by radib            ###   ########.fr       */
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
	p->roof_and_ground = init_image(p, p->height, p->width);
	y = 0;
	while (y < p->height / 2)
	{
		x = 0;
		while (x < p->width)
		{
			put_pixel_to_image(p->roof_and_ground, x, y, color);
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
			put_pixel_to_image(p->roof_and_ground, x, y, color);
			x++;
		}
		y--;
	}
}

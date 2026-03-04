/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: radib <radib@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 14:35:21 by radib             #+#    #+#             */
/*   Updated: 2026/03/04 14:56:21 by radib            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

void	moving_cam(t_c **c, int key)
{
	if (key == 65361)
	{
		(*c)->angle -= 0.01;
		if ((*c)->angle < 0)
			(*c)->angle = 360;
	}
	else
	{
		(*c)->angle += 0.01;
		if ((*c)->angle > 360)
			(*c)->angle = 0;
	}
}

void	cleanup(t_c **c)
{
	t_c	*z;

	z = *c;
	mlx_clear_window(z->m_ptr, z->w_ptr);
	mlx_destroy_window(z->m_ptr, z->w_ptr);
	mlx_destroy_display(z->m_ptr);
	free(*c);
}

int	handle_key(int key, t_c *c)
{
	if (key == 65307)
		cleanup(&c);
	if (key == 119 || key == 97 || key == 115 || key == 100)
		moving(&c, key);
	if (key == 65361 || key == 65363)
		moving_cam(&c, key);
	return (0);
}

int	cleanup_exit(t_c *c)
{
	mlx_clear_window(c->m_ptr, c->w_ptr);
	mlx_destroy_window(c->m_ptr, c->w_ptr);
	mlx_destroy_display(c->m_ptr);
	exit(0);
}

int	main(void)
{
	t_c	*c;

	c = malloc(sizeof (t_c));
	init_cube(&c, 'N');
	mlx_hook(c->w_ptr, 17, 1L >> 17, cleanup_exit, c);
	mlx_key_hook(c->w_ptr, handle_key, c);
	render_roof(10000 * 0 + 100 * 20 + 20, &c);
	render_floor(300 * 10000 + 100 * 100 + 50, &c);
	mlx_loop(c->m_ptr);
}

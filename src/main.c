/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: radib <radib@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 14:35:21 by radib             #+#    #+#             */
/*   Updated: 2026/03/03 15:15:12 by radib            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	handle_key(int key, t_c *c)
{
	if (key == 65307)
		cleanup(c, 6);
	if (key == 119 || key == 97 || key == 115 || key == 100)
		moving(c, key);
	if (key == 65361 || key == 65363)
		moving_cam(c, key);
	return (0);
}

void init_cube()
{
	
}
int	main(void)
{
	t_c	*c;

	c = malloc(sizeof (t_c));
	init_cube(&c);
	mlx_hook(c->w_ptr, 17, 1L >> 17, cleanup_exit, c);
	mlx_key_hook(c->w_ptr, handle_key, c);
	mlx_loop(c->m_ptr);
}
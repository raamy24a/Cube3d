/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: radib <radib@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 14:35:21 by radib             #+#    #+#             */
/*   Updated: 2026/03/12 20:16:11 by radib            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

void	moving_cam(t_c **c, int key)
{
	if (key == 65361)
	{
		(*c)->angle -= 5.00;
		if ((*c)->angle < 0)
			(*c)->angle = 360 - ((*c)->angle * -1);
		raycast(c, 0, (*c)->angle);
	}
	else
	{
		(*c)->angle += 5.00;
		(*c)->angle = fmodf((*c)->angle, 360.00);
		raycast(c, 0, (*c)->angle);
	}
	printf("angle : %f\n", (*c)->angle);
}

void	cleanup(t_c **c)
{
	t_c	*z;

	z = *c;
	mlx_clear_window(z->m_ptr, z->w_ptr);
	mlx_destroy_window(z->m_ptr, z->w_ptr);
	mlx_destroy_display(z->m_ptr);
	free(*c);
	exit(0);
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

		//temporary code until <---- is reached
	    const char *lines[] = {
        "1111111111111111111111111",
        "1000000000110000000000001",
        "1000000100110000000000001",
        "1000000000000000000000001",
        "111111111111000001110000000000001",
        "100000000011000001110111111111111",
        "11110111111111011100000010001",
        "11110111111111011101010010001",
        "11000000110101011100000010001",
        "10000000000000001100000010001",
        "10000000000000001101010010001",
        "1100000111010101111101111000111",
        "11110111 1110101 101111010001",
        "11111111 1111111 111111111111"
    };
    
    int rows = sizeof(lines) / sizeof(lines[0]);

    // Allocate char** array
    char **map = malloc(rows * sizeof(char*));
    if (!map) {
        perror("malloc failed");
        return 1;
    }

    // Allocate and copy each line
    for (int i = 0; i < rows; i++) {
        map[i] = malloc(strlen(lines[i]) + 1); // +1 for null terminator
        if (!map[i]) {
            perror("malloc failed");
            // free previous allocations
            for (int j = 0; j < i; j++) free(map[j]);
            free(map);
            return 1;
        }
        strcpy(map[i], lines[i]);
    }
	//<----
	c = malloc(sizeof (t_c));
	init_cube(&c, 'N', map);
	mlx_hook(c->w_ptr, 17, 1L >> 17, cleanup_exit, c);
	mlx_key_hook(c->w_ptr, handle_key, c);
	render_roof(10000 * 0 + 100 * 20 + 20, &c);
	render_floor(300 * 10000 + 100 * 100 + 50, &c);
	mlx_put_image_to_window(c->m_ptr, c->w_ptr, c->roof_and_ground->img, 0, 0);
	c->displayed_img = init_image(c, c->height, c->width);
	raycast(&c, 0, c->angle);
	mlx_loop(c->m_ptr);
}
// ESC	65307
// W	119
// A	97
// S	115
// D	100
// UP	65362
// DOWN	65364
// LEFT	65361
// RIGHT	65363
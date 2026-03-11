/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moving.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: radib <radib@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 12:05:26 by radib             #+#    #+#             */
/*   Updated: 2026/03/11 13:50:17 by radib            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

static void	moving_calculator(t_c **c, int angle)
{
	if (angle == 0)
		(*c)->pos_y += 1;
	if (angle == 90)
		(*c)->pos_x += 1;
	if (angle == 180)
		(*c)->pos_y -= 1;
	if (angle == 270)
		(*c)->pos_y -= 1;
	raycast(c, 0, (*c)->angle);
}

void	moving(t_c **c, int key)
{
	if (key == 119)
		moving_calculator(c, 0);
		// moving_calculator((*c)->angle);
	if (key == 97)
		moving_calculator(c, 270);
		// moving_calculator((*c)->angle + 270);
	if (key == 115)
		moving_calculator(c, 180);
		// moving_calculator((*c)->angle + 180);
	if (key == 100)
		moving_calculator(c, 90);
		// moving_calculator((*c)->angle + 90);
}
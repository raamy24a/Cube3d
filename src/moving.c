/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moving.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: radib <radib@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 12:05:26 by radib             #+#    #+#             */
/*   Updated: 2026/03/14 20:03:42 by radib            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"



static void	moving_calculator(t_c **c, int angle)
{
	(*c)->pos_x = (*c)->pos_x + sin(deg_to_rad(angle));
	(*c)->pos_y = (*c)->pos_y - cos(deg_to_rad(angle));
	raycast(c, 0, (*c)->angle);
}

void	moving(t_c **c, int key)
{
	if (key == 119)
		moving_calculator(c, fmodf((*c)->angle, 360.00f));
		// moving_calculator((*c)->angle);
	if (key == 97)
		moving_calculator(c, fmodf(270 + (*c)->angle, 360.00f));
		// moving_calculator((*c)->angle + 270);
	if (key == 115)
		moving_calculator(c, fmodf(180 + (*c)->angle, 360.00f));
		// moving_calculator((*c)->angle + 180);
	if (key == 100)
		moving_calculator(c, fmodf(90 + (*c)->angle, 360.00f));
		// moving_calculator((*c)->angle + 90);
}
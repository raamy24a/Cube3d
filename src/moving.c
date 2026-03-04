/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moving.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: radib <radib@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 12:05:26 by radib             #+#    #+#             */
/*   Updated: 2026/03/04 12:38:36 by radib            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

static void	moving_calculator(int angle)
{
	(void)angle;
}

void	moving(t_c **c, int key)
{
	if (key == 119)
		moving_calculator((*c)->angle);
	if (key == 97)
		moving_calculator((*c)->angle + 270);
	if (key == 115)
		moving_calculator((*c)->angle + 180);
	if (key == 100)
		moving_calculator((*c)->angle + 90);
}
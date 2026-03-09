/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: radib <radib@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 14:35:49 by radib             #+#    #+#             */
/*   Updated: 2026/03/09 16:46:14 by radib            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

float	angle_calc(float angle, float calc)
{
	angle = angle + calc - 33;
	if (angle < 0)
		angle = 360 + angle;
	else if (angle > 360)
		angle = 360 - angle;
	return (angle);
}

int	**raycast(t_c **c, int i, float angles)
{
	t_c		*p;
	float	a;
	float	b;
	float	hyp;

	while (i < p->width)
	{
		p->pos_x;
		p->pos_y;
		angles = angle_calc(p->angle, 66 / p->width * i);
		p->rays[0] = ;
		p->rays[1] = ;
	}
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: radib <radib@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 14:35:49 by radib             #+#    #+#             */
/*   Updated: 2026/03/09 14:49:22 by radib            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

float	angle_calc(float angle, float calc)
{
	angle = angle + calc - 45;
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
		
		p->rays[0] = ;
		p->rays[1] = ;
	}
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: radib <radib@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 14:35:49 by radib             #+#    #+#             */
/*   Updated: 2026/03/10 15:55:41 by radib            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

double	angle_calc(float angle, float calc)
{
	angle = angle + calc - 33;
	if (angle < 0)
		angle = 360 + angle;
	else if (angle > 360)
		angle = 360 - angle;
	return (angle);
}
float	hit_wall_n(t_c *p)
{
	int		i;
	float	temp;

	temp = 1 - (p->pos_y - (int)p->pos_y);
	i = 0;
	while (p->map[(int)p->pos_y - i][(int)p->pos_x] != '1')
		i++;
	return (temp + i);
}
float	hit_wall_e(t_c *p)
{
	float	temp;

	temp = p->pos_x - (int)p->pos_x;
}
float	hit_wall_w(t_c *p)
{
	float	temp;

	temp = p->pos_x - (int)p->pos_x;
}
float	hit_wall_s(t_c *p)
{
	int		i;
	float	temp;

	temp = 1 - (p->pos_y - (int)p->pos_y);
	i = 0;
	while (p->map[(int)p->pos_y + i][(int)p->pos_x] != '1')
		i++;
	return (temp + i);
}

int	**top_left(t_c **c, float a, float b, double angles)
{
	t_c		*p;
	float	hypb;
	float	hypa;
	int		i;

	p = *c;
	angles -= 270;
	b = p->pos_x - (int)p->pos_x;
	a = 1 - (p->pos_y - (int)p->pos_y);
	while (b < )
	{
		
	}
		
		hypb = 1 / (sin(angles) / b);
		
		angles -= 90;
		hypa = 1 / (cos(angles) / a);
	}
}
int	**top_right()
{
	
}
int	**bottom_left()
{
	
}
int	**bottom_right()
{
	
}

int	**raycast(t_c **c, int i, double angles)
{
	t_c		*p;
	float	hyp;

	p = *c;
	while (i < p->width)
	{
		p->pos_x;
		
		angles = angle_calc(p->angle, 66 / p->width * i);
		p->rays[0] = ;
		p->rays[1] = ;
	}
}

a = b/c;

3 = 6/2;


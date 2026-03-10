/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: radib <radib@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 14:35:49 by radib             #+#    #+#             */
/*   Updated: 2026/03/10 17:58:59 by radib            ###   ########.fr       */
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
float	len_to_hit_wall_n(t_c *p)
{
	int		i;
	float	temp;

	temp = 1 - (p->pos_y - (int)p->pos_y);
	i = 0;
	while (p->map[(int)p->pos_y - i][(int)p->pos_x] != '1')
		i++;
	return (temp + i);
}
float	len_to_hit_wall_e(t_c *p)
{
	int		i;
	float	temp;

	temp = p->pos_x - (int)p->pos_x;
	i = 0;
	while (p->map[(int)p->pos_y][(int)p->pos_x - i] != '1')
		i++;
	return (temp + i);
}
float	len_to_hit_wall_w(t_c *p)
{
	int		i;
	float	temp;

	temp = p->pos_x - (int)p->pos_x;
	i = 0;
	while (p->map[(int)p->pos_y][(int)p->pos_x + i] != '1')
		i++;
	return (temp + i);
}
float	len_to_hit_wall_s(t_c *p)
{
	int		i;
	float	temp;

	temp = 1 - (p->pos_y - (int)p->pos_y);
	i = 0;
	while (p->map[(int)p->pos_y + i][(int)p->pos_x] != '1')
		i++;
	return (temp + i);
}

t_r	*top_left(t_c **c, float adj, float opp, double angles)
{
	t_c		*p;
	float	hyp_w;
	float	hyp_n;
	t_r		*raydata;

	raydata = malloc(sizeof(t_c));
	p = *c;
	angles -= 270;
	opp = len_to_hit_wall_w(p);
	adj = len_to_hit_wall_n(p);
	hyp_w = 1 / (sin(angles) / opp);
	angles = 90 - angles;
	hyp_n = 1 / (cos(angles) / adj);
	if (hyp_n > hyp_w)
		return (raydata->dist = hyp_w, raydata->wall = 'w', raydata);
	return (raydata->dist = hyp_n, raydata->wall = 'n', raydata);
}
t_r	*top_right(t_c **c, float adj, float opp, double angles)
{
	t_c		*p;
	float	hyp_e;
	float	hyp_n;
	t_r		*raydata;

	raydata = malloc(sizeof(t_c));
	p = *c;
	opp = len_to_hit_wall_e(p);
	adj = len_to_hit_wall_n(p);
	hyp_n = 1 / (cos(angles) / adj);
	angles = 90 - angles;
	hyp_e = 1 / (sin(angles) / opp);
	if (hyp_n > hyp_e)
		return (raydata->dist = hyp_e, raydata->wall = 'e', raydata);
	return (raydata->dist = hyp_n, raydata->wall = 'n', raydata);
}
t_r	*bottom_left(t_c **c, float adj, float opp, double angles)
{
		t_c		*p;
	float	hyp_w;
	float	hyp_s;
	t_r		*raydata;

	raydata = malloc(sizeof(t_c));
	p = *c;
	angles -= 180;
	opp = len_to_hit_wall_w(p);
	adj = len_to_hit_wall_s(p);
	hyp_w = 1 / (sin(angles) / opp);
	angles = 90 - angles;
	hyp_s = 1 / (cos(angles) / adj);
	if (hyp_s > hyp_w)
		return (raydata->dist = hyp_w, raydata->wall = 'w', raydata);
	return (raydata->dist = hyp_s, raydata->wall = 's', raydata);
}
t_r	*bottom_right(t_c **c, float adj, float opp, double angles)
{
	t_c		*p;
	float	hyp_e;
	float	hyp_s;
	t_r		*raydata;

	raydata = malloc(sizeof(t_c));
	p = *c;
	angles -= 90;
	opp = len_to_hit_wall_e(p);
	adj = len_to_hit_wall_s(p);
	hyp_s = 1 / (cos(angles) / adj);
	angles = 90 - angles;
	hyp_e = 1 / (sin(angles) / opp);
	if (hyp_s > hyp_e)
		return (raydata->dist = hyp_e, raydata->wall = 'e', raydata);
	return (raydata->dist = hyp_s, raydata->wall = 's', raydata);
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
		p->raydata = ;
	}
}

a = b/c;

3 = 6/2;


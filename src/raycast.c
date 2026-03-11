/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: radib <radib@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 14:35:49 by radib             #+#    #+#             */
/*   Updated: 2026/03/11 11:59:39 by radib            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

double deg_to_rad(double deg)
{
    return (deg * M_PI / 180.0);
}

double	angle_calc(double angle, double calc)
{
	angle = angle + calc - 33;
	if (angle < 0)
		angle = 360 + angle;
	else if (angle >= 360)
		angle = 360 - angle;
	return (angle);
}
double	len_to_hit_wall_n(t_c *p)
{
	int		i;
	double	temp;

	temp = 1 - (p->pos_y - (int)p->pos_y);
	i = 0;
	while (p->map[(int)p->pos_y - i][(int)p->pos_x] != '1')
		i++;
	return (temp + i);
}
double	len_to_hit_wall_e(t_c *p)
{
	int		i;
	double	temp;

	temp = p->pos_x - (int)p->pos_x;
	i = 0;
	while (p->map[(int)p->pos_y][(int)p->pos_x - i] != '1')
		i++;
	return (temp + i);
}
double	len_to_hit_wall_w(t_c *p)
{
	int		i;
	double	temp;

	temp = p->pos_x - (int)p->pos_x;
	i = 0;
	while (p->map[(int)p->pos_y][(int)p->pos_x + i] != '1')
		i++;
	return (temp + i);
}
double	len_to_hit_wall_s(t_c *p)
{
	int		i;
	double	temp;

	temp = 1 - (p->pos_y - (int)p->pos_y);
	i = 0;
	while (p->map[(int)p->pos_y + i][(int)p->pos_x] != '1')
		i++;
	return (temp + i);
}

t_r	*top_left(t_c **c, double adj, double opp, double angles)
{
	t_c		*p;
	double	hyp_w;
	double	hyp_n;
	t_r		*raydata;

	raydata = malloc(sizeof(t_c));
	p = *c;
	angles -= 270;
	opp = len_to_hit_wall_w(p);
	adj = len_to_hit_wall_n(p);
	hyp_w = 1 / (sin(deg_to_rad(angles)) / opp);
	angles = 90 - angles;
	hyp_n = 1 / (cos(deg_to_rad(angles)) / adj);
	if (hyp_n > hyp_w)
		return (raydata->dist = hyp_w, raydata->wall = 'w', raydata);
	return (raydata->dist = hyp_n, raydata->wall = 'n', raydata);
}
t_r	*top_right(t_c **c, double adj, double opp, double angles)
{
	t_c		*p;
	double	hyp_e;
	double	hyp_n;
	t_r		*raydata;

	raydata = malloc(sizeof(t_c));
	p = *c;
	opp = len_to_hit_wall_e(p);
	adj = len_to_hit_wall_n(p);
	hyp_n = 1 / (cos(deg_to_rad(angles)) / adj);
	angles = 90 - angles;
	hyp_e = 1 / (sin(deg_to_rad(angles)) / opp);
	if (hyp_n > hyp_e)
		return (raydata->dist = hyp_e, raydata->wall = 'e', raydata);
	return (raydata->dist = hyp_n, raydata->wall = 'n', raydata);
}
t_r	*bottom_left(t_c **c, double adj, double opp, double angles)
{
	t_c		*p;
	double	hyp_w;
	double	hyp_s;
	t_r		*raydata;

	raydata = malloc(sizeof(t_c));
	p = *c;
	angles -= 180;
	opp = len_to_hit_wall_w(p);
	adj = len_to_hit_wall_s(p);
	hyp_w = 1 / (sin(deg_to_rad(angles)) / opp);
	angles = 90 - angles;
	hyp_s = 1 / (cos(deg_to_rad(angles)) / adj);
	if (hyp_s > hyp_w)
		return (raydata->dist = hyp_w, raydata->wall = 'w', raydata);
	return (raydata->dist = hyp_s, raydata->wall = 's', raydata);
}
t_r	*bottom_right(t_c **c, double adj, double opp, double angles)
{
	t_c		*p;
	double	hyp_e;
	double	hyp_s;
	t_r		*raydata;

	raydata = malloc(sizeof(t_c));
	p = *c;
	angles -= 90;
	opp = len_to_hit_wall_e(p);
	adj = len_to_hit_wall_s(p);
	hyp_s = 1 / (cos(deg_to_rad(angles)) / adj);
	angles = 90 - angles;
	hyp_e = 1 / (sin(deg_to_rad(angles)) / opp);
	if (hyp_s > hyp_e)
		return (raydata->dist = hyp_e, raydata->wall = 'e', raydata);
	return (raydata->dist = hyp_s, raydata->wall = 's', raydata);
}

t_r	*angle_choser(t_c **c, int angles)
{
	if (angles >= 0 && angles < 90)
		return (top_right(c, 0, 0, angles));
	if (angles >= 90 && angles < 180)
		return (bottom_right(c, 0, 0, angles));
	if (angles >= 180 && angles < 270)
		return (bottom_right(c, 0, 0, angles));
	if (angles >= 270 && angles < 360)
		return (top_left(c, 0, 0, angles));
	return (0);
}

int	find_color(int a)
{
	if (a == 'n')
		return (0xff0000);
	else if (a == 's')
		return (0x191970);
	else if (a == 'e')
		return (0xff3e96);
	else if (a == 'w')
		return (0xffc0cb);
	return (0);
}

void	draw_wall_height_line(t_r *raydata, t_img **displayed_img, t_c *p, int x)
{
	int		i;
	double	y;
	int		color;

	color = find_color(raydata->wall);
	i = p->height - raydata->dist * 20;
	y = raydata->dist * 20;
	while (y < i)
	{
		put_pixel_to_image((*displayed_img), x, (int)y, color);
		y++;
	}
}

void	raycast(t_c **c, int i, double angles)
{
	t_c		*p;

	p = *c;
	while (i < p->width)
	{
		angles = angle_calc(p->angle, (double)66 / p->width * i);
		p->raydata[i] = angle_choser(c, angles);
		if (!p->raydata[i])
			printf("angle : %f, width pixel : %d ray error\n", p->angle, i);
		i++;
	}
	i = 0;
	p->displayed_img = p->roof_and_ground;
	while (i < p->width)
	{
		draw_wall_height_line(p->raydata[i], &p->displayed_img, p, i);
		i++;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: radib <radib@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 14:35:49 by radib             #+#    #+#             */
/*   Updated: 2026/03/14 17:33:07 by radib            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

float	deg_to_rad(float deg)
{
	return (deg * M_PI / 180.0);
}

float	angle_calc(float angle, float calc)
{
	// printf("%f %f\n", angle, calc);
	angle = angle + calc;
	if (angle < 0)
		angle += 360;
	else if (angle >= 360)
		angle = fmodf(angle, 360.00);
	return (angle);
}

t_r	*dda(t_c **c, float angle)
{
    t_c     *p;
    t_r     *raydata;
    // Ray direction vector (compass: N=0, clockwise)
    float   ray_dir_x;
    float   ray_dir_y;
    // Current map cell
    int     map_x;
    int     map_y;
    // Accumulated side distances
    float   side_dist_x;
    float   side_dist_y;
    // Delta distances (cost to cross one cell)
    float   delta_x;
    float   delta_y;
    // Step direction (+1 or -1)
    int     step_x;
    int     step_y;
    // Which side was hit (0 = E/W wall, 1 = N/S wall)
    int     side;

    p = *c;
    raydata = malloc(sizeof(t_r));

    // Convert compass angle to direction vector
    // Compass: N=0 → (x=0,y=-1), E=90 → (x=1,y=0), etc.
    ray_dir_x = sin(deg_to_rad(angle));
    ray_dir_y = -cos(deg_to_rad(angle));

    // Starting map cell
    map_x = (int)p->pos_x;
    map_y = (int)p->pos_y;

    // How far to cross a full cell in each axis
    delta_x = (ray_dir_x == 0) ? 1e30 : fabs(1.0f / ray_dir_x);
    delta_y = (ray_dir_y == 0) ? 1e30 : fabs(1.0f / ray_dir_y);

    // Initialize step and side_dist
    if (ray_dir_x < 0)
    {
        step_x = -1;
        side_dist_x = (p->pos_x - map_x) * delta_x;
    }
    else
    {
        step_x = 1;
        side_dist_x = (map_x + 1.0f - p->pos_x) * delta_x;
    }
    if (ray_dir_y < 0)
    {
        step_y = -1;
        side_dist_y = (p->pos_y - map_y) * delta_y;
    }
    else
    {
        step_y = 1;
        side_dist_y = (map_y + 1.0f - p->pos_y) * delta_y;
    }

    // DDA loop — step until we hit a wall
    while (1)
    {
        if (side_dist_x < side_dist_y)
        {
            side_dist_x += delta_x;
            map_x += step_x;
            side = 0; // E or W wall hit
        }
        else
        {
            side_dist_y += delta_y;
            map_y += step_y;
            side = 1; // N or S wall hit
        }
        if ((*c)->map[map_y][map_x] == '1')
            break ;
    }

    // Perpendicular distance (avoids fisheye)
    if (side == 0)
    {
        raydata->dist = side_dist_x - delta_x;
        raydata->wall = (ray_dir_x > 0) ? 'e' : 'w';
    }
    else
    {
        raydata->dist = side_dist_y - delta_y;
        raydata->wall = (ray_dir_y > 0) ? 's' : 'n';
    }
    return (raydata);
}

// t_r	*top_left(t_c **c, float adj, float opp, float angles)
// {
// 	float	hyp_w;
// 	float	hyp_n;
// 	t_r		*raydata;

// 	raydata = malloc(sizeof(t_r));
// 	angles = fmod(angles, 90.00);
// 	opp = dda((*c), angles);
// 	adj = dda((*c), angles);
// 	// printf("opp : %f adj : %f ", opp, adj);
// 	hyp_w = opp / (sin(deg_to_rad(angles)));
// 	// printf("tl%f\n", angles);
// 	// angles = 90 - angles;
// 	// printf("tl%f\n", angles);
// 	hyp_n = adj / (cos(deg_to_rad(angles)));
// 	if (hyp_n > hyp_w)
// 	{
// 		// printf("dist W:%f\n", hyp_w);
// 		return (raydata->dist = hyp_w, raydata->wall = 'n', raydata);
// 	}
// 	// printf("dist N:%f\n", hyp_n);
// 	return (raydata->dist = hyp_n, raydata->wall = 'w', raydata);
// }

// t_r	*top_right(t_c **c, float adj, float opp, float angles)
// {
// 	t_c		*p;
// 	float	hyp_e;
// 	float	hyp_n;
// 	t_r		*raydata;

// 	raydata = malloc(sizeof(t_r));
// 	angles = fmod(angles, 90.00);
// 	p = *c;
// 	opp = dda(p, angles);
// 	adj = dda(p, angles);
// 	hyp_n = adj / (cos(deg_to_rad(angles)));
// 	// printf("tr%f\n", angles);
// 	// printf("opp : %f adj : %f ", opp, adj);
// 	// angles = 90 - angles;
// 	// printf("tr%f\n", angles);
// 	hyp_e = opp / (sin(deg_to_rad(angles)));
// 	if (hyp_n > hyp_e)
// 	{
// 		// printf("dist E:%f\n", hyp_e);
// 		return (raydata->dist = hyp_e, raydata->wall = 'e', raydata);
// 	}
// 	// printf("dist N:%f\n", hyp_n);
// 	return (raydata->dist = hyp_n, raydata->wall = 'n', raydata);
// }

// t_r	*bottom_left(t_c **c, float adj, float opp, float angles)
// {
// 	t_c		*p;
// 	float	hyp_w;
// 	float	hyp_s;
// 	t_r		*raydata;

// 	raydata = malloc(sizeof(t_r));
// 	p = *c;
// 	angles = fmod(angles, 90.00);
// 	opp = dda(p, angles);
// 	adj = dda(p, angles);
// 	// printf("opp : %f adj : %f ", opp, adj);
// 	hyp_s = adj / (cos(deg_to_rad(angles)));
// 	// printf("bl%f\n", angles);
// 	// angles = 90 - angles;
// 	// printf("bl%f\n", angles);
// 	hyp_w = opp / (sin(deg_to_rad(angles)));
// 	if (hyp_s > hyp_w)
// 	{
// 		// printf("dist W:%f\n", hyp_w);
// 		return (raydata->dist = hyp_w, raydata->wall = 'w', raydata);
// 	}
// 	// printf("dist S:%f\n", hyp_s);
// 	return (raydata->dist = hyp_s, raydata->wall = 's', raydata);
// }

// t_r	*bottom_right(t_c **c, float adj, float opp, float angles)
// {
// 	t_c		*p;
// 	float	hyp_e;
// 	float	hyp_s;
// 	t_r		*raydata;

// 	raydata = malloc(sizeof(t_r));
// 	p = *c;
// 	// printf("br%f\n", angles);
// 	angles = fmod(angles, 90.00);
// 	opp = dda(p);
// 	adj = dda(p);
// 	// printf("opp : %f adj : %f ", opp, adj);
// 	hyp_e = opp / (sin(deg_to_rad(angles)));
// 	// printf("br%f\n", angles);
// 	// angles = 90 - angles;
// 	// printf("br%f\n", angles);
// 	hyp_s = adj / (cos(deg_to_rad(angles)));
// 	if (hyp_s > hyp_e)
// 	{
// 		// printf("dist E:%f\n", hyp_e);
// 		return (raydata->dist = hyp_e, raydata->wall = 's', raydata);
// 	}
// 	// printf("dist S:%f\n", hyp_s);
// 	return (raydata->dist = hyp_s, raydata->wall = 'e', raydata);
// }

// t_r	*angle_choser(t_c **c, float angles)
// {
// 	// printf("%f\n", angles);
// 	if (angles >= 0 && angles < 90)
// 		return (top_right(c, 0, 0, angles));
// 	if (angles >= 90 && angles < 180)
// 		return (bottom_right(c, 0, 0, angles));
// 	if (angles >= 180 && angles < 270)
// 		return (bottom_left(c, 0, 0, angles));
// 	if (angles >= 270 && angles < 360)
// 		return (top_left(c, 0, 0, angles));
// 	return (0);
// }

int	find_color(int a)
{
	if (a == 'n')
		return (0xff0000);
	else if (a == 's')
		return (0xffff00);
	else if (a == 'e')
		return (0xffffff);
	else if (a == 'w')
		return (0x00ffff);
	return (0);
}

void	draw_wall_height_line(t_r *raydata, t_img **displayed_img
	, t_c *p, int x)
{
	int		i;
	float	y;
	int		color;
	int		wall_size;

	wall_size = p->height / raydata->dist;
	color = find_color(raydata->wall);
	i = p->height - (p->height - wall_size) / 2;
	y = (p->height - wall_size) / 2;
	if (y < 0)
		y = 0;
	// temp fix to fix later
	while (y < i && y < p->height)
	{
		put_pixel_to_image((*displayed_img), x, (int)y, color);
		y++;
	}
}
float rad_to_deg(float rad)
{
    return (rad * 180.0f / M_PI);
}
// void	raycast(t_c **c, int i, float angles)
// {
// t_c		*p;

// p = *c;
// while (i < p->width)
// {
// 	angles = angle_calc(p->angle, 90.00 / (float)p->width * i);
// 	// printf("angle : %f\n", angles); //anglepring
// 	p->raydata[i] = angle_choser(c, angles);
// 	if (!p->raydata[i])
// 		printf("angle : %f, width pixel : %d ray error\n", angles, i);
// 	i++;
// }
// i = 0;
// render_roof(10000 * 0 + 100 * 20 + 20, c);
// render_floor(300 * 10000 + 100 * 100 + 50, c);
// p->displayed_img = p->roof_and_ground;
// un_fish_eye(c, 0, 0);
// while (i < p->width)
// {
// 	// printf("%f\n", p->raydata[i]->dist); //distprint
// 	draw_wall_height_line(p->raydata[i], &p->displayed_img, p, i);
// 	i++;
// }
// mlx_clear_window(p->m_ptr, p->w_ptr);
// mlx_put_image_to_window(p->m_ptr, p->w_ptr, p->displayed_img->img, 0, 0);
// }
void raycast(t_c **c, int i, float angles)
{
    t_c     *p;
    float   plane_x;
    float   plane_y;
    float   dir_x;
    float   dir_y;
    float   camera_x;
	float	corrected_dist;

    p = *c;
    // Camera plane vector (perpendicular to view direction)
    // Length = tan(fov/2) to scale correctly
    dir_x = sin(deg_to_rad(p->angle));
    dir_y = -cos(deg_to_rad(p->angle));
    plane_x = cos(deg_to_rad(p->angle)) * tan(deg_to_rad(p->fov / 2));
    plane_y = sin(deg_to_rad(p->angle)) * tan(deg_to_rad(p->fov / 2));

    while (i < p->width)
    {
        // camera_x goes from -1 (left) to +1 (right) linearly
        camera_x = 2.0f * i / p->width - 1.0f;

        // Ray direction via camera plane — linear in screen space
        float ray_x = dir_x + plane_x * camera_x;
        float ray_y = dir_y + plane_y * camera_x;

        // Convert back to angle for your dda
        angles = fmodf(rad_to_deg(atan2f(ray_x, -ray_y)) + 360.0f, 360.0f);

        p->raydata[i] = dda(c, angles);
		draw_wall_height_line(p->raydata[i], &p->displayed_img, p, i);
				float diff = angles - p->angle;
		corrected_dist = p->raydata[i]->dist * cos(deg_to_rad(diff));
		p->raydata[i]->dist = corrected_dist;
		i++;
    }
	i = 0;
	render_roof(10000 * 0 + 100 * 20 + 20, c);
	render_floor(300 * 10000 + 100 * 100 + 50, c);
	p->displayed_img = p->roof_and_ground;
	while (i < p->width)
	{
		draw_wall_height_line(p->raydata[i], &p->displayed_img, p, i);
		i++;
	}
	mlx_clear_window(p->m_ptr, p->w_ptr);
	mlx_put_image_to_window(p->m_ptr, p->w_ptr, p->displayed_img->img, 0, 0);
    // ... rest unchanged
}
// void	raycast(t_c **c, int i, float angles)
// {
// 	t_c		*p;
// 	// float	corrected_dist;

// 	p = *c;
// 	while (i < p->width)
// 	{
// 		angles = p->angle - p->fov/2 + p->fov * (i + 0.5)/p->width;
// 		angles = fmodf(angles + 360.0, 360.0); // normalize 0-360
// 		p->raydata[i] = dda(c, angles);
// 		if (!p->raydata[i])
// 			printf("angle : %f, width pixel : %d ray error\n", angles, i);
// 		// printf("player angle : %f, ray angle : %f, calculed : %f\n", p->angle, angles, p->angle - angles);

// 		float diff = angles - p->angle;
// 		printf("ray angle: %f, player angle: %f, diff: %f\n", angles, p->angle, diff);

// 	// if (diff > 180.0)
// 	//     diff -= 360.0;
// 	// if (diff < -180.0)
// 	//     diff += 360.0;
// 		// corrected_dist = p->raydata[i]->dist * cos(deg_to_rad(diff));
// 		// printf("raw dist: %f, corrected dist: %f\n", p->raydata[i]->dist, corrected_dist);
// 		// p->raydata[i]->dist = corrected_dist;
// 		i++;
// 	}
// 	i = 0;
// 	render_roof(10000 * 0 + 100 * 20 + 20, c);
// 	render_floor(300 * 10000 + 100 * 100 + 50, c);
// 	p->displayed_img = p->roof_and_ground;
// 	while (i < p->width)
// 	{
// 		draw_wall_height_line(p->raydata[i], &p->displayed_img, p, i);
// 		i++;
// 	}
// 	mlx_clear_window(p->m_ptr, p->w_ptr);
// 	mlx_put_image_to_window(p->m_ptr, p->w_ptr, p->displayed_img->img, 0, 0);
// }
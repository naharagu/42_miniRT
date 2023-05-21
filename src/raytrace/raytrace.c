/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saikeda <saikeda@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 10:14:45 by naharagu          #+#    #+#             */
/*   Updated: 2023/05/21 15:32:49 by saikeda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "raytrace.h"
#include <math.h>

// static t_vec3	get_sx_basis(t_scene *scene)
// {
// 	t_vec3	e_sx;
// 	double	denominator;

// 	denominator = sqrt(pow(scene->camera.dir.x, 2) + \
// 					pow(scene->camera.dir.z, 2));
// 	e_sx.x = scene->camera.dir.z / denominator;
// 	e_sx.y = 0;
// 	e_sx.z = scene->camera.dir.x / denominator;
// 	return (vec3_normalize(e_sx));
// }

// static t_vec3	get_screen_direction(double x, double y, t_ray *ray, t_scene *scene)
// {
// 	t_vec3	screen;
// 	// t_vec3	e_sx;
// 	// t_vec3	e_sy;

// 	// e_sx = get_sx_basis(scene);
// 	// e_sy = vec3_normalize(vec3_cross_product(scene->camera.dir, e_sx));
// 	screen = vec3_addition(vec3_multiply_scalar(e_sx, (x - ((double)WIDTH / 2))), \
// 				vec3_multiply_scalar(e_sy, (((double)HEIGHT / 2) - y)));
// 	return (vec3_normalize(vec3_addition(ray->screen_center, screen)));
// }

static void	get_screen(t_window *window)
{
	double	denominator;

	denominator = sqrt(pow(window->scene->camera.dir.x, 2) + \
					pow(window->scene->camera.dir.z, 2));
	window->screen.e_sx.x = window->scene->camera.dir.z / denominator;
	window->screen.e_sx.y = 0;
	window->screen.e_sx.z = window->scene->camera.dir.x / denominator;
	window->screen.e_sx = vec3_normalize(window->screen.e_sx);
	window->screen.e_sy = vec3_normalize(vec3_cross_product(window->scene->camera.dir, window->screen.e_sx));
	window->screen.center = vec3_addition(window->scene->camera.origin, \
		vec3_multiply_scalar(window->scene->camera.dir, \
		((double)WIDTH / 2 / tan(window->scene->camera.fov / 2 / 180 * M_PI))));
}

void	put_pixel_to_addr(t_window *window, int x, int y, int color)
{
	char	*addr;
	char	*dst;
	int		len;
	int		bpp;

	addr = window->addr;
	len = window->line_length;
	bpp = window->bits_per_pixel;
	dst = addr + (y * len + x * (bpp / 8));
	*(unsigned int *)dst = color;
}

static bool	shadow_intersect(t_intersect *intersect, t_scene *scene)
{
	t_ray		shadow_ray;
	t_intersect	shadow_intersect;

	shadow_ray.origin = intersect->point;
	shadow_ray.dir = scene->light.dir;
	return (calculate_intersect_point(&shadow_ray, &shadow_intersect, \
	scene, intersect->index) == true && \
	EPSILON < shadow_intersect.distance && \
	shadow_intersect.distance < \
	vec3_magnitude(vec3_subtraction(scene->light.origin, intersect->point)));
}

static t_color	calculate_color(t_ray *ray, \
									t_intersect *intersect, t_scene *scene)
{
	if (calculate_intersect_point(ray, intersect, scene, -1) == false)
		return ((t_color){0, 0, 0});
	else
	{
		scene->light.dir = \
		vec3_normalize(vec3_subtraction(scene->light.origin, intersect->point));
		if (shadow_intersect(intersect, scene))
			return (vec3_multiply_scalar(scene->ambient_color, \
					scene->ambient_ratio));
		else
			return (shading(*ray, *intersect, scene));
	}
}

// void	raytrace(t_window *window, t_scene *scene)
void	raytrace(t_window *window)
{
	int			x;
	int			y;
	t_ray		ray;
	t_intersect	intersect;

	ray.origin = window->scene->camera.origin;
	get_screen(window);
	// ray.screen_center = vec3_addition(window->scene->camera.origin, \
	// 		vec3_multiply_scalar(window->scene->camera.dir, \
	// 		((double)WIDTH / 2 / tan(window->scene->camera.fov / 2 / 180 * M_PI))));
	x = 0;
	while (x < WIDTH)
	{
		y = 0;
		while (y < HEIGHT)
		{
			// ray.dir = get_screen_direction(x, y, &ray, window->scene);
			ray.dir = vec3_normalize(vec3_addition(window->screen.center, \
				vec3_addition(vec3_multiply_scalar(window->screen.e_sx, \
				(x - ((double)WIDTH / 2))), vec3_multiply_scalar(window->screen.e_sy, \
				(((double)HEIGHT / 2) - y)))));
			put_pixel_to_addr(window, x, y, \
				get_color_in_int(calculate_color(&ray, &intersect, window->scene)));
			y++;
		}
		x++;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saikeda <saikeda@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 10:14:45 by naharagu          #+#    #+#             */
/*   Updated: 2023/05/20 10:49:43 by saikeda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "raytrace.h"
#include <math.h>

static t_vec3	get_ray_direction(double x, double y, t_ray ray)
{
	t_vec3	screen;

	screen = (t_vec3){(double)2 * x / ((double)WIDTH - 1.0) - 1.0, \
			-(double)2 * y / ((double)HEIGHT - 1.0) + 1.0, \
			0};
	return (vec3_normalize(vec3_subtraction(screen, ray.origin)));
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

void	raytrace(t_window *window, t_scene *scene)
{
	int			x;
	int			y;
	t_ray		ray;
	t_intersect	intersect;

	ray.origin = scene->camera.origin;
	x = 0;
	while (x < WIDTH)
	{
		y = 0;
		while (y < HEIGHT)
		{
			ray.dir = get_ray_direction(x, y, ray);
			put_pixel_to_addr(window, x, y, \
				get_color_in_int(calculate_color(&ray, &intersect, scene)));
			y++;
		}
		x++;
	}
}

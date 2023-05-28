/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saikeda <saikeda@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 10:14:45 by naharagu          #+#    #+#             */
/*   Updated: 2023/05/28 22:32:38 by saikeda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "raytrace.h"

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
			return (vec3_multiply_scalar(intersect->color, \
					scene->ambient_ratio));
		else
			return (shading(*ray, *intersect, scene));
	}
}

void	raytrace(t_window *window)
{
	int			x;
	int			y;
	t_ray		ray;
	t_intersect	intersect;

	ray.origin = window->scene->camera.origin;
	x = 0;
	while (x < WIDTH)
	{
		y = 0;
		while (y < HEIGHT)
		{
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
	printf("dir %f, %f, %f\n", window->scene->camera.dir.x, window->scene->camera.dir.y, window->scene->camera.dir.z);
	printf("org %f, %f, %f\n", window->scene->camera.origin.x, window->scene->camera.origin.y, window->scene->camera.origin.z);
	printf("ray_org %f, %f, %f\n", ray.origin.x, ray.origin.y, ray.origin.z);
}

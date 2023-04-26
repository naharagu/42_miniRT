/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharagu <naharagu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 10:14:45 by naharagu          #+#    #+#             */
/*   Updated: 2023/04/26 19:06:35 by naharagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "raytrace.h"
#include <math.h>

static t_vec3	get_ray_direction(double x, double y, t_ray ray)
{
	t_vec3	screen;

	screen = (t_vec3){(double)2 * x / (double)WIDTH - 1.0, \
				(double)2 * y / (double)HEIGHT - 1.0, 0};
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

void	raytrace(t_window *window, t_scene *scene)
{
	int			x;
	int			y;
	t_ray		ray;
	t_intersect	intersect;
	t_color		color;

	ray.origin = scene->camera.origin;
	x = 0;
	while (x < WIDTH)
	{
		y = 0;
		while (y < HEIGHT)
		{
			ray.dir = get_ray_direction(x, y, ray);
			if (calculate_intersect_point(&ray, &intersect, scene) == false)
				color = ((t_color){0, 0, 0});
			else
				color = shading(ray, intersect, scene);
			put_pixel_to_addr(window, x, HEIGHT - y - 1, \
					get_color_in_int(color));
			y++;
		}
		x++;
	}
}

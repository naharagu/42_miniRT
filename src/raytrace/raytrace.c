/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saikeda <saikeda@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 10:14:45 by naharagu          #+#    #+#             */
/*   Updated: 2023/05/08 07:35:06 by saikeda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "raytrace.h"
#include <math.h>

static t_vec3	get_ray_direction(double x, double y, t_ray ray)
{
	t_vec3	screen;

	// // 元々記載の式
	// screen = (t_vec3){(double)2 * x / (double)WIDTH - 1.0, \
	// 			(double)2 * y / (double)HEIGHT - 1.0, 0};
	// 東京電機大資料の式
	screen = (t_vec3){(double)2 * x / ((double)WIDTH - 1.0) - 1.0, \
			-(double)2 * y / ((double)HEIGHT - 1.0) + 1.0, \
			0};
	// // デバッグ用
	// if (((int)x % 50 == 0 || x == (double)WIDTH - 1.0) && ((int)y % 50 == 0 || y == (double)HEIGHT - 1.0))
	// 	printf("x %lf y %lf xs %lf ys %lf zs %lf\n", x, y, screen.x, screen.y, screen.z);
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
			else {
				color = shading(ray, intersect, scene);
				// printf("x %d y %d cr %lf cg %lf cb %lf\n", x, y, color.x, color.y, color.z);
			}
			put_pixel_to_addr(window, x, HEIGHT - y - 1, \
					get_color_in_int(color));
			// put_pixel_to_addr(window, x, y, \
			// 		get_color_in_int(color));
			y++;
		}
		x++;
	}
}

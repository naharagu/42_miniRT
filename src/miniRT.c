/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharagu <naharagu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 10:14:45 by naharagu          #+#    #+#             */
/*   Updated: 2023/04/10 22:15:31 by naharagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "raytrace.h"
#include <math.h>
#include <stdbool.h>

static t_vec3	get_ray(t_scene *scene, double x, double y)
{
	t_vec3	screen;

	screen = (t_vec3){(double)2 * x / (double)WIDTH - 1.0, \
					(double)2 * y / (double)HEIGHT - 1.0, 0};
	return (vec3_normalize(vec3_subtraction(screen, scene->camera.origin)));
}

static bool calculate_hit_point(t_scene *scene, t_vec3 *ray)
{
	double	sphere_r = 0.7;
	double	a;
	double	b;
	double	c;
	double	discriminant;
	double	t;
	double	t2;

	a = vec3_magnitude(*ray) * vec3_magnitude(*ray);
	b = 2.0 * vec3_dot_product(scene->camera.origin, *ray);
	c = vec3_magnitude(scene->camera.origin) * vec3_magnitude(scene->camera.origin) - sphere_r * sphere_r;
	discriminant = b * b - 4.0 * a * c;
	if (discriminant < 0.0)
		return (false);
	t = (-b + sqrt(discriminant)) / (2.0 * a);
	if (discriminant > 0.0)
	{
		t2 = (-b - sqrt(discriminant)) / (2.0 * a);
		if (t2 < t)
			t = t2;
	}
	scene->hit.point = vec3_addition(scene->camera.origin, vec3_multiply_scalar(*ray, t));
	scene->hit.normal = vec3_normalize(vec3_subtraction(scene->hit.point,
				scene->shapes->center));
	scene->light.direction = vec3_normalize(vec3_subtraction(scene->light.origin,
				scene->hit.point));
	return (true);
}

void	put_pixel_to_addr(t_world *world, int x, int y, int color)
{
	char 	*addr;
	char	*dst;
	int		len;
	int		bpp;

	addr = world->addr;
	len = world->line_length;
	bpp = world->bits_per_pixel;
	dst = addr + (y * len + x * (bpp / 8));
	*(unsigned int *)dst = color;
}

// dstに代入されるアドレスは、画像データの先頭アドレスから、y座標のラインのバイト数とx座標に対応するバイト数を加算したアドレス
// このアドレスに対して、カラー値を書き込むことで、指定された座標にカラーのピクセルを描画

void	mini_rt(t_world *world, t_scene *scene)
{
	int		x;
	int		y;
	t_vec3	ray;
	t_color	color;

	x = 0;
	while (x < WIDTH)
	{
		y = 0;
		while (y < HEIGHT)
		{
			ray = get_ray(scene, x, y);
			if (calculate_hit_point(scene, &ray) == false)
			{
				color = ((t_color){100, 149, 237});
				// color = ((t_color){0, 50, 100});
			}
			else
			{
				color = shading(scene, ray);
			}
			put_pixel_to_addr(world, x, HEIGHT - y - 1, \
					get_color_in_int(color));
			y++;
		}
		x++;
	}
}

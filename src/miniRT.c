/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharagu <naharagu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 10:14:45 by naharagu          #+#    #+#             */
/*   Updated: 2023/04/08 10:55:44 by naharagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "raytrace.h"
#include <math.h>

static t_vec3	get_ray(t_world *world, double x, double y)
{
	t_vec3	camera;
	t_vec3	screen;

	camera = world->camera;
	screen = (t_vec3){(double)2 * x / (double)WIDTH - 1.0, \
					(double)2 * y / (double)HEIGHT - 1.0, 0};
	return (vec3_normalize(vec3_subtraction(screen, camera)));
}

static int	calculate_hit_point(t_world *world, t_vec3 *ray)
{
	t_vec3	camera;
	t_vec3	light;
	t_vec3	sphere;
	double	sphere_r;
	double	a;
	double	b;
	double	c;
	double	discriminant;
	double	t;
	double	t2;

	camera = world->camera;
	light = world->light;
	sphere = world->object;
	sphere_r = 0.7;
	a = vec3_magnitude(*ray) * vec3_magnitude(*ray);
	b = 2.0 * vec3_dot_product(camera, *ray);
	c = vec3_magnitude(camera) * vec3_magnitude(camera) - sphere_r * sphere_r;
	discriminant = b * b - 4.0 * a * c;
	if (discriminant < 0.0)
		return (-1);
	t = (-b + sqrt(discriminant)) / (2.0 * a);
	if (discriminant > 0.0)
	{
		t2 = (-b - sqrt(discriminant)) / (2.0 * a);
		if (t2 < t)
			t = t2;
	}
	world->hit.point = vec3_addition(camera, vec3_multiply_scalar(*ray, t));
	world->hit.normal = vec3_normalize(vec3_subtraction(world->hit.point,
				sphere));
	world->light_dir = vec3_normalize(vec3_subtraction(light,
				world->hit.point));
	return (0);
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

void	mini_rt(t_world *world)
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
			ray = get_ray(world, x, y);
			if (calculate_hit_point(world, &ray) == -1)
				color = ((t_color){100, 149, 237});
			else
			{
				color = shading(world, ray);
				// color += shadowing;
			}
			put_pixel_to_addr(world, x, HEIGHT - y - 1, \
					get_color_in_int(color));
			y++;
		}
		x++;
	}
}
//shading = 1) diffuse_reflection + 2) specular_reflection
// .      + 3) ambient_reflection
//shadowing = 1) shadow + 2) reflection + 3) refraction

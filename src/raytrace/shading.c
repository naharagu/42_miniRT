/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shading.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharagu <naharagu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 10:14:21 by naharagu          #+#    #+#             */
/*   Updated: 2023/04/08 10:14:22 by naharagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytrace.h"
#include "vector.h"
#include <math.h>

double	calculate_ambient_light(void)
{
	double	k_a;
	double	i_a;
	double	r_ambient;

	k_a = 0.01;
	i_a = 0.1;
	r_ambient = k_a * i_a;
	return (r_ambient);
}

double	calculate_diffuse_reflection(t_world *world)
{
	double	diffuse;
	double	i_i;
	double	k_d;
	double	r_diffuse;

	diffuse = vec3_dot_product(world->light_dir, world->hit.normal);
	if (diffuse < 0.0)
		diffuse = 0.0;
	i_i = 1.0;
	k_d = 0.69;
	r_diffuse = k_d * i_i * diffuse;
	return (r_diffuse);
}

double	calculate_specular_reflection(t_world *world, t_vec3 ray)
{
	double	r_specular;
	t_vec3	normal;
	t_vec3	light_dir;
	double	i_i;
	double	k_s;
	double	alpha;
	t_vec3	v;
	t_vec3	r;

	normal = world->hit.normal;
	light_dir = world->light_dir;
	i_i = 1.0;
	k_s = 0.3;
	alpha = 8;
	v = vec3_multiply_scalar(ray, -1);
	r = vec3_subtraction(vec3_multiply_scalar(vec3_multiply_scalar(normal,
					vec3_dot_product(normal, light_dir)), 2), normal);
	r_specular = k_s * i_i * pow(vec3_dot_product(v, r), alpha);
	if (vec3_dot_product(v, r) < 0)
		r_specular = 0;
	return (r_specular);
}

t_color	shading(t_world *world, t_vec3 ray)
{
	double	r_ambient;
	double	r_diffuse;
	double	r_specular;
	double	r_total;

	r_ambient = calculate_ambient_light();
	r_diffuse = calculate_diffuse_reflection(world);
	r_specular = calculate_specular_reflection(world, ray);
	r_total = r_ambient + r_diffuse + r_specular;
	return ((t_color){255 * r_total, 255 * r_total, 255 * r_total});
}

// 環境光の環境反射(Ambient)
// 直接光の拡散反射(Diffuse)
// 直接光の鏡面反射(Specular)
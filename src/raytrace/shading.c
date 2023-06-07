/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shading.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saikeda <saikeda@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 10:14:21 by naharagu          #+#    #+#             */
/*   Updated: 2023/06/07 21:59:15 by saikeda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytrace.h"
#include "parse.h"
#include "vector.h"
#include <math.h>

double	calculate_diffuse_reflection(t_intersect intersect, t_light *light)
{
	double	cosine_theta;
	double	r_diffuse;

	cosine_theta = vec3_dot_product(intersect.b_normal, light->dir);
	if (cosine_theta < 0.0)
		return (0.0);
	r_diffuse = K_DIFFUSE * light->intensity * cosine_theta;
	return (r_diffuse);
}

double	calculate_specular_reflection(t_ray ray, \
									t_intersect intersect, t_light *light)
{
	double	cosine_theta;
	t_vec3	v;
	t_vec3	r;
	double	vr;
	double	r_specular;

	cosine_theta = vec3_dot_product(intersect.b_normal, light->dir);
	if (cosine_theta < 0.0)
		return (0.0);
	v = vec3_multiply_scalar(ray.dir, -1);
	r = vec3_multiply_scalar(intersect.b_normal, 2 * cosine_theta);
	r = vec3_subtraction(r, light->dir);
	vr = vec3_dot_product(v, r);
	if (vr < 0)
		return (0.0);
	r_specular = K_SPECULAR * light->intensity * pow(vr, ALPHA);
	return (r_specular);
}

t_vec3	shading(t_ray ray, t_intersect intersect, \
						t_scene *scene, t_light *light)
{
	double	r_ambient;
	double	r_diffuse;
	double	r_specular;
	double	r_total;

	r_ambient = scene->ambient_ratio;
	r_diffuse = calculate_diffuse_reflection(intersect, light);
	r_specular = calculate_specular_reflection(ray, intersect, light);
	r_total = r_ambient + r_diffuse + r_specular;
	return (vec3_multiply_scalar(intersect.color, r_total));
}

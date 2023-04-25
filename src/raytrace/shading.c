/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shading.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharagu <naharagu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 10:14:21 by naharagu          #+#    #+#             */
/*   Updated: 2023/04/25 21:25:14 by naharagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytrace.h"
#include "parse.h"
#include "vector.h"
#include <math.h>

double	calculate_diffuse_reflection(t_scene *scene)
{
	double	cosine_theta;
	double	r_diffuse;

	cosine_theta = vec3_dot_product(scene->intersect.normal, scene->light.direction);
	if (cosine_theta < 0.0)
		return (0.0);
	r_diffuse = K_DIFFUSE * scene->light.intensity * cosine_theta;
	return (r_diffuse);
}

double	calculate_specular_reflection(t_scene *scene, t_vec3 ray)
{
	double	cosine_theta;
	t_vec3	v;
	t_vec3	r;
	double	vr;
	double	r_specular;

	cosine_theta = vec3_dot_product(scene->intersect.normal, scene->light.direction);
	if (cosine_theta < 0.0)
		return (0.0);
	v = vec3_multiply_scalar(ray, -1);
	r = vec3_multiply_scalar(scene->intersect.normal, 2 * cosine_theta);
	r = vec3_subtraction(r, scene->light.direction);
	vr = vec3_dot_product(v, r);
	if (vr < 0)
		return (0.0);
	r_specular = K_SPECULAR * scene->light.intensity * pow(vr, ALPHA);
	return (r_specular);
}

t_color	shading(t_scene *scene, t_vec3 ray)
{
	double	r_ambient;
	double	r_diffuse;
	double	r_specular;
	double	r_total;

	r_ambient = scene->ambient_ratio;
	r_diffuse = calculate_diffuse_reflection(scene);
	r_specular = calculate_specular_reflection(scene, ray);
	r_total = r_ambient + r_diffuse + r_specular;
	return (vec3_multiply_scalar(scene->ambient_color, r_total));
}

// shading
// 1.環境光の環境反射(Ambient)
// 2.直接光の拡散反射(Diffuse)
// 3.直接光の鏡面反射(Specular)
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shading.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saikeda <saikeda@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 10:14:21 by naharagu          #+#    #+#             */
/*   Updated: 2023/06/12 20:07:44 by saikeda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytrace.h"
#include "parse.h"
#include "vector.h"
#include <math.h>

static bool	shadow_intersect(t_intersect *intersect, \
									t_scene *scene, t_light *light)
{
	t_ray		shadow_ray;
	t_intersect	shadow_intersect;

	shadow_ray.origin = intersect->point;
	shadow_ray.dir = light->dir;
	return (calculate_intersect_point(&shadow_ray, &shadow_intersect, \
	scene, intersect->index) == true && \
	EPSILON < shadow_intersect.distance && \
	shadow_intersect.distance < \
	vec3_magnitude(vec3_subtraction(light->origin, intersect->point)));
}

static t_vec3	diffuse_reflection(t_intersect *intersect, t_light *light)
{
	double	cosine_theta;
	double	r_diffuse;

	cosine_theta = vec3_dot_product(intersect->b_normal, light->dir);
	if (cosine_theta < 0.0)
		r_diffuse = 0.0;
	else
		r_diffuse = K_DIFFUSE * light->intensity * cosine_theta;
	return (vec3_multiply_scalar(convert_rgb(light->color), r_diffuse));
}

static t_vec3	specular_reflection(t_ray *ray, \
									t_intersect *intersect, t_light *light)
{
	double	cosine_theta;
	double	vr;
	double	r_specular;

	vr = 0.0;
	cosine_theta = vec3_dot_product(intersect->b_normal, light->dir);
	if (cosine_theta >= 0.0)
		vr = vec3_dot_product(vec3_multiply_scalar(ray->dir, -1), \
		vec3_subtraction(vec3_multiply_scalar(intersect->b_normal, \
								2 * cosine_theta), light->dir));
	if (cosine_theta < 0.0 || vr < 0.0)
		r_specular = 0.0;
	else
		r_specular = K_SPECULAR * light->intensity * pow(vr, ALPHA);
	return (vec3_multiply_scalar(convert_rgb(light->color), r_specular));
}

static t_vec3	adjust_minmax(t_vec3 reflect, double min, double max)
{
	if (reflect.x < min)
		reflect.x = min;
	if (reflect.y < min)
		reflect.y = min;
	if (reflect.z < min)
		reflect.z = min;
	if (reflect.x > max)
		reflect.x = max;
	if (reflect.y > max)
		reflect.y = max;
	if (reflect.z > max)
		reflect.z = max;
	return (reflect);
}

t_vec3	shading(t_ray *ray, t_intersect *intersect, t_scene *scene)
{
	t_vec3	reflect;
	t_light	*light;

	reflect = vec3_multiply_scalar(convert_rgb(scene->ambient_color), \
												scene->ambient_ratio);
	light = scene->lights;
	while (light)
	{
		light->dir = \
		vec3_normalize(vec3_subtraction(light->origin, intersect->point));
		if (shadow_intersect(intersect, scene, light) == false)
		{
			reflect = \
			vec3_addition(reflect, diffuse_reflection(intersect, light));
			reflect = \
			vec3_addition(reflect, specular_reflection(ray, intersect, light));
		}
		light = light->next;
	}
	return (adjust_minmax(reflect, 0.0, 1.0));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharagu <naharagu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 21:34:41 by naharagu          #+#    #+#             */
/*   Updated: 2023/04/25 22:09:16 by naharagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shape.h"
#include "main.h"
#include "raytrace.h"
#include "vector.h"
#include <math.h>

bool	intersect_sphere(t_shape *shape, t_vec3 *ray, t_scene *scene)
{
	double			sphere_r;
	t_discriminant	d;

	sphere_r = shape->radius;
	d.a = vec3_magnitude(*ray) * vec3_magnitude(*ray);
	d.b = 2.0 * vec3_dot_product(scene->camera.origin, *ray);
	d.c = vec3_magnitude(scene->camera.origin) * vec3_magnitude(scene->camera.origin) - sphere_r * sphere_r;
	d.discriminant = d.b * d.b - 4.0 * d.a * d.c;
	if (d.discriminant < 0.0)
		return (false);
	d.t = (-d.b + sqrt(d.discriminant)) / (2.0 * d.a);
	if (d.discriminant > 0.0)
	{
		d.t2 = (-d.b - sqrt(d.discriminant)) / (2.0 * d.a);
		if (d.t2 < d.t)
			d.t = d.t2;
	}
	scene->intersect.point = vec3_addition(scene->camera.origin, vec3_multiply_scalar(*ray, d.t));
	scene->intersect.normal = vec3_normalize(vec3_subtraction(scene->intersect.point,
				scene->shapes->center));
	scene->light.dir = vec3_normalize(vec3_subtraction(scene->light.origin,
				scene->intersect.point));
	return (true);
}

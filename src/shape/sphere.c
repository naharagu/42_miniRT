/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharagu <naharagu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 21:34:41 by naharagu          #+#    #+#             */
/*   Updated: 2023/04/26 15:58:45 by naharagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shape.h"
#include "main.h"
#include "raytrace.h"
#include "vector.h"
#include <math.h>

bool	intersect_sphere(t_shape *shape, t_ray *ray, t_scene *scene)
{
	t_vec3			so;
	t_discriminant	d;

	so = vec3_subtraction(ray->origin, shape->center);
	d.a = vec3_magnitude_squared(ray->dir);
	d.b = 2.0 * vec3_dot_product(so, ray->dir);
	d.c = vec3_magnitude_squared(so) - shape->radius * shape->radius;
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
	scene->intersect.point = vec3_addition(ray->origin, vec3_multiply_scalar(ray->dir, d.t));
	scene->intersect.normal = vec3_normalize(vec3_subtraction(scene->intersect.point,
				scene->shapes->center));
	scene->light.dir = vec3_normalize(vec3_subtraction(scene->light.origin,
				scene->intersect.point));
	scene->intersect.distance = d.t;
	// printf("distance: %f\n", d.t);
	return (true);
}

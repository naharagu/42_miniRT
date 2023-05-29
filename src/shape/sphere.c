/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharagu <naharagu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 21:34:41 by naharagu          #+#    #+#             */
/*   Updated: 2023/05/29 13:30:33 by naharagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shape.h"
#include "main.h"
#include "raytrace.h"
#include "vector.h"
#include <math.h>

bool	intersect_sphere(t_shape *shape, t_ray *ray, t_intersect *intersect)
{
	t_discriminant	d;

	d.so = vec3_subtraction(ray->origin, shape->center);
	d.a = vec3_dot_product(ray->dir, ray->dir);
	d.b = 2.0 * vec3_dot_product(d.so, ray->dir);
	d.c = vec3_dot_product(d.so, d.so) - shape->radius * shape->radius;
	d.discriminant = d.b * d.b - 4.0 * d.a * d.c;
	if (d.discriminant < 0.0)
		return (false);
	d.t = (-d.b + sqrt(d.discriminant)) / (2.0 * d.a);
	if (d.t > 0.0)
	{
		d.t2 = (-d.b - sqrt(d.discriminant)) / (2.0 * d.a);
		if (0.0 < d.t2 && d.t2 < d.t)
			d.t = d.t2;
		intersect->point = \
			vec3_addition(ray->origin, vec3_multiply_scalar(ray->dir, d.t));
		intersect->normal = \
			vec3_normalize(vec3_subtraction(intersect->point, shape->center));
		intersect->distance = d.t;
		intersect->color = shape->color;
		intersect->index = shape->index;
		return (true);
	}
	return (false);
}

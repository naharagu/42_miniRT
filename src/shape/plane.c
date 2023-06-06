/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saikeda <saikeda@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 19:37:49 by saikeda           #+#    #+#             */
/*   Updated: 2023/06/04 21:44:15 by saikeda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shape.h"
#include "main.h"
#include "raytrace.h"
#include "vector.h"
#include <math.h>

bool	intersect_plane(t_shape *shape, t_ray *ray, t_intersect *intersect)
{
	t_discriminant	d;

	d.a = vec3_dot_product(ray->dir, shape->normal);
	if (d.a == 0)
		return (false);
	d.b = vec3_dot_product(ray->origin, shape->normal);
	d.c = vec3_dot_product(shape->normal, shape->center);
	d.t = ((d.c - d.b) / d.a);
	if (d.t < 0)
		return (false);
	intersect->point = \
		vec3_addition(ray->origin, vec3_multiply_scalar(ray->dir, d.t));
	intersect->normal = shape->normal;
	intersect->distance = d.t;
	// intersect->color = shape->color;
	intersect->color = shape->colors->color;
	intersect->index = shape->index;
	return (true);
}

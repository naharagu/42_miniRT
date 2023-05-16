/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saikeda <saikeda@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 19:37:49 by saikeda           #+#    #+#             */
/*   Updated: 2023/05/15 21:08:05 by saikeda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shape.h"
#include "main.h"
#include "raytrace.h"
#include "vector.h"
#include <math.h>

bool	intersect_plane(t_shape *shape, t_ray *ray, t_intersect *intersect, t_scene *scene)
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
	intersect->point = vec3_addition(ray->origin, vec3_multiply_scalar(ray->dir, d.t));
	intersect->normal = shape->normal;
	scene->light.dir = vec3_normalize(vec3_subtraction(scene->light.origin,
				intersect->point));
	intersect->distance = d.t;
	return (true);
}
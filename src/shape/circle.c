/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   circle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saikeda <saikeda@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 08:39:54 by saikeda           #+#    #+#             */
/*   Updated: 2023/06/20 23:08:31 by saikeda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shape.h"
#include "main.h"
#include "raytrace.h"
#include "vector.h"
#include <math.h>

static void	calc_intersect_circle(t_shape *shape, t_intersect *intersect)
{
	t_vec3	p;

	intersect->b_normal = intersect->normal;
	p = vec3_subtraction(intersect->point, shape->center);
	intersect->pi_x = acos(vec3_dot_product(p, \
				shape->unit_x) / vec3_magnitude(p));
	if (isnan(intersect->pi_x) || isinf(intersect->pi_x))
		intersect->pi_x = 0.0;
	if (vec3_dot_product(p, shape->unit_y) > 0)
			intersect->pi_x = 2 * M_PI - intersect->pi_x;
	intersect->color_idx_x = \
		calc_circle_index(intersect->pi_x, (double)shape->color_div);
	intersect->color_idx_y = 0;
	checkerboard_color(shape, intersect);
}

bool	intersect_circle(t_shape *shape, t_ray *ray, t_intersect *intersect)
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
	if (vec3_magnitude(vec3_subtraction(intersect->point, shape->center)) > \
						shape->radius)
		return (false);
	intersect->normal = shape->normal;
	intersect->distance = d.t;
	calc_intersect_circle(shape, intersect);
	intersect->type = shape->type;
	intersect->index = shape->index;
	return (true);
}

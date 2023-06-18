/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharagu <naharagu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 19:37:49 by saikeda           #+#    #+#             */
/*   Updated: 2023/06/18 22:53:38 by naharagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shape.h"
#include "main.h"
#include "raytrace.h"
#include "vector.h"
#include <math.h>

static size_t	calc_plane_index(double pi, size_t division)
{
	size_t	index;

	if (pi < 0)
		pi = pi * -1 + division;
	index = (size_t)(pi / division);
	return (index);
}

// static void	bump_plane(t_shape *shape, t_intersect *intersect)
// {
// }

static void	calc_intersect_plane(t_shape *shape, t_intersect *intersect)
{
	t_vec3	p;

	intersect->b_normal = intersect->normal;
	p = vec3_subtraction(intersect->point, shape->center);
	intersect->pi_x = vec3_dot_product(p, shape->unit_x);
	if (isnan(intersect->pi_x) || isinf(intersect->pi_x))
		intersect->pi_x = 0.0;
	intersect->pi_y = vec3_dot_product(p, shape->unit_z);
	if (isnan(intersect->pi_y) || isinf(intersect->pi_y))
		intersect->pi_y = 0.0;
	intersect->color_idx_x = \
		calc_plane_index(intersect->pi_x, shape->color_div);
	intersect->color_idx_y = \
		calc_plane_index(intersect->pi_y, shape->color_div);
	checkerboard_color(shape, intersect);
	if (intersect->bump == true)
	{
		intersect->bump_idx_x = \
			calc_plane_index(intersect->pi_x, shape->bump_div);
		intersect->bump_idx_y = \
			calc_plane_index(intersect->pi_y, shape->bump_div);
		// bump_plane(shape, intersect);
	}
}

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
	intersect->b_normal = intersect->normal;
	intersect->distance = d.t;
	calc_intersect_plane(shape, intersect);
	intersect->index = shape->index;
	return (true);
}

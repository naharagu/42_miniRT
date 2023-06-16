/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saikeda <saikeda@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 07:28:08 by saikeda           #+#    #+#             */
/*   Updated: 2023/06/15 22:24:42 by saikeda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shape.h"
#include "main.h"
#include "raytrace.h"
#include "vector.h"
#include <math.h>

static void	precalc_cone(t_shape *shape, t_ray *ray, t_discriminant *d)
{
	t_vec3	p;
	t_vec3	s;

	p = vec3_subtraction(shape->center, ray->origin);
	s = shape->normal;
	d->vv = vec3_dot_product(ray->dir, ray->dir);
	d->sv = vec3_dot_product(s, ray->dir);
	d->pv = vec3_dot_product(p, ray->dir);
	d->ss = vec3_dot_product(s, s);
	d->ps = vec3_dot_product(p, s);
	d->pp = vec3_dot_product(p, p);
	if (d->ss != 0)
	{
		d->a = d->vv - (pow(d->sv, 2) / d->ss) - \
		(pow(d->sv, 2) / pow(d->ss, 2) * pow(shape->radius / shape->height, 2));
		d->b = d->pv - (d->ps * d->sv / d->ss) - \
		(d->ps * d->sv / pow(d->ss, 2) * pow(shape->radius / shape->height, 2));
		d->c = d->pp - (pow(d->ps, 2) / d->ss) - \
		(pow(d->ps, 2) / pow(d->ss, 2) * pow(shape->radius / shape->height, 2));
		d->discriminant = d->b * d->b - d->a * d->c;
	}
}

static bool	within_cone(t_shape *shape, \
							t_intersect *intersect, t_discriminant *d)
{
	d->t2 = (vec3_dot_product(intersect->point, shape->normal) - \
				vec3_dot_product(shape->center, shape->normal));
	if (0 <= d->t2 && d->t2 <= shape->height)
	{
		intersect->normal = \
			vec3_normalize(vec3_subtraction(intersect->point, \
			vec3_addition(shape->center, \
			vec3_multiply_scalar(shape->normal, d->t2))));
		intersect->distance = d->t;
		// intersect->b_normal = intersect->normal;
		// intersect->color = shape->colors->color;
		calc_intersect_cylinder(shape, intersect, d);
		intersect->index = shape->index;
		return (true);
	}
	return (false);
}

bool	intersect_cone(t_shape *shape, t_ray *ray, t_intersect *intersect)
{
	t_discriminant	d;

	precalc_cone(shape, ray, &d);
	if (d.ss == 0 || d.a == 0 || d.discriminant < 0)
		return (false);
	d.discriminant = sqrt(d.discriminant);
	d.t = (d.b - d.discriminant) / d.a;
	intersect->point = \
		vec3_addition(ray->origin, vec3_multiply_scalar(ray->dir, d.t));
	if (d.t < 0.0 || within_cone(shape, intersect, &d) == false)
	{
		d.t = (d.b + d.discriminant) / d.a;
		intersect->point = \
			vec3_addition(ray->origin, vec3_multiply_scalar(ray->dir, d.t));
		return (0.0 <= d.t && within_cone(shape, intersect, &d));
	}
	return (true);
}

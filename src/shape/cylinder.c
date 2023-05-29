/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharagu <naharagu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 21:10:48 by saikeda           #+#    #+#             */
/*   Updated: 2023/05/29 22:21:18 by naharagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shape.h"
#include "main.h"
#include "raytrace.h"
#include "vector.h"
#include <math.h>

static void	precalc_cylinder(t_shape *shape, t_ray *ray, t_discriminant *d)
{
	t_vec3	p;
	t_vec3	p2;
	t_vec3	s;

	p = vec3_subtraction(shape->center, ray->origin);
	p2 = vec3_addition(shape->center, \
			vec3_multiply_scalar(shape->normal, shape->height));
	p2 = vec3_subtraction(p2, ray->origin);
	s = vec3_subtraction(p2, p);
	d->vv = vec3_dot_product(ray->dir, ray->dir);
	d->sv = vec3_dot_product(s, ray->dir);
	d->pv = vec3_dot_product(p, ray->dir);
	d->ss = vec3_dot_product(s, s);
	d->ps = vec3_dot_product(p, s);
	d->pp = vec3_dot_product(p, p);
	if (d->ss != 0)
	{
		d->a = d->vv - d->sv * d->sv / d->ss;
		d->b = d->pv - d->ps * d->sv / d->ss;
		d->c = d->pp - d->ps * d->ps / d->ss - \
							(shape->radius * shape->radius);
		d->discriminant = d->b * d->b - d->a * d->c;
	}
}

static bool	within_cylinder(t_shape *shape, \
							t_intersect *intersect, t_discriminant *d)
{
	d->t2 = (vec3_dot_product(intersect->point, shape->normal) - \
				vec3_dot_product(shape->center, shape->normal)) / \
				vec3_dot_product(shape->normal, shape->normal);
	if (0 <= d->t2 && d->t2 <= shape->height)
	{
		intersect->normal = \
			vec3_normalize(vec3_subtraction(intersect->point, \
			vec3_addition(shape->center, \
			vec3_multiply_scalar(shape->normal, d->t2))));
		intersect->distance = d->t;
		intersect->color = shape->color;
		intersect->index = shape->index;
		return (true);
	}
	return (false);
}

bool	intersect_cylinder(t_shape *shape, t_ray *ray, t_intersect *intersect)
{
	t_discriminant	d;

	precalc_cylinder(shape, ray, &d);
	if (d.ss == 0 || d.a == 0 || d.discriminant < 0)
		return (false);
	d.discriminant = sqrt(d.discriminant);
	d.t = (d.b - d.discriminant) / d.a;
	intersect->point = \
		vec3_addition(ray->origin, vec3_multiply_scalar(ray->dir, d.t));
	if (d.t < 0.0 || within_cylinder(shape, intersect, &d) == false)
	{
		d.t = (d.b + d.discriminant) / d.a;
		intersect->point = \
			vec3_addition(ray->origin, vec3_multiply_scalar(ray->dir, d.t));
		return (0.0 <= d.t && within_cylinder(shape, intersect, &d));
	}
	return (true);
}

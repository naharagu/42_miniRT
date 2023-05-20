/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saikeda <saikeda@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 21:10:48 by saikeda           #+#    #+#             */
/*   Updated: 2023/05/20 10:54:11 by saikeda          ###   ########.fr       */
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
	d->Dvv = vec3_dot_product(ray->dir, ray->dir);
	d->Dsv = vec3_dot_product(s, ray->dir);
	d->Dpv = vec3_dot_product(p, ray->dir);
	d->Dss = vec3_dot_product(s, s);
	d->Dps = vec3_dot_product(p, s);
	d->Dpp = vec3_dot_product(p, p);
	if (d->Dss != 0)
	{
		d->a = d->Dvv - d->Dsv * d->Dsv / d->Dss;
		d->b = d->Dpv - d->Dps * d->Dsv / d->Dss;
		d->c = d->Dpp - d->Dps * d->Dps / d->Dss - \
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
	if (d.Dss == 0 || d.a == 0 || d.discriminant < 0)
		return (false);
	d.discriminant = sqrt(d.discriminant);
	d.t = (d.b - d.discriminant) / d.a;
	intersect->point = \
		vec3_addition(ray->origin, vec3_multiply_scalar(ray->dir, d.t));
	if (within_cylinder(shape, intersect, &d) == false)
	{
		d.t = (d.b + d.discriminant) / d.a;
		intersect->point = \
			vec3_addition(ray->origin, vec3_multiply_scalar(ray->dir, d.t));
		return (within_cylinder(shape, intersect, &d));
	}
	return (true);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saikeda <saikeda@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 21:34:41 by naharagu          #+#    #+#             */
/*   Updated: 2023/06/18 10:22:36 by saikeda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shape.h"
#include "main.h"
#include "raytrace.h"
#include "vector.h"
#include <math.h>

static void	calc_sphere_pi(t_shape *shape, t_intersect *intersect)
{
	intersect->pro_x = vec3_subtraction(intersect->normal, \
		vec3_multiply_scalar(shape->unit_y, \
		vec3_dot_product(intersect->normal, shape->unit_y)));
	if (vec3_magnitude(intersect->pro_x) == 0.0)
		intersect->pi_x = 0.0;
	else
	{
		intersect->pi_x = acos(vec3_dot_product(intersect->pro_x, \
			shape->unit_x) / (vec3_magnitude(intersect->pro_x)));
		if (isnan(intersect->pi_x) || isinf(intersect->pi_x))
			intersect->pi_x = 0.0;
		if (vec3_dot_product(intersect->pro_x, shape->unit_z) > 0)
			intersect->pi_x = 2 * M_PI - intersect->pi_x;
	}
	intersect->pro_y = vec3_subtraction(intersect->normal, \
		vec3_multiply_scalar(shape->unit_x, \
		vec3_dot_product(intersect->normal, shape->unit_x)));
	if (vec3_magnitude(intersect->pro_y) == 0.0)
		intersect->pi_y = 0.0;
	else
	{
		intersect->pi_y = \
			acos(vec3_dot_product(intersect->pro_y, shape->unit_y) \
			/ (vec3_magnitude(intersect->pro_y)));
		if (isnan(intersect->pi_y) || isinf(intersect->pi_y))
			intersect->pi_y = 0.0;
	}
}

size_t	calc_circle_index(double pi, double division)
{
	double	tmp;
	size_t	index;

	tmp = 0.0;
	index = 0;
	while (1)
	{
		tmp += 2 * M_PI / division;
		if (pi <= tmp)
			return (index);
		index++;
	}
	return (index);
}

void	checkerboard_color(t_shape *shape, t_intersect *intersect)
{
	size_t	index;
	t_color	*tmp;

	index = intersect->color_idx_x + intersect->color_idx_y;
	index %= shape->colors_cnt;
	tmp = shape->colors;
	while (1)
	{
		if (index == 0)
			break ;
		index--;
		tmp = tmp->next;
	}
	intersect->color = tmp->color;
}

static void	sphere_b_normal(t_shape *shape, t_intersect *intersect)
{
	t_bump_map	*tmp;
	size_t		i;

	tmp = shape->bump_map;
	if (tmp == NULL)
		intersect->b_normal = shape->normal;
	else
	{
		i = 0;
		while (i < \
			intersect->bump_idx_x * shape->bump_div + intersect->bump_idx_y)
		{
			tmp = tmp->next;
			i++;
		}
		intersect->b_normal = tmp->b_normal;
	}
}

static void	calc_intersect_sphere(t_shape *shape, t_intersect *intersect)
{
	intersect->b_normal = intersect->normal;
	calc_sphere_pi(shape, intersect);
	intersect->color_idx_x = \
		calc_circle_index(intersect->pi_x, (double)shape->color_div);
	intersect->color_idx_y = \
		calc_circle_index(intersect->pi_y, (double)shape->color_div);
	checkerboard_color(shape, intersect);
	intersect->bump = shape->bump_flag;
	if (intersect->bump == true)
	{
		intersect->bump_idx_x = \
			calc_circle_index(intersect->pi_x, (double)shape->bump_div);
		intersect->bump_idx_y = \
			calc_circle_index(intersect->pi_y, (double)shape->bump_div);
		sphere_b_normal(shape, intersect);
	}
}

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
		calc_intersect_sphere(shape, intersect);
		intersect->index = shape->index;
		return (true);
	}
	return (false);
}

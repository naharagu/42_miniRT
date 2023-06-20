/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saikeda <saikeda@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 21:10:48 by saikeda           #+#    #+#             */
/*   Updated: 2023/06/20 17:06:02 by saikeda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shape.h"
#include "main.h"
#include "raytrace.h"
#include "vector.h"
#include <math.h>

size_t	calc_cylinder_index(double height, double current, double division)
{
	double	tmp;
	size_t	index;

	tmp = 0.0;
	index = 0;
	while (1)
	{
		tmp += height / division;
		if (current <= tmp)
			break ;
		index++;
	}
	return (index);
}

static void	cylinder_b_normal(t_shape *shape, t_intersect *intersect)
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
			intersect->bump_idx_x)
		{
			tmp = tmp->next;
			i++;
		}
		intersect->b_normal = tmp->b_normal;
	}
}

void	calc_intersect_cylinder(t_shape *shape, t_intersect *intersect, \
													t_discriminant *d)
{
	intersect->b_normal = intersect->normal;
	intersect->pi_x = acos(vec3_dot_product(intersect->normal, \
			shape->unit_x) / (vec3_magnitude(intersect->normal)));
	if (isnan(intersect->pi_x) || isinf(intersect->pi_x))
		intersect->pi_x = 0.0;
	if (vec3_dot_product(intersect->normal, shape->unit_y) > 0)
			intersect->pi_x = 2 * M_PI - intersect->pi_x;
	intersect->color_idx_x = \
		calc_circle_index(intersect->pi_x, (double)shape->color_div);
	intersect->color_idx_y = \
		calc_cylinder_index(shape->height, d->t2, (double)shape->color_div);
	checkerboard_color(shape, intersect);
	intersect->bump = shape->bump_flag;
	if (intersect->bump == true)
	{
		intersect->bump_idx_x = \
			calc_circle_index(intersect->pi_x, (double)shape->bump_div);
		intersect->bump_idx_y = \
			calc_cylinder_index(shape->height, d->t2, (double)shape->bump_div);
		cylinder_b_normal(shape, intersect);
	}
}

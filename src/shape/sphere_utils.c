/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saikeda <saikeda@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 12:59:59 by saikeda           #+#    #+#             */
/*   Updated: 2023/06/20 16:45:20 by saikeda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shape.h"
#include "main.h"
#include "raytrace.h"
#include "vector.h"
#include <math.h>

static void	calc_pi_x(t_shape *shape, t_intersect *intersect)
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
}

static void	calc_pi_y(t_shape *shape, t_intersect *intersect)
{
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

void	calc_sphere_pi(t_shape *shape, t_intersect *intersect)
{
	calc_pi_x(shape, intersect);
	calc_pi_y(shape, intersect);
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
			break ;
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

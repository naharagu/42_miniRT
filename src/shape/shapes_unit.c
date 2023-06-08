/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapes_unit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saikeda <saikeda@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 19:01:06 by saikeda           #+#    #+#             */
/*   Updated: 2023/06/06 22:26:40 by saikeda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shape.h"
#include "parse.h"
#include "exit.h"
#include "libft.h"

static void	sphere_unit(t_window *window, t_shape *shape)
{
	shape->unit_x = window->screen.e_sx;
	shape->unit_y = window->screen.e_sy;
	shape->unit_z = window->scene->camera.dir;
}

static void	plane_unit(t_window *window, t_shape *shape)
{
	double	norm;

	shape->unit_y = shape->normal;
	shape->unit_z = vec3_normalize(vec3_cross_product(shape->unit_y, \
												window->screen.e_sx));
	norm = vec3_dot_product(shape->unit_z, shape->unit_z);
	if (norm < 1.0 - EPSILON || 1.0 + EPSILON < norm)
	{
		shape->unit_z.x = 0;
		shape->unit_z.y = 0;
		shape->unit_z.z = 1;
	}
	shape->unit_x = vec3_normalize(vec3_cross_product(shape->unit_y, \
													shape->unit_z));
}

static void	cylinder_unit(t_window *window, t_shape *shape)
{
	double	norm;

	shape->unit_z = shape->normal;
	shape->unit_x = \
		vec3_normalize(vec3_cross_product(shape->unit_z, window->screen.e_sy));
	norm = vec3_dot_product(shape->unit_x, shape->unit_x);
	if (norm < 1.0 - EPSILON || 1.0 + EPSILON < norm)
	{
		shape->unit_z.x = 1;
		shape->unit_z.y = 0;
		shape->unit_z.z = 0;
	}
	shape->unit_y = \
		vec3_normalize(vec3_cross_product(shape->unit_x, shape->unit_z));
}

void	shapes_unit(t_window *window)
{
	t_shape	*tmp;

	tmp = window->scene->shapes;
	while (tmp)
	{
		if (tmp->type == SPHERE)
			sphere_unit(window, tmp);
		else if (tmp->type == PLANE)
			plane_unit(window, tmp);
		else if (tmp->type == CYLINDER || tmp->type == CONE)
			cylinder_unit(window, tmp);
		tmp = tmp->next;
	}
}

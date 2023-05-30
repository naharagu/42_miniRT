/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharagu <naharagu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 10:51:00 by saikeda           #+#    #+#             */
/*   Updated: 2023/05/29 13:37:30 by naharagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "raytrace.h"
#include <math.h>

static bool	intersect_helper(t_shape *shape, t_ray *ray, t_intersect *intersect)
{
	if (shape->type == SPHERE)
		return (intersect_sphere(shape, ray, intersect));
	else if (shape->type == PLANE)
		return (intersect_plane(shape, ray, intersect));
	else if (shape->type == CYLINDER)
		return (intersect_cylinder(shape, ray, intersect));
	return (false);
}

bool	calculate_intersect_point(t_ray *ray, t_intersect *intersect, \
									t_scene *scene, ssize_t intersect_index)
{
	t_shape		*current_shape;
	t_intersect	nearest_intersect;

	current_shape = scene->shapes;
	nearest_intersect.distance = INFINITY;
	while (current_shape)
	{
		if (current_shape->index != intersect_index && \
			intersect_helper(current_shape, ray, intersect) && \
			intersect->distance < nearest_intersect.distance)
			nearest_intersect = *intersect;
		current_shape = current_shape->next;
	}
	if (nearest_intersect.distance == INFINITY)
		return (false);
	*intersect = nearest_intersect;
	return (true);
}

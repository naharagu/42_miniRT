/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharagu <naharagu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 10:14:45 by naharagu          #+#    #+#             */
/*   Updated: 2023/04/26 19:20:39by naharagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "raytrace.h"
#include <math.h>
#include "test.h"

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

bool	calculate_intersect_point(t_ray *ray, t_intersect *intersect, t_scene *scene)
{
	t_shape		*current_shape;
	t_shape 	*nearest_shape;
	t_intersect	nearest_intersect;

	current_shape = scene->shapes;
	nearest_shape = NULL;
	nearest_intersect.distance = INFINITY;
	while (current_shape)
	{
		if (intersect_helper(current_shape, ray, intersect))
		{
			if (intersect->distance < nearest_intersect.distance)
			{
				nearest_shape = current_shape;
				nearest_intersect = *intersect;
			}
		}
		current_shape = current_shape->next;
	}
	if (nearest_shape == NULL)
		return (false);
	*intersect = nearest_intersect;
	scene->light.dir = vec3_normalize(vec3_subtraction(scene->light.origin, intersect->point));
	return (true);
}

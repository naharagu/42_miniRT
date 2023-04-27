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

static bool	intersect_helper(t_shape *shape, t_ray *ray, t_intersect *intersect, t_scene *scene)
{
	if (shape->type == SPHERE)
		return (intersect_sphere(shape, ray, intersect, scene));
	// else if (shape->type == PLANE)
		// return (intersect_plane(shape, ray, scene));
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
		if (intersect_helper(current_shape, ray, intersect, scene))
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
	return (true);
}

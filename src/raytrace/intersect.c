/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharagu <naharagu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 10:14:45 by naharagu          #+#    #+#             */
/*   Updated: 2023/04/26 14:37:12 by naharagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "raytrace.h"
#include <math.h>
#include "test.h"

static bool	intersect_helper(t_shape *shape, t_vec3 *ray, t_scene *scene)
{
	if (shape->type == SPHERE)
		return (intersect_sphere(shape, ray, scene));
	// else if (shape->type == PLANE)
	// 	return (intersect_plane(shape, ray, scene));
	return (false);
}

bool	calculate_intersect_point(t_scene *scene, t_vec3 *ray)
{
	// get nearest intersect point
	// if (intersect_sphere(scene->shapes, ray, scene))
	t_shape	*tmp_shape;
	double	nearest_distance;

	nearest_distance = INFINITY;
	tmp_shape = scene->shapes;
	while (tmp_shape)
	{
		if (intersect_helper(tmp_shape, ray, scene))
		{
			if (vec3_magnitude(vec3_subtraction(scene->intersect.point, \
							scene->camera.origin)) < nearest_distance)
			{
				nearest_distance = vec3_magnitude(vec3_subtraction(scene->intersect.point,
							scene->camera.origin));
			}
		}
		tmp_shape = tmp_shape->next;
	}
	return (intersect_helper(scene->shapes, ray, scene));
}

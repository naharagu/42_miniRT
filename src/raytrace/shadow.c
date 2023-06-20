/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saikeda <saikeda@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 18:45:53 by saikeda           #+#    #+#             */
/*   Updated: 2023/06/20 18:49:34 by saikeda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytrace.h"
#include "parse.h"
#include "vector.h"
#include <math.h>

bool	intersect_helper(t_shape *shape, t_ray *ray, t_intersect *intersect);

static bool	calculate_shadow_point(t_ray *ray, t_intersect *intersect, \
									t_scene *scene, ssize_t intersect_index)
{
	t_shape		*current_shape;
	t_intersect	nearest_intersect;

	current_shape = scene->shapes;
	nearest_intersect.distance = INFINITY;
	while (current_shape)
	{
		if (current_shape->type != CIRCLE && \
			current_shape->index != intersect_index && \
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

bool	shadow_intersect(t_intersect *intersect, \
									t_scene *scene, t_light *light)
{
	t_ray		shadow_ray;
	t_intersect	shadow_intersect;

	shadow_ray.origin = intersect->point;
	shadow_ray.dir = light->dir;
	return (calculate_shadow_point(&shadow_ray, &shadow_intersect, \
	scene, intersect->index) == true && \
	EPSILON < shadow_intersect.distance && \
	shadow_intersect.distance < \
	vec3_magnitude(vec3_subtraction(light->origin, intersect->point)));
}

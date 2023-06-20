/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saikeda <saikeda@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 18:45:53 by saikeda           #+#    #+#             */
/*   Updated: 2023/06/20 23:28:49 by saikeda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytrace.h"
#include "parse.h"
#include "vector.h"
#include <math.h>

bool	intersect_helper(t_shape *shape, t_ray *ray, t_intersect *intersect);

static bool	is_subshape(t_shape *current, t_intersect *intersect)
{
	if (current->type == CYLINDER && \
		current->index < intersect->index && \
		intersect->index - current->index <= 2 && \
		intersect->type == CIRCLE)
		return (true);
	else if (current->type == CONE && \
		current->index < intersect->index && \
		intersect->index - current->index == 1 && \
		intersect->type == CIRCLE)
		return (true);
	else if (current->type == CIRCLE && \
		((current->index > intersect->index && \
		current->index - intersect->index == 1 && \
		intersect->type == CONE) || \
		(current->index > intersect->index && \
		current->index - intersect->index <= 2 && \
		intersect->type == CYLINDER)))
		return (true);
	return (false);
}

static bool	calculate_shadow_point(t_ray *ray, t_intersect *shadow_intersect, \
									t_scene *scene, t_intersect *intersect)
{
	t_shape		*current_shape;
	t_intersect	nearest_intersect;

	current_shape = scene->shapes;
	nearest_intersect.distance = INFINITY;
	while (current_shape)
	{
		if (current_shape->index != intersect->index && \
			is_subshape(current_shape, intersect) == false && \
			intersect_helper(current_shape, ray, shadow_intersect) == true && \
			shadow_intersect->distance < nearest_intersect.distance)
			nearest_intersect = *shadow_intersect;
		current_shape = current_shape->next;
	}
	if (nearest_intersect.distance == INFINITY)
		return (false);
	*shadow_intersect = nearest_intersect;
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
	scene, intersect) == true && \
	EPSILON < shadow_intersect.distance && \
	shadow_intersect.distance < \
	vec3_magnitude(vec3_subtraction(light->origin, intersect->point)));
}

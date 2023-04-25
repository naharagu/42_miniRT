/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharagu <naharagu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 19:00:18 by naharagu          #+#    #+#             */
/*   Updated: 2023/04/25 22:09:17 by naharagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

void	print_color(t_color color)
{
	printf("r: %f, g: %f, b: %f\n", color.x, color.y, color.z);
}

void	print_vec3(t_vec3 vec)
{
	printf("x: %f, y: %f, z: %f\n", vec.x, vec.y, vec.z);
}

void	print_t_scene(t_scene *scene)
{
	printf("ambient_ratio: %f\n", scene->ambient_ratio);
	printf("ambient_color: ");
	print_color(scene->ambient_color);
	printf("camera.origin: ");
	print_vec3(scene->camera.origin);
	printf("camera.dir: ");
	print_vec3(scene->camera.dir);
	printf("camera.fov: %f\n", scene->camera.fov);
	printf("light.origin: ");
	print_vec3(scene->light.origin);
	printf("light.intensity: %f]\n", scene->light.intensity);
	printf("light.color: ");
	print_color(scene->light.color);
}

void	print_t_shape(t_shape *shape)
{
	printf("type: %d\n", shape->type);
	printf("center: ");
	print_vec3(shape->center);
	printf("radius: %f\n", shape->radius);
	printf("color: ");
	print_color(shape->color);
}

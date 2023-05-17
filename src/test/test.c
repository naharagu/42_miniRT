/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saikeda <saikeda@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 19:00:18 by naharagu          #+#    #+#             */
/*   Updated: 2023/05/10 21:38:29 by saikeda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

void	put_titile_in_green(char *title)
{
	printf("\033[32m===%s===\033[0m\n", title);
}

void	print_color(t_color color)
{
	printf("r: %.1f, g: %.1f, b: %.1f\n", color.x, color.y, color.z);
}

void	print_vec3(t_vec3 vec)
{
	printf("x: %.1f, y: %.1f, z: %.1f\n", vec.x, vec.y, vec.z);
}

void	print_t_scene(t_scene *scene)
{
	put_titile_in_green("t_scene");
	printf("ambient_ratio: %.1f\n", scene->ambient_ratio);
	printf("ambient_color: ");
	print_color(scene->ambient_color);
	printf("camera.origin: ");
	print_vec3(scene->camera.origin);
	printf("camera.dir: ");
	print_vec3(scene->camera.dir);
	printf("camera.fov: %.1f\n", scene->camera.fov);
	printf("light.origin: ");
	print_vec3(scene->light.origin);
	printf("light.intensity: %.1f\n", scene->light.intensity);
	printf("light.color: ");
	print_color(scene->light.color);
}

int	num_shape = 0;
void	print_t_shape(t_shape *shape)
{
	put_titile_in_green("t_shape");
	num_shape++;
	if (shape->type == SPHERE)
	{
		printf("No.%d ", num_shape);
		printf("SPHERE\n");
		printf("center: ");
		print_vec3(shape->center);
		printf("radius: %lf\n", shape->radius);
		printf("color: ");
		print_color(shape->color);
	}
	else if (shape->type == PLANE)
	{
		printf("No.%d ", num_shape);
		printf("PLANE\n");
		printf("center: ");
		print_vec3(shape->center);
		printf("normal: ");
		print_vec3(shape->normal);
		printf("color: ");
		print_color(shape->color);
	}
	else if (shape->type == CYLINDER)
	{
		printf("No.%d ", num_shape);
		printf("CYLINDER\n");
		printf("center: ");
		print_vec3(shape->center);
		printf("normal: ");
		print_vec3(shape->normal);
		printf("radius: %lf\n", shape->radius);
		printf("height: %lf\n", shape->height);
		printf("color: ");
		print_color(shape->color);
	}
	else
	{
		printf("No.%d\n", num_shape);
		printf("Error: Invalid shape type\n");
	}
}

void	print_shape_lst(t_shape *shape)
{
	while (shape)
	{
		print_t_shape(shape);
		shape = shape->next;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_shape.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saikeda <saikeda@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 08:47:34 by naharagu          #+#    #+#             */
/*   Updated: 2023/06/02 09:03:05 by saikeda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "exit.h"
#include "libft.h"
#include "utils.h"
#include "shape.h"

void	parse_sphere(char **str_array, t_scene *scene)
{
	t_shape	*shape;

	if (count_array(str_array) != 4)
		put_error_and_exit("Invalid sphere format");
	shape = shape_lst_add(scene);
	shape->type = SPHERE;
	shape->center = parse_vec3(str_array[1]);
	shape->radius = ft_atod(str_array[2]) / 2;
	shape->color = parse_color(str_array[3]);
}

void	parse_plane(char **str_array, t_scene *scene)
{
	t_shape	*shape;

	if (count_array(str_array) != 4)
		put_error_and_exit("Invalid plane format");
	shape = shape_lst_add(scene);
	shape->type = PLANE;
	shape->center = parse_vec3(str_array[1]);
	shape->normal = parse_vec3(str_array[2]);
	check_normalized(shape->normal);
	shape->color = parse_color(str_array[3]);
}

void	parse_cylinder(char **str_array, t_scene *scene)
{
	t_shape	*shape;

	if (count_array(str_array) != 6)
		put_error_and_exit("Invalid cylinder format");
	shape = shape_lst_add(scene);
	shape->type = CYLINDER;
	shape->center = parse_vec3(str_array[1]);
	shape->normal = parse_vec3(str_array[2]);
	check_normalized(shape->normal);
	shape->radius = ft_atod(str_array[3]) / 2;
	shape->height = ft_atod(str_array[4]);
	shape->color = parse_color(str_array[5]);
}

void	parse_cone(char **str_array, t_scene *scene)
{
	t_shape	*shape;

	if (count_array(str_array) != 6)
		put_error_and_exit("Invalid cone format");
	shape = shape_lst_add(scene);
	shape->type = CONE;
	shape->center = parse_vec3(str_array[1]);
	shape->normal = parse_vec3(str_array[2]);
	check_normalized(shape->normal);
	shape->radius = ft_atod(str_array[3]) / 2;
	shape->height = ft_atod(str_array[4]);
	shape->color = parse_color(str_array[5]);
}

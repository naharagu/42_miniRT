/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_shape.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharagu <naharagu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 08:47:34 by naharagu          #+#    #+#             */
/*   Updated: 2023/04/26 20:15:53 by naharagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "exit.h"
#include "libft.h"
#include "utils.h"
#include "shape.h"
#include "test.h"

void	parse_sphere(char **str_array, t_scene *scene)
{
	t_shape	*shape;

	if (count_array(str_array) != 4)
		put_error_and_exit("Invalid sphere format");
	shape = shape_lst_add(scene);
	shape->type = SPHERE;
	shape->center = parse_vec3(str_array[1]);
	shape->radius = ft_atod(str_array[2]) / 2;
	shape->color = parse_vec3(str_array[3]);
	// print_t_shape(shape);
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
	shape->color = parse_vec3(str_array[3]);
}

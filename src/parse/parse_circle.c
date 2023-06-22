/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_circle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saikeda <saikeda@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 08:22:53 by saikeda           #+#    #+#             */
/*   Updated: 2023/06/23 07:07:43 by saikeda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "exit.h"
#include "libft.h"
#include "utils.h"
#include "shape.h"

void	color_lst_add(t_shape *shape, t_color *color_ptr);

static void	copy_colors(t_color *colors, t_shape *shape)
{
	t_color	*tmp;

	shape->colors = NULL;
	while (colors)
	{
		tmp = malloc(sizeof(t_color));
		if (tmp == NULL)
			put_error_and_exit("Failed allocate");
		tmp->color = colors->color;
		tmp->next = NULL;
		color_lst_add(shape, tmp);
		colors = colors->next;
	}
}

void	parse_bottom_circle(t_scene *scene, t_shape *shape)
{
	t_shape	*new;

	new = shape_lst_add(scene);
	new->type = CIRCLE;
	new->center = shape->center;
	new->normal = vec3_multiply_scalar(shape->normal, -1);
	new->radius = shape->radius;
	copy_colors(shape->colors, new);
	new->colors_cnt = shape->colors_cnt;
	new->color_div = shape->color_div;
	new->bump_flag = shape->bump_flag;
	new->bump_div = shape->bump_div;
	scene->shapes_num++;
	if (scene->shapes_num > LIMIT_SHAPES)
		put_error_and_exit("Invalid shapes num");
}

void	parse_top_circle(t_scene *scene, t_shape *shape)
{
	t_shape	*new;

	new = shape_lst_add(scene);
	new->type = CIRCLE;
	new->center = vec3_addition(shape->center, \
		vec3_multiply_scalar(shape->normal, shape->height));
	new->normal = shape->normal;
	new->radius = shape->radius;
	copy_colors(shape->colors, new);
	new->colors_cnt = shape->colors_cnt;
	new->color_div = shape->color_div;
	new->bump_flag = shape->bump_flag;
	new->bump_div = shape->bump_div;
	scene->shapes_num++;
	if (scene->shapes_num > LIMIT_SHAPES)
		put_error_and_exit("Invalid shapes num");
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saikeda <saikeda@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 08:47:34 by naharagu          #+#    #+#             */
/*   Updated: 2023/06/06 22:21:58 by saikeda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "exit.h"
#include "libft.h"
#include "utils.h"

t_vec3	parse_color(char *str)
{
	t_vec3	color;
	char	**str_array;

	str_array = ft_split(str, ',');
	if (str_array == NULL)
		put_error_and_exit("Failed to split color");
	if (count_array(str_array) != 3)
		put_error_and_exit("Invalid color format");
	color.x = ft_atod(str_array[0]);
	color.y = ft_atod(str_array[1]);
	color.z = ft_atod(str_array[2]);
	if (is_in_range_int(color.x, 0, 255) == false
		|| is_in_range_int(color.y, 0, 255) == false
		|| is_in_range_int(color.z, 0, 255) == false)
		put_error_and_exit("Invalid color format");
	free_split(str_array);
	return (color);
}

static t_color	*make_color(char **str_array, size_t index)
{
	char	**vec_array;
	t_color	*color_ptr;

	vec_array = ft_split(str_array[index], ',');
	if (vec_array == NULL)
		return (NULL);
	if (count_array(vec_array) != 3)
	{
		free_split(vec_array);
		return (NULL);
	}
	color_ptr = malloc(sizeof(t_color));
	if (color_ptr == NULL)
		put_error_and_exit("Failed allocate");
	color_ptr->color = vec3_create(ft_atod(vec_array[0]), \
						ft_atod(vec_array[1]), ft_atod(vec_array[2]));
	free_split(vec_array);
	if (is_in_range_int(color_ptr->color.x, 0, 255) == false
		|| is_in_range_int(color_ptr->color.y, 0, 255) == false
		|| is_in_range_int(color_ptr->color.z, 0, 255) == false)
	{
		free(color_ptr);
		return (NULL);
	}
	color_ptr->next = NULL;
	return (color_ptr);
}

static void	color_lst_add(t_shape *shape, t_color *color_ptr)
{
	t_color	*tmp;

	if (shape->colors == NULL)
		shape->colors = color_ptr;
	else
	{
		tmp = shape->colors;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = color_ptr;
	}
	shape->colors_cnt++;
}

static size_t	parse_color_div(t_shape *shape, char **str_array, size_t index)
{
	int	num;

	if (str_array[index] == NULL || ft_strcmp(str_array[index], "bump") == 0)
	{
		shape->color_div = 1;
		return (index);
	}
	else
	{
		num = ft_atoi(str_array[index]);
		if (num <= 0)
			put_error_and_exit("Invalid color_div format");
		shape->color_div = (size_t)num;
		return (++index);
	}
}

size_t	parse_colors(t_shape *shape, char **str_array, size_t index)
{
	t_color	*tmp;

	shape->colors = NULL;
	shape->colors_cnt = 0;
	while (1)
	{
		tmp = make_color(str_array, index);
		if (tmp == NULL)
			break ;
		color_lst_add(shape, tmp);
		index++;
	}
	if (shape->colors == NULL)
		put_error_and_exit("Invalid color format");
	index = parse_color_div(shape, str_array, index);
	return (index);
}

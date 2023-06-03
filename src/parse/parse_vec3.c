/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_vec3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saikeda <saikeda@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 08:47:34 by naharagu          #+#    #+#             */
/*   Updated: 2023/06/04 00:46:33 by saikeda          ###   ########.fr       */
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

bool	check_range_vec3(t_vec3 vec3)
{
	if (vec3.x < -LIMIT_RANGE || LIMIT_RANGE < vec3.x)
		return (false);
	if (vec3.y < -LIMIT_RANGE || LIMIT_RANGE < vec3.y)
		return (false);
	if (vec3.z < -LIMIT_RANGE || LIMIT_RANGE < vec3.z)
		return (false);
	return (true);
}

t_vec3	parse_vec3(char *str)
{
	t_vec3	vec3;
	char	**str_array;

	str_array = ft_split(str, ',');
	if (str_array == NULL)
		put_error_and_exit("Failed to split vector");
	if (count_array(str_array) != 3)
		put_error_and_exit("Invalid vector format");
	vec3.x = ft_atod(str_array[0]);
	vec3.y = ft_atod(str_array[1]);
	vec3.z = ft_atod(str_array[2]);
	if (check_range_vec3(vec3) == false)
		put_error_and_exit("Invalid vector range");
	free_split(str_array);
	return (vec3);
}

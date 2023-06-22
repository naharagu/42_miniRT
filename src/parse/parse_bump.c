/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_bump.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saikeda <saikeda@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 06:29:27 by saikeda           #+#    #+#             */
/*   Updated: 2023/06/23 07:06:15 by saikeda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "exit.h"
#include "libft.h"
#include "utils.h"
#include "shape.h"

static size_t	parse_bump_div(t_shape *shape, char **str_array, size_t index)
{
	int	num;

	if (str_array[index] == NULL)
		put_error_and_exit("Invalid bump_div format");
	num = ft_atoi(str_array[index]);
	if (num <= 0)
		put_error_and_exit("Invalid bump_div format");
	shape->bump_div = (size_t)num;
	if (shape->bump_div > LIMIT_DIVISION)
		put_error_and_exit("Invalid color_div");
	return (++index);
}

size_t	parse_bump(t_shape *shape, char **str_array, size_t index)
{
	shape->bump_map = NULL;
	if (str_array[index] == NULL)
	{
		shape->bump_flag = false;
		shape->bump_div = 0;
		return (index);
	}
	else if (ft_strcmp(str_array[index], "bump") == 0)
	{
		shape->bump_flag = true;
		return (parse_bump_div(shape, str_array, ++index));
	}
	return (index);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ACL.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharagu <naharagu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 08:47:34 by naharagu          #+#    #+#             */
/*   Updated: 2023/04/25 19:41:43 by naharagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "exit.h"
#include "libft.h"
#include "utils.h"
#include "test.h"

void	parse_ambient(char **str_array, t_scene *scene)
{
	if (scene->ambient_ratio != -1)
		put_error_and_exit("There are multiple ambient light");
	if (count_array(str_array) != 3)
		put_error_and_exit("Invalid ambient light format");
	scene->ambient_ratio = ft_atod(str_array[1]); //atoi -> atof
	if (is_in_range_double(scene->ambient_ratio, 0.0, 1.0) == false)
		put_error_and_exit("Invalid ambient ratio");
	scene->ambient_color = parse_color(str_array[2]);
}

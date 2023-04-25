/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ACL.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharagu <naharagu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 08:47:34 by naharagu          #+#    #+#             */
/*   Updated: 2023/04/25 19:53:47 by naharagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "exit.h"
#include "libft.h"
#include "utils.h"

void	parse_ambient(char **str_array, t_scene *scene)
{
	if (scene->ambient_ratio != -1)
		put_error_and_exit("There are multiple ambient light");
	if (count_array(str_array) != 3)
		put_error_and_exit("Invalid ambient light format");
	scene->ambient_ratio = ft_atod(str_array[1]); //atoi -> atof
	if (is_in_range_double(scene->ambient_ratio, 0.0, 1.0) == false)
		put_error_and_exit("Invalid ambient ratio");
	scene->ambient_color = parse_vec3(str_array[2]);
}

void	parse_camera(char **str_array, t_scene *scene)
{
	if (scene->camera.fov != -1)
		put_error_and_exit("There are multiple camera");
	if (count_array(str_array) != 4)
		put_error_and_exit("Invalid camera format");
	scene->camera.origin = parse_vec3(str_array[1]);
	scene->camera.direction = parse_vec3(str_array[2]);
	scene->camera.fov = ft_atod(str_array[3]);
	if (is_in_range_double(scene->camera.fov, 0.0, 180.0) == false)
		put_error_and_exit("Invalid camera fov");
}

// void	parse_light(char **str_array, t_scene *scene)
// {
// 	t_light	*light;

// 	if (count_array(str_array) != 4)
// 		put_error_and_exit("Invalid light format");
// 	light = (t_light *)malloc(sizeof(t_light));
// 	if (light == NULL)
// 		put_error_and_exit("Failed to malloc light");
// 	light->pos = parse_vector(str_array[1]);
// 	light->ratio = ft_atod(str_array[2]);
// 	if (is_in_range_double(light->ratio, 0.0, 1.0) == false)
// 		put_error_and_exit("Invalid light ratio");
// 	light->color = parse_color(str_array[3]);
// 	light->next = NULL;
// 	if (scene->light == NULL)
// 		scene->light = light;
// 	else
// 	{
// 		light->next = scene->light;
// 		scene->light = light;
// 	}
// }

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ACL.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saikeda <saikeda@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 08:47:34 by naharagu          #+#    #+#             */
/*   Updated: 2023/06/04 01:15:29 by saikeda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "exit.h"
#include "libft.h"
#include "utils.h"

void	parse_ambient(char **str_array, t_scene *scene)
{
	if (scene->ambient_ratio != -1)
		put_error_and_exit("There are multiple ambient lights");
	if (count_array(str_array) != 3)
		put_error_and_exit("Invalid ambient light format");
	scene->ambient_ratio = ft_atod(str_array[1]);
	if (is_in_range_double(scene->ambient_ratio, 0.0, 1.0) == false)
		put_error_and_exit("Invalid ambient ratio");
	scene->ambient_color = parse_color(str_array[2]);
}

void	parse_camera(char **str_array, t_scene *scene)
{
	if (scene->camera.fov != -1)
		put_error_and_exit("There are multiple cameras");
	if (count_array(str_array) != 4)
		put_error_and_exit("Invalid camera format");
	scene->camera.origin = parse_vec3(str_array[1]);
	scene->camera.dir = parse_vec3(str_array[2]);
	check_normalized(scene->camera.dir);
	scene->camera.fov = ft_atod(str_array[3]);
	if (is_in_range_double(scene->camera.fov, 0.0, 180.0) == false)
		put_error_and_exit("Invalid camera fov");
}

static t_light	*light_lst_last(t_light *lights)
{
	if (lights == NULL)
		return (NULL);
	while (lights->next)
		lights = lights->next;
	return (lights);
}

static t_light	*light_lst_add(t_scene *scene)
{
	t_light	*tmp;

	if (scene->lights == NULL)
	{
		scene->lights = malloc(sizeof(t_light));
		if (scene->lights == NULL)
			put_error_and_exit("Failed to malloc");
		scene->lights_num++;
		scene->lights->next = NULL;
		return (scene->lights);
	}
	else
	{
		tmp = light_lst_last(scene->lights);
		tmp->next = malloc(sizeof(t_light));
		if (tmp->next == NULL)
			put_error_and_exit("Failed to malloc");
		scene->lights_num++;
		tmp->next->next = NULL;
		return (tmp->next);
	}
}

void	parse_light(char **str_array, t_scene *scene)
{
	t_light	*light;

	if (count_array(str_array) != 4)
		put_error_and_exit("Invalid light format");
	light = light_lst_add(scene);
	light->origin = parse_vec3(str_array[1]);
	light->intensity = ft_atod(str_array[2]);
	light->color = parse_color(str_array[3]);
	if (is_in_range_double(light->intensity, 0.0, 1.0) == false)
		put_error_and_exit("Invalid light intensity");
}

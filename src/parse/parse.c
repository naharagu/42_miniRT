/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saikeda <saikeda@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 08:47:34 by naharagu          #+#    #+#             */
/*   Updated: 2023/06/04 01:15:17 by saikeda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "exit.h"
#include "libft.h"
#include "utils.h"

static void	convert_line_to_scene(char *line, t_scene *scene)
{
	char	**str_array;

	str_array = ft_split(line, ' ');
	errno = 0;
	if (str_array == NULL)
		put_error_and_exit("Failed to split line");
	if (ft_strcmp(str_array[0], "A") == 0)
		parse_ambient(str_array, scene);
	else if (ft_strcmp(str_array[0], "C") == 0)
		parse_camera(str_array, scene);
	else if (ft_strcmp(str_array[0], "L") == 0)
		parse_light(str_array, scene);
	else if (ft_strcmp(str_array[0], "sp") == 0)
		parse_sphere(str_array, scene);
	else if (ft_strcmp(str_array[0], "pl") == 0)
		parse_plane(str_array, scene);
	else if (ft_strcmp(str_array[0], "cy") == 0)
		parse_cylinder(str_array, scene);
	else if (ft_strcmp(str_array[0], "co") == 0)
		parse_cone(str_array, scene);
	else
		put_error_and_exit("Invalid content in rt file");
	if (errno != 0)
		put_error_and_exit("Failed to convert string to double");
	free_split(str_array);
}

static void	convert_argv_to_scene(char *argv, t_scene *scene)
{
	int		fd;
	char	*line;

	fd = open(argv, O_RDONLY);
	if (fd == -1)
		put_error_and_exit("Failed to open file");
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		else if (*line == '\n')
			;
		else
			convert_line_to_scene(line, scene);
		free(line);
	}
	if (close(fd) == -1)
		put_error_and_exit("Failed to close file");
}

static void	check_acl(t_scene	*scene)
{
	if (scene->ambient_ratio == -1)
		put_error_and_exit("There is no ambient light");
	if (scene->camera.fov == -1)
		put_error_and_exit("There is no camera");
	if (scene->lights_num == 0)
		put_error_and_exit("There is no light");
}

void	parse_rt_file(int argc, char **argv, t_scene *scene)
{
	if (argc != 2)
		put_error_and_exit("Usage: ./miniRT [.rt file]");
	validate_file_name(argv[1]);
	init_scene(scene);
	convert_argv_to_scene(argv[1], scene);
	check_acl(scene);
}

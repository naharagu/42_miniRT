/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharagu <naharagu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 08:47:34 by naharagu          #+#    #+#             */
/*   Updated: 2023/05/29 09:56:28 by naharagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "exit.h"
#include "libft.h"
#include "utils.h"
#include "test.h"

void	convert_line_to_scene(char *line, t_scene *scene)
{
	char	**str_array;

	str_array = ft_split(line, ' ');
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
	else
		put_error_and_exit("Invalid content in rt file");
	free_split(str_array);
}

void	convert_argv_to_scene(char *argv, t_scene *scene)
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

void	parse_rt_file(int argc, char **argv, t_scene *scene)
{
	if (argc != 2)
		put_error_and_exit("Usage: ./miniRT [.rt file]");
	validate_file_name(argv[1]);
	init_scene(scene);
	convert_argv_to_scene(argv[1], scene);
	print_t_scene(scene); //for test. delete later
	print_shape_lst(scene->shapes); //for test. delete later
}

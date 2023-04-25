/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharagu <naharagu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 08:47:34 by naharagu          #+#    #+#             */
/*   Updated: 2023/04/25 19:36:32 by naharagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "exit.h"
#include "libft.h"
#include "utils.h"
#include "test.h"

static void	validate_file_name(char *argv)
{
	if (ft_strlen(argv) < 4)
		put_rtfile_error_and_exit("Invalid file name");
	if (ft_strncmp(ft_strrchr(argv, '.'), ".rt", 3) != 0)
		put_rtfile_error_and_exit("Invalid file name");
}

void	free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

unsigned int	count_array(char **str_array)
{
	unsigned int	i;

	i = 0;
	while (str_array[i])
		i++;
	return (i);
}

t_color	parse_color(char *str)
{
	t_color	color;
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

void	convert_line_to_scene(char *line, t_scene *scene)
{
	char	**str_array;

	str_array = ft_split(line, ' ');
	if (str_array == NULL)
		put_error_and_exit("Failed to split line");
	if (ft_strcmp(str_array[0], "A") == 0)
		parse_ambient(str_array, scene);
	// else
	// 	put_error_and_exit("Invalid content in rt file");
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
	print_t_scene(scene); //delete later (for test)
}

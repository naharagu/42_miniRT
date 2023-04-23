/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharagu <naharagu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 08:47:34 by naharagu          #+#    #+#             */
/*   Updated: 2023/04/23 22:26:16 by naharagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "exit.h"
#include "libft.h"
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

// void	parse_ambient(char **str_array, t_scene *scene)
// {
// 	if (scene->ambient_ratio != -1)
// 		put_error_and_exit("There are multiple ambient light");
// 	scene->ambient_ratio = ft_atof(str_array[1]);
// 	if (scene->ambient_ratio < 0 || scene->ambient_ratio > 1)
// 		put_error_and_exit("Invalid ambient ratio");
// 	scene->ambient_color = parse_color(str_array[2]);
// }

void	convert_line_to_scene(char *line, t_scene *scene)
{
	char	**str_array;

	str_array = ft_split(line, ' ');
	if (str_array == NULL)
		put_error_and_exit("Failed to split line");
	(void) scene;
	// if (str_array[0] == "A")
	// 	parse_ambient(str_array, scene);
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

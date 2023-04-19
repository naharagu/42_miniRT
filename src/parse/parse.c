/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharagu <naharagu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 08:47:34 by naharagu          #+#    #+#             */
/*   Updated: 2023/04/19 23:08:56 by naharagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "scene.h"
#include "parse.h"
#include "exit.h"
#include "libft.h"
#include <fcntl.h>

void	init_world(t_world *world)
{
	world->mlx = mlx_init();
	world->mlx_win = mlx_new_window(world->mlx, WIDTH, HEIGHT, "miniRT");
	world->img = mlx_new_image(world->mlx, WIDTH, HEIGHT);
	world->addr = mlx_get_data_addr(world->img, &world->bits_per_pixel,
			&world->line_length, &world->endian);
}

// imgパラメータには、使用する画像を指定。
// mlx_get_data_addr() は、画像が保存されているメモリの開始点のアドレスを char * 型ポインタで返す。
// mlx_get_data_addr() が正常に呼び出された場合、次の3つのパラメータに値が指定。
//1. bits_per_pixel パラメータには、ピクセルの色を表現するために必要なビット数が入力。
//2. size_line パラメータには、画像1行を保存するために必要なバイト数が入力。
//3. endianパラメータは、ピクセルの色の保存方法が
//    little endian（0指定）かbig endian（1指定）かを示す（mlx_new_image manを参照）。

static void	validate_file_name(char *argv)
{
	if (ft_strlen(argv) < 4)
		put_error_and_exit("Invalid file name\n");
	if (ft_strncmp(ft_strrchr(argv, '.'), ".rt", 3) != 0)
		put_error_and_exit("Invalid file name\n");
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
// 	if (str_array[1] == NULL)
// 		put_error_and_exit("Invalid content in rt file\n");
// 	scene->ambient_ratio = ft_atof(str_array[1]);
// 	if (scene->ambient_ratio < 0 || scene->ambient_ratio > 1)
// 		put_error_and_exit("Invalid content in rt file\n");
// 	scene->ambient_color = parse_color(str_array[2]);
// }

void	convert_line_to_scene(char *line, t_scene *scene)
{
	char	**str_array;


	str_array = ft_split(line, ' ');
	if (str_array == NULL)
		put_error_and_exit("Failed to split line\n");
	(void) scene;
	// if (str_array[0] == "A")
	// 	parse_ambient(str_array, scene);
	// else
	// 	put_error_and_exit("Invalid content in rt file\n");
	free_split(str_array);
}

void	validate_and_init_scene(char *argv, t_scene *scene)
{
	int		fd;
	char	*line;

	fd = open(argv, O_RDONLY);
	if (fd == -1)
		put_error_and_exit("Failed to open file\n");
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
		put_error_and_exit("Failed to close file\n");
}

void	parse_rt_file(int argc, char **argv, t_world *world, t_scene *scene)
{
	if (argc != 2)
		put_error_and_exit("Usage: ./miniRT [.rt file]\n");
	validate_file_name(argv[1]);
	// validate_and_init_scene(argv[1], scene);
	init_world(world);
	init_scene(scene);
}

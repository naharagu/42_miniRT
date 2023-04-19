/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharagu <naharagu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 21:34:41 by naharagu          #+#    #+#             */
/*   Updated: 2023/04/19 23:18:03 by naharagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "shape.h"
#include "vector.h"
#include "libft.h"
#include <stdlib.h>

void	init_scene(t_scene *scene)
{
	scene->ambient_color = (t_color){255, 255, 255};
	scene->ambient_ratio = 0.001;
	scene->camera.origin = (t_vec3){0, 0, -5};
	scene->light.origin = (t_vec3){-5, 5, -5};
	scene->shapes = ft_calloc(1, sizeof(t_shape));
	if (!scene->shapes)
		exit(1);
	init_shape(scene->shapes);
}

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

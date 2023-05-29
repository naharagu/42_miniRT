/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saikeda <saikeda@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 21:34:41 by naharagu          #+#    #+#             */
/*   Updated: 2023/05/28 21:52:16 by saikeda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "shape.h"
#include "vector.h"
#include "libft.h"

void	init_scene(t_scene *scene)
{
	scene->ambient_ratio = -1;
	scene->ambient_color = (t_color){-1, -1, -1};
	scene->camera.origin = (t_vec3){-1, -1, -1};
	scene->camera.dir = (t_vec3){-1, -1, -1};
	scene->camera.fov = -1;
	scene->light.origin = (t_vec3){-5, 5, -5};
	scene->light.intensity = -1;
	scene->shapes = NULL;
}

void	init_window(t_window *window)
{
	window->mlx = mlx_init();
	window->mlx_win = mlx_new_window(window->mlx, WIDTH, HEIGHT, "miniRT");
	window->img = mlx_new_image(window->mlx, WIDTH, HEIGHT);
	window->addr = mlx_get_data_addr(window->img, &window->bits_per_pixel,
			&window->line_length, &window->endian);
}

// imgパラメータには、使用する画像を指定。
// mlx_get_data_addr() は、画像が保存されているメモリの開始点のアドレスを char * 型ポインタで返す。
// mlx_get_data_addr() が正常に呼び出された場合、次の3つのパラメータに値が指定。
//1. bits_per_pixel パラメータには、ピクセルの色を表現するために必要なビット数が入力。
//2. size_line パラメータには、画像1行を保存するために必要なバイト数が入力。
//3. endianパラメータは、ピクセルの色の保存方法が
//    little endian（0指定）かbig endian（1指定）かを示す（mlx_new_image manを参照）。

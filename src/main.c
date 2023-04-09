/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharagu <naharagu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 10:14:07 by naharagu          #+#    #+#             */
/*   Updated: 2023/04/09 21:46:40 by naharagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "mlx.h"
#include "color.h"
#include <math.h>
#include "libft.h"

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

int	key_handler(int key, t_world *world)
{
	dprintf(STDERR_FILENO, "key: %d\n", key);//
	if (key == ESC)
		mlx_loop_end(world->mlx);
	return (0);
}

int	main(void)
{
	t_world	world;
	t_scene scene;

	init_world(&world);
	init_scene(&scene);
	mini_rt(&world, &scene);
	mlx_put_image_to_window(world.mlx, world.mlx_win, world.img, 0, 0);
	mlx_key_hook(world.mlx_win, key_handler, &world);
	mlx_loop(world.mlx);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharagu <naharagu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 10:14:07 by naharagu          #+#    #+#             */
/*   Updated: 2023/04/08 10:37:01 by naharagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "mlx.h"
#include <math.h>

void	init_world(t_world *world)
{
	world->mlx = mlx_init();
	world->mlx_win = mlx_new_window(world->mlx, WIDTH, HEIGHT, "miniRT");
	world->img = mlx_new_image(world->mlx, WIDTH, HEIGHT);
	world->addr = mlx_get_data_addr(world->img, &world->bits_per_pixel,
			&world->line_length, &world->endian);
	world->camera = (t_vec3){0, 0, -5};
	world->light = (t_vec3){-5, 5, -5};
	world->object = (t_vec3){0, 0, 5};
}

int	main(void)
{
	t_world	world;

	init_world(&world);
	mini_rt(&world);
	mlx_put_image_to_window(world.mlx, world.mlx_win, world.img, 0, 0);
	mlx_loop(world.mlx);
	return (0);
}

	// draw_square(&world, 0, 0, 0x00FF0000);
// imgパラメータには、使用する画像を指定。
// mlx_get_data_addr() は、画像が保存されているメモリの開始点のアドレスを char * 型ポインタで返す。
// mlx_get_data_addr() が正常に呼び出された場合、次の3つのパラメータに値が指定。
//- bits_per_pixel パラメータには、ピクセルの色を表現するために必要なビット数が入力。
//- size_line パラメータには、画像1行を保存するために必要なバイト数が入力。
//- endianパラメータは、ピクセルの色の保存方法が
//    little endian（0指定）かbig endian（1指定）かを示す（mlx_new_image manを参照）。

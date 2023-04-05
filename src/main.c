#include "miniRT.h"
#include <math.h>

void	put_pixel_to_addr(t_world *world, int x, int y, int color)
{
	char	*dst;

	dst = world->addr
		+ (y * world->line_length + x * (world->bits_per_pixel/ 8));
	*(unsigned int *)dst = color;
}

// dstに代入されるアドレスは、画像データの先頭アドレスから、y座標のラインのバイト数とx座標に対応するバイト数を加算したアドレス
// このアドレスに対して、カラー値を書き込むことで、指定された座標にカラーのピクセルを描画

void	draw_world(t_world *world)
{
	int		x;
	int		y;
	t_color	color;

	x = 0;
	while (x < WIDTH)
	{
		y = 0;
		while (y < HEIGHT)
		{
			color = miniRT(world, x, y);
			put_pixel_to_addr(world, x, HEIGHT - y - 1, get_color_in_int(color));
			y++;
		}
		x++;
	}
}

void init_world(t_world *world)
{
	world->mlx = mlx_init();
	world->mlx_win = mlx_new_window(world->mlx, WIDTH, HEIGHT, "miniRT");
	world->img = mlx_new_image(world->mlx, WIDTH, HEIGHT);
	world->addr = mlx_get_data_addr(world->img, &world->bits_per_pixel,
			&world->line_length, &world->endian);
}

int	main(void)
{
	t_world	world;

	init_world(&world);
	// draw_square(&world, 0, 0, 0x00FF0000);
	draw_world(&world);
	mlx_put_image_to_window(world.mlx, world.mlx_win, world.img, 0, 0);
	mlx_loop(world.mlx);
	return (0);
}

// imgパラメータには、使用する画像を指定。
// mlx_get_data_addr() は、画像が保存されているメモリの開始点のアドレスを char * 型ポインタで返す。
// mlx_get_data_addr() が正常に呼び出された場合、次の3つのパラメータに値が指定。
//- bits_per_pixel パラメータには、ピクセルの色を表現するために必要なビット数が入力。
//- size_line パラメータには、画像1行を保存するために必要なバイト数が入力。
//- endianパラメータは、ピクセルの色の保存方法が
//    little endian（0指定）かbig endian（1指定）かを示す（mlx_new_image manを参照）。

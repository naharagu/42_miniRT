#include "miniRT.h"

void	put_pixel_to_addr(t_world *world, int x, int y, int color)
{
	char	*dst;

	dst = world->addr + (y * world->line_length + x * (world->bits_per_pixel
				/ 8));
	*(unsigned int *)dst = color;
	return ;
}

// dstに代入されるアドレスは、画像データの先頭アドレスから、y座標のラインのバイト数とx座標に対応するバイト数を加算したアドレス
// このアドレスに対して、カラー値を書き込むことで、指定された座標にカラーのピクセルを描画

void	draw_square(t_world *world, int x_start, int y_start, int color)
{
	int		x_current;
	int		y_current;
	double	r;
	double	g;
	double	b;

	x_current = x_start;
	while (x_current < x_start + 400)
	{
		y_current = y_start;
		while (y_current < y_start + 400)
		{
			r = (double)(400 - x_current) / 400.0 * 255.0;
			g = (double)(y_current - y_start) / 400.0 * 255.0;
			b = 0.0;
			color = get_color_in_int((t_color){r, g, b});
			put_pixel_to_addr(world, x_current, y_current, color);
			y_current++;
		}
		x_current++;
	}
	return ;
}

void	draw_sphere(t_world *world, int x_start, int y_start, int color)
{
	int		x;
	int		y;
	double sphere_r;

	t_vec3	camera;
	camera = (t_vec3){0, 0, -100};
	// t_vec3	sphere;
	// sphere = (t_vec3){0, 0, 5};

	t_vec3	light;
	light = (t_vec3){-5, 5, 5};

	sphere_r = 0.5;
	x = x_start;
	while (x < x_start + world->screen_width)
	{
		y = y_start;
		while (y < y_start + world->screen_height)
		{
			t_vec3 screen;
			screen = (t_vec3){(double) 2 * x / (double)world->screen_width - 1.0,
				(double)2 * y / (double)world->screen_height - 1.0, 0};
			t_vec3 ray;
			ray = vec3_normalize(vec3_subtraction(screen, camera));

			double a = vec3_magnitude(ray) * vec3_magnitude(ray);
			double b = 2.0 * vec3_dot_product(camera, ray);
			double c = vec3_magnitude(camera) * vec3_magnitude(camera) - sphere_r * sphere_r;

			double discriminant = b * b - 4.0 * a * c;
			if (discriminant >= 0.0)
				put_pixel_to_addr(world, x, y, color);
			else
				put_pixel_to_addr(world, x, y, get_color_in_int((t_color){100, 149, 237}));
			y++;
		}
		x++;
	}
	return ;
}

void init_world(t_world *world)
{
	world->screen_height = 400;
	world->screen_width = 400;
	world->mlx = mlx_init();
	world->mlx_win = mlx_new_window(world->mlx,
			world->screen_width, world->screen_height, "miniRT");
	world->img = mlx_new_image(world->mlx,
			world->screen_width, world->screen_height);
	world->addr = mlx_get_data_addr(world->img, &world->bits_per_pixel,
			&world->line_length, &world->endian);
	return ;
}

int	main(void)
{
	t_world	world;

	init_world(&world);
	// draw_square(&world, 0, 0, 0x00FF0000);
	draw_sphere(&world, 0, 0, 0x00FF0000);
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

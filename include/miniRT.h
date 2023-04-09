#ifndef MINIRT_H
# define MINIRT_H

#include <stdio.h>//
#include "vector.h"
#include "scene.h"

#define HEIGHT 400
#define	WIDTH 400

typedef struct s_world
{
	void	*mlx;
	void	*mlx_win;
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}			t_world;

void	mini_rt(t_world *world, t_scene *scene);
void	put_pixel_to_addr(t_world *world, int x, int y, int color);

#endif
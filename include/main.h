#ifndef MAIN_H
# define MAIN_H

#include <stdio.h>//
#include "vector.h"
#include "scene.h"
#include "mlx.h"

#define HEIGHT 400
#define	WIDTH 400
#define ESC 65307

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


#endif
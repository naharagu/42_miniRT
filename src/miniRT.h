#ifndef MINIRT_H
# define MINIRT_H

# include "../libft/libft.h"
# include "../minilibx/mlx.h"
# include "vector/vector.h"
# include <stdio.h>

typedef struct s_world
{
	void	*mlx;
	void	*mlx_win;
	unsigned int screen_width;
	unsigned int screen_height;
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}			t_world;

#endif
#ifndef MAIN_H
# define MAIN_H

#include <stdio.h> //delete later
#include "vector.h"
#include "mlx.h"

#define HEIGHT 400
#define	WIDTH 400
#define ESC 65307

typedef struct s_window
{
	void	*mlx;
	void	*mlx_win;
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}			t_window;

#endif

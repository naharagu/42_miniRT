#ifndef MINIRT_H
# define MINIRT_H

# include <../libft/libft.h>
# include <../minilibx/mlx.h>
# include <stdio.h>

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

typedef struct s_vec3 t_color;
struct		s_vec3
{
	double	x;
	double	y;
	double	z;
};

#endif
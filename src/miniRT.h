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
	int screen_width;
	int screen_height;
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	t_list	*camera;
	t_list	*lights;
	t_list	*objects;
	t_vec3	ambient_light;
}			t_world;

typedef struct s_camera
{
	t_vec3	origin;
	t_vec3	orientation;
	double	fov;
}			t_camera;

#endif
#ifndef MINIRT_H
# define MINIRT_H

# include "../libft/libft.h"
# include "../minilibx/mlx.h"
# include "vector/vector.h"

#include <stdio.h>//

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

typedef struct s_light
{
	t_vec3	origin;
	double	ratio;
	t_vec3	color;
}			t_light;

//環境光の環境反射(Ambient)
// 直接光の拡散反射(Diffuse)
// 直接光の鏡面反射(Specular)

t_color miniRT(t_world *world, double x, double y);
void	put_pixel_to_addr(t_world *world, int x, int y, int color);

#endif
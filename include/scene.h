#ifndef	SCENE_H
# define SCENE_H

# include "vector.h"
# include "color.h"
# include "shape.h"

typedef struct s_camera
{
	t_vec3	origin;
	t_vec3	orientation;
	double	fov;
}			t_camera;

typedef struct s_hit
{
	t_vec3	point;
	t_vec3	normal;
	t_vec3	color;
}			t_hit;

typedef struct s_scene
{
	t_color	ambient_color;
	double	ambient_ratio;
	t_vec3	camera;
	t_vec3	light;
	t_vec3	light_dir;
	t_vec3	object;
	t_shape *shapes;
	t_hit	hit;
}			t_scene;

#endif
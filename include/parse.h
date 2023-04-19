#ifndef PARSE_H
# define PARSE_H

#include "main.h"
#include "shape.h"
#include "color.h"
typedef struct s_camera
{
	t_vec3	origin;
	t_vec3	direction;
	double	fov;
}			t_camera;

typedef struct s_light
{
	t_vec3	origin;
	t_vec3	direction;
	double	intensity;
}			t_light;

typedef struct s_hit
{
	t_vec3	point;
	t_vec3	normal;
	t_vec3	color;
}			t_hit;

typedef struct s_scene
{
	t_color		ambient_color;
	double		ambient_ratio;
	t_camera	camera;
	t_light		light;
	t_shape 	*shapes;
	t_hit		hit;
}			t_scene;

void	init_scene(t_scene *scene);
void	init_world(t_world *world);
void	parse_rt_file(int argc, char **argv, t_world *world, t_scene *scene);

#endif

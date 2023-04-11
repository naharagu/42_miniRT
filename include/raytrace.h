#ifndef RAYTRACE_H
# define RAYTRACE_H

#include "color.h"
#include "scene.h"
#include "vector.h"

#define LIGHT_INTENSITY 1
#define K_DIFFUSE 0.69
#define K_SPECULAR 0.3
#define ALPHA 2

typedef struct s_ray
{
	t_vec3	origin;
	t_vec3	direction;
}			t_ray;

t_color	shading(t_scene *scene, t_vec3 ray);

#endif
#ifndef RAYTRACE_H
# define RAYTRACE_H

#include "color.h"
#include "scene.h"
#include "vector.h"

t_color	shading(t_scene *scene, t_vec3 ray);

#endif
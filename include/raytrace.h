#ifndef RAYTRACE_H
# define RAYTRACE_H

#include "miniRT.h"
#include "color.h"

t_color	shading(t_world *world, t_vec3 ray);

#endif
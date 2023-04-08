#ifndef RAYTRACE_H
# define RAYTRACE_H

#include "miniRT.h"
#include "color.h"

double	calculate_ambient_light(void);
double calculate_diffuse_reflection(t_world *world, t_vec3 ray);

#endif
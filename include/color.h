#ifndef COLOR_H
# define COLOR_H

#include "vector.h"

typedef struct s_vec3 t_color;

void	set_color(double r, double g, double b, t_color *color);
int		get_color_in_int(t_color color);

#endif
#ifndef VECTOR_H
# define VECTOR_H

typedef struct s_vec3 t_color;
struct		s_vec3
{
	double	x;
	double	y;
	double	z;
};

void		set_color(double r, double g, double b, t_color *color);
int			get_color_in_int(t_color color);

#endif
#ifndef COLOR_H
# define COLOR_H

typedef struct s_color t_color;
struct s_color
{
	double r;
	double g;
	double b;
};

void		set_color(double r, double g, double b, t_color *color);
int			get_color_in_int(t_color color);

#endif
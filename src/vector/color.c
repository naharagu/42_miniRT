#include "color.h"

void	set_color(double r, double g, double b, t_color *color)
{
	color->r = r;
	color->g = g;
	color->b = b;
	return ;
}

int	get_color_in_int(t_color color)
{
	int	r;
	int	g;
	int	b;

	r = (int)(color.r);
	g = (int)(color.g);
	b = (int)(color.b);
	return ((r << 16) + (g << 8) + b);
}

#include "vector.h"

void	set_color(double r, double g, double b, t_color *color)
{
	color->x = r;
	color->y = g;
	color->z = b;
	return ;
}

int	get_color_in_int(t_color color)
{
	int	r;
	int	g;
	int	b;

	r = (int)(color.x);
	g = (int)(color.y);
	b = (int)(color.z);
	return ((r << 16) + (g << 8) + b);
}

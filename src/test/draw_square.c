#include "miniRT.h"
#include "test.h"
#include "color.h"

void	draw_square(t_world *world, int x_start, int y_start, int color)
{
	int		x_current;
	int		y_current;
	double	r;
	double	g;
	double	b;

	x_current = x_start;
	while (x_current < x_start + 400)
	{
		y_current = y_start;
		while (y_current < y_start + 400)
		{
			r = (double)(400 - x_current) / 400.0 * 255.0;
			g = (double)(y_current - y_start) / 400.0 * 255.0;
			b = 0.0;
			color = get_color_in_int((t_color){r, g, b});
			put_pixel_to_addr(world, x_current, y_current, color);
			y_current++;
		}
		x_current++;
	}
	return ;
}
#include "miniRT.h"
#include "raytrace.h"
#include <math.h>

t_vec3 get_ray(t_world *world, double x, double y)
{
	t_vec3 camera = world->camera;
	t_vec3 screen;

	screen = (t_vec3){(double) 2 * x / (double)WIDTH - 1.0,
		(double)2 * y / (double)HEIGHT - 1.0, 0};
	return (vec3_normalize(vec3_subtraction(screen, camera)));
}

t_color	shading(t_world *world, t_vec3 ray)
{
	double R_r;

	R_r = calculate_ambient_light();
	R_r += calculate_diffuse_reflection(world, ray);

	return (t_color){255 * R_r, 255 * R_r, 255 * R_r};
}

void	miniRT(t_world *world)
{
	int		x;
	int		y;
	t_vec3	ray;
	t_color color;

	x = 0;
	while (x < WIDTH)
	{
		y = 0;
		while (y < HEIGHT)
		{
			ray = get_ray(world, x, y);
			color = shading(world, ray);
			put_pixel_to_addr(world, x, HEIGHT - y - 1, get_color_in_int(color));
			y++;
		}
		x++;
	}
}
//shading = 1) diffuse_reflection + 2) specular_reflection + 3) ambient_reflection
//shadowing = 1) shadow + 2) reflection + 3) refraction

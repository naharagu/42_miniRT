#include "miniRT.h"
#include "raytrace.h"
#include <math.h>

static t_vec3 get_ray(t_world *world, double x, double y)
{
	t_vec3 camera = world->camera;
	t_vec3 screen;

	screen = (t_vec3){(double) 2 * x / (double)WIDTH - 1.0,
		(double)2 * y / (double)HEIGHT - 1.0, 0};
	return (vec3_normalize(vec3_subtraction(screen, camera)));
}

static int	calculate_hit_point(t_world *world, t_vec3 *ray)
{
	t_vec3	camera = world->camera;
	t_vec3	light = world->light;
	t_vec3	sphere = world->object;
	double	sphere_r = 0.7;

	double a = vec3_magnitude(*ray) * vec3_magnitude(*ray);
	double b = 2.0 * vec3_dot_product(camera, *ray);
	double c = vec3_magnitude(camera) * vec3_magnitude(camera) - sphere_r * sphere_r;

	double discriminant = b * b - 4.0 * a * c;
	if (discriminant < 0.0)
		return (-1);
	double t = (-b + sqrt(discriminant)) / (2.0 * a);
	if (discriminant > 0.0)
	{
		double t2 = (-b - sqrt(discriminant)) / (2.0 * a);
		if (t2 < t)
			t = t2;
	}
	world->hit.point = vec3_addition(camera, vec3_multiply_scalar(*ray, t));
	world->hit.normal = vec3_normalize(vec3_subtraction(world->hit.point, sphere));
	world->light_dir = vec3_normalize(vec3_subtraction(light, world->hit.point));
	return (0);
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
			if (calculate_hit_point(world, &ray) == -1)
				color = ((t_color){100, 149, 237});
			else
			{
				color = shading(world, ray);
				// color += shadowing;
			}
			put_pixel_to_addr(world, x, HEIGHT - y - 1, get_color_in_int(color));
			y++;
		}
		x++;
	}
}
//shading = 1) diffuse_reflection + 2) specular_reflection + 3) ambient_reflection
//shadowing = 1) shadow + 2) reflection + 3) refraction

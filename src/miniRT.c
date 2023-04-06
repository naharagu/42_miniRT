#include "miniRT.h"
#include <math.h>

t_vec3 get_ray(t_world *world, double x, double y)
{
	t_vec3 camera = world->camera;
	t_vec3 screen;

	screen = (t_vec3){(double) 2 * x / (double)WIDTH - 1.0,
		(double)2 * y / (double)HEIGHT - 1.0, 0};
	return (vec3_normalize(vec3_subtraction(screen, camera)));
}

t_color calculate_diffuse_reflection(t_world *world, t_vec3 ray)
{
	t_vec3	camera = world->camera;
	t_vec3	light = world->light;
	t_vec3	sphere = world->object;
	double	sphere_r = 0.7;

	double a = vec3_magnitude(ray) * vec3_magnitude(ray);
	double b = 2.0 * vec3_dot_product(camera, ray);
	double c = vec3_magnitude(camera) * vec3_magnitude(camera) - sphere_r * sphere_r;

	double discriminant = b * b - 4.0 * a * c;
	if (discriminant < 0.0)
		return ((t_color){100, 149, 237});
	double t = (-b + sqrt(discriminant)) / (2.0 * a);
	if (discriminant > 0.0)
	{
		double t2 = (-b - sqrt(discriminant)) / (2.0 * a);
		if (t2 < t)
			t = t2;
	}
	t_vec3 hit_point = vec3_addition(camera, vec3_multiply_scalar(ray, t));
	t_vec3 normal = vec3_normalize(vec3_subtraction(hit_point, sphere));
	t_vec3 light_dir = vec3_normalize(vec3_subtraction(light, hit_point));
	double diffuse = vec3_dot_product(light_dir, normal);
	if (diffuse < 0.0)
		diffuse = 0.0;

	double I_i = 1.0;
	double k_d = 0.69;
	double R_d = k_d * I_i * diffuse;

	double I_a = 0.1;
	double k_a = 0.01;
	double R_a = k_a * I_a;

	double k_s = 0.3;
	double alpha = 8;
	t_vec3 v = vec3_multiply_scalar(ray, -1);
	t_vec3 r = vec3_subtraction(vec3_multiply_scalar(vec3_multiply_scalar(normal, vec3_dot_product(normal, light_dir)), 2), normal);
	double R_s = k_s * I_i * pow(vec3_dot_product(v, r), alpha);
	if (vec3_dot_product(v, r) < 0)
		R_s = 0;

	double R_r = R_a + R_d + R_s;
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
			color = calculate_diffuse_reflection(world, ray);
			put_pixel_to_addr(world, x, HEIGHT - y - 1, get_color_in_int(color));
			y++;
		}
		x++;
	}
}
#include "raytrace.h"
#include "vector.h"
#include <math.h>

double	calculate_ambient_light(void)
{
	double	k_a;
	double	I_a;
	double	R_a;

	k_a = 0.01;
	I_a = 0.1;
	R_a = k_a * I_a;
	return (R_a);
}

double calculate_diffuse_reflection(t_world *world)
{
	double diffuse = vec3_dot_product(world->light_dir, world->hit.normal);
	if (diffuse < 0.0)
		diffuse = 0.0;

	double I_i = 1.0;
	double k_d = 0.69;
	double R_d = k_d * I_i * diffuse;

	return  R_d;
}

double calculate_specular_reflection(t_world * world, t_vec3 ray)
{
	double R_s;
	t_vec3 normal = world->hit.normal;
	t_vec3 light_dir = world->light_dir;

	double I_i = 1.0;
	double k_s = 0.3;
	double alpha = 8;
	t_vec3 v = vec3_multiply_scalar(ray, -1);
	t_vec3 r = vec3_subtraction(vec3_multiply_scalar(vec3_multiply_scalar(normal, vec3_dot_product(normal, light_dir)), 2), normal);
	R_s = k_s * I_i * pow(vec3_dot_product(v, r), alpha);
	if (vec3_dot_product(v, r) < 0)
		R_s = 0;
	return (R_s);
}

t_color	shading(t_world *world, t_vec3 ray)
{
	double R_a;
	double R_d;
	double R_s;
	double R_r;

	R_a = calculate_ambient_light();
	R_d = calculate_diffuse_reflection(world);
	R_s = calculate_specular_reflection(world, ray);
	R_r = R_a + R_d + R_s;
	return (t_color){255 * R_r, 255 * R_r, 255 * R_r};
}

// 環境光の環境反射(Ambient)
// 直接光の拡散反射(Diffuse)
// 直接光の鏡面反射(Specular)
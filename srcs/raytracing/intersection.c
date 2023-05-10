/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takira <takira@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 12:28:12 by takira            #+#    #+#             */
/*   Updated: 2023/04/11 19:16:32 by takira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	intersection_with_cylinder(t_shape *shape, const t_ray *ray,
										 t_intersection_point *out_intp)
{
	t_cylinder	*cyl;
	float		A, B, C, D;
	float		t1, t2;
	t_vector	pe_pc, pipc_n;
	t_vector	d_x_n;
	t_vector	pepc_x_n;
	t_vector	t1d, t2d;
	t_vector	pos1, pos2;
	t_vector	p1_pc, p2_pc;

	cyl = &shape->data.cylinder;
	pe_pc = sub(&ray->start, &cyl->position);

	d_x_n = cross(&ray->direction, &cyl->normal);
	pepc_x_n = cross(&pe_pc, &cyl->normal);
	A = SQR(norm(&d_x_n));
	B = 2.0f * dot(&d_x_n, &pepc_x_n);
	C = SQR(norm(&pepc_x_n)) - SQR(cyl->radius);

	D = SQR(B) - 4.0f * A * C;

	if (A == 0.0f || D < 0.0f)
		return (0);

	t1 = (float) (-B - sqrtf(D)) / (2.0f * A);
	t2 = (float) (-B + sqrtf(D)) / (2.0f * A);

	if (!out_intp)
		return (0);

	t1d = mult(t1, &ray->direction);
	pos1 = add(&ray->start, &t1d);
	p1_pc = sub(&pos1, &cyl->position);

	if (0.0f < t1 && 0.0f <= dot(&p1_pc, &cyl->normal) && dot(&p1_pc, &cyl->normal) <= cyl->height)
	{
		out_intp->distance = t1;
		out_intp->position = pos1;
		pipc_n = mult(dot(&p1_pc, &cyl->normal), &cyl->normal);
		out_intp->normal = sub(&p1_pc, &pipc_n);
		normalize(&out_intp->normal);
		return (1);
	}

	t2d = mult(t2, &ray->direction);
	pos2 = add(&ray->start, &t2d);
	p2_pc = sub(&pos2, &cyl->position);
	if (0.0f < t2 && 0.0f <= dot(&p2_pc, &cyl->normal) && dot(&p2_pc, &cyl->normal) <= cyl->height)
	{
		out_intp->distance = t2;
		out_intp->position = pos2;
		pipc_n = mult(dot(&p2_pc, &cyl->normal), &cyl->normal);
		out_intp->normal = sub(&p2_pc, &pipc_n);
		out_intp->normal = normalize_vec_inv(&out_intp->normal);
		return (1);
	}
	return (0);
}

static int	intersection_with_corn(const t_shape *shape, const t_ray *ray,
									 t_intersection_point *out_intp)
{
	const t_corn	*corn = &shape->data.corn;
	t_vector		di = ray->direction;
	t_vector		pe = ray->start;
	float			A, B, C, D;
	float			r = corn->radius;
	float			h = corn->height;
	t_vector		pc = corn->origin;
	t_vector		n = corn->normal;
	t_vector		d = normalize_vec_inv(&n);

	t_vector		cross_d_n = cross(&di, &n);
	float			dot_d_n = dot(&di, &n);
	t_vector		sub_pe_pc = sub(&pe, &pc);
	t_vector		cross_pepc_n = cross(&sub_pe_pc, &n);
	float			dot_pepc_n = dot(&sub_pe_pc, &n);

	float			t1, t2;
	t_vector		t1d, t2d;
	t_vector		pos1, pos2;

	float			alpha;
	t_vector		l;

	A = squared_norm(&cross_d_n) - SQR(r / h) * SQR(dot_d_n);
	B = 2.0f * dot(&cross_d_n, &cross_pepc_n) - 2.0f * SQR(r / h) * dot_d_n * dot_pepc_n;
	C = squared_norm(&cross_pepc_n) - SQR(r / h) * SQR(dot_pepc_n);

	D = SQR(B) - 4.0f * A * C;

	if (A == 0.0f || D < 0.0f || !out_intp)
		return (0);

	t1 = (float) (-B - sqrtf(D)) / (2.0f * A);
	t2 = (float) (-B + sqrtf(D)) / (2.0f * A);

	alpha = atanf(r / h);

	t1d = mult(t1, &di);
	pos1 = add(&pe, &t1d);
	t_vector	p1_pc = sub(&pos1, &pc);
	t_vector	h1 = mult(dot(&p1_pc, &n), &n);
	t_vector	l1 = sub(&p1_pc, &h1);
	normalize(&l1);

	l = normalize_vec(&p1_pc);

	if (0.0f < t1 && -h <= dot(&p1_pc, &n) && dot(&p1_pc, &n) <= 0.0f)
	{
		out_intp->distance = t1;
		out_intp->position = pos1;
		out_intp->normal = vec_calc(norm(&d) * cosf(alpha), &l, -1.0f, &d);

		normalize(&out_intp->normal);
		return (1);
	}

	t2d = mult(t2, &di);
	pos2 = add(&pe, &t2d);
	t_vector	p2_pc = sub(&pos2, &pc);
	t_vector	h2 = mult(dot(&p2_pc, &n), &n);
	t_vector	l2 = sub(&p2_pc, &h2);
	normalize(&l2);

	l = normalize_vec(&p2_pc);

	if (0.0f < t2 && -h <= dot(&p2_pc, &n) && dot(&p2_pc, &n) <= 0.0f)
	{
		out_intp->distance = t2;
		out_intp->position = pos2;
		out_intp->normal = vec_calc(norm(&d) * cosf(alpha), &l, -1.0f, &d);

		out_intp->normal = normalize_vec_inv(&out_intp->normal);
		return (1);
	}
	return (0);
}

static int	intersection_with_sphere(const t_shape *shape, const t_ray *ray,
									   t_intersection_point *out_intp)
{
	const t_sphere	*sph = &shape->data.sphere;
	t_vector		pe_pc;
	float			A, B, C, D;
	float			t;
	t_vector		td;

	pe_pc = sub(&ray->start, &sph->center);
	A = dot(&ray->direction, &ray->direction);
	B = 2.0f * dot(&ray->direction, &pe_pc);
	C = dot(&pe_pc, &pe_pc) - SQR(sph->radius);

	D = SQR(B) - 4.0f * A * C;

	if (A == 0.0f)
		return (0);
	t = -1.0f;
	if (D == 0.0f)
		t = -B / (2.0f * A);
	else if (D > 0.0f)
	{
		float t1 = (float) (-B + sqrtf(D)) / (2.0f * A);
		float t2 = (float) (-B - sqrtf(D)) / (2.0f * A);
		if (t1 > 0.0f)
			t = t1;
		if (t2 > 0.0f && t2 < t)
			t = t2;
	}

	if (t <= 0.0f || !out_intp)
		return (0);

	out_intp->distance = t;
	td = mult(t, &ray->direction);
	out_intp->position = add(&ray->start, &td);
	out_intp->normal = sub(&out_intp->position, &sph->center);
	normalize(&out_intp->normal);
	return (1);
}

static int	intersection_with_plane(const t_shape *shape, const t_ray *ray,
									  t_intersection_point *out_intp)
{
	const t_plane	*pln = &shape->data.plane;
	float 			dn_dot = dot(&ray->direction, &pln->normal);
	t_vector		s_p;
	float			t;
	t_vector		td, inv_eye_dir;

	if (dn_dot == 0.0f)
		return (0);

	s_p = sub(&ray->start, &pln->position);

	t = -1.0f * dot(&s_p, &pln->normal) / dn_dot;

	if (t <= 0.0f || !out_intp)
		return (0);

	out_intp->distance = t;
	td = mult(t, &ray->direction);
	out_intp->position = add(&ray->start, &td);
	out_intp->normal = pln->normal;

	inv_eye_dir = normalize_vec_inv(&ray->direction);
	if (dot(&pln->normal, &inv_eye_dir) < 0)
		out_intp->normal = normalize_vec_inv(&pln->normal);

	return (1);
}

int intersection_test(t_shape *shape, const t_ray *ray,
					  t_intersection_point *out_intp)
{
	if (shape->type == ST_PLANE)
		return (intersection_with_plane(shape, ray, out_intp));
	if (shape->type == ST_SPHERE)
		return (intersection_with_sphere(shape, ray, out_intp));
	if (shape->type == ST_CYLINDER)
		return (intersection_with_cylinder(shape, ray, out_intp));
	if (shape->type == ST_CORN)
		return (intersection_with_corn(shape, ray, out_intp));
	return (0);
}

int get_nearest_shape(const t_scene *scene, const t_ray *ray,
					  float max_dist, int exit_once_found,
					  t_shape **out_shape, t_intersection_point *out_intp)
{
	t_shape					*nearest_shape = NULL;
	t_intersection_point	nearest_intp;
	t_intersection_point	intp;
	int						res;
	t_list 					*obj_node;

	nearest_intp.distance = max_dist;

	obj_node = scene->shape_list;
	while (obj_node)
	{
		res = intersection_test(obj_node->content, ray, &intp);

		if (res && intp.distance < nearest_intp.distance)
		{
			nearest_shape = obj_node->content;
			nearest_intp = intp;
			if (exit_once_found)
				break;
		}
		obj_node = obj_node->next;
	}

	if (!nearest_shape)
		return (0);
	if (out_shape)
		*out_shape = nearest_shape;
	if (out_intp)
		*out_intp = nearest_intp;
	return (1);
}

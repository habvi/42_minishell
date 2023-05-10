/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takira <takira@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 16:19:43 by takira            #+#    #+#             */
/*   Updated: 2023/04/12 15:28:50 by takira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_colorf	get_checker_color_on_plane(t_intersection_point intp, t_shape *shape)
{
	int				condition_checker;
	t_texture_map	pattern_map;
	float			u_mag, v_mag;

	pattern_map = get_planar_map(shape->data.plane.position, intp.position, intp.normal);

	u_mag = 1.0f / 50.0f;
	v_mag = 1.0f / 50.0f;

	condition_checker = (int)(floorf(pattern_map.u * u_mag) + floorf(pattern_map.v * v_mag)) % 2;
	if (condition_checker)
		return (shape->material.checker_color);
	return (shape->material.diffuse_ref);
}

static t_colorf	get_checker_color_on_sphere(t_intersection_point intp, t_shape *shape)
{
	int				condition_checker;
	t_texture_map	pattern_map;
	float			u_mag, v_mag;

	pattern_map = get_spherical_map(intp.position, shape->data.sphere.center, shape->data.sphere.radius);

	u_mag = 10.0f;
	v_mag = 10.0f;

	condition_checker = (int)(floorf(pattern_map.u * u_mag) + floorf(pattern_map.v * v_mag)) % 2;
	if (condition_checker)
		return (shape->material.checker_color);
	return (shape->material.diffuse_ref);
}

static t_colorf	get_checker_color_on_cylinder(t_intersection_point intp, t_shape *shape)
{
	int				condition_checker;
	t_texture_map	pattern_map;
	float			u_mag, v_mag;

	pattern_map = get_cylindrical_map( intp.position, shape->data.cylinder.position, shape->data.cylinder.normal, shape->data.cylinder.height);
	u_mag = 10.0f;
	v_mag = 7.0f;

	condition_checker = (int)(floorf(pattern_map.u * u_mag) + floorf(pattern_map.v * v_mag)) % 2;
	if (condition_checker)
		return (shape->material.checker_color);
	return (shape->material.diffuse_ref);
}

static t_colorf	get_checker_color_on_corn(t_intersection_point intp, t_shape *shape)
{
	int				condition_checker;
	t_texture_map	pattern_map;
	float			u_mag, v_mag;

	u_mag = 10.0f;
	v_mag = 10.0f;

	pattern_map = get_conical_map( intp.position, shape->data.corn.position, shape->data.corn.normal, shape->data.corn.height);

	condition_checker = (int)(floorf(pattern_map.u * u_mag) + floorf(pattern_map.v * v_mag)) % 2;
	if (condition_checker)
		return (shape->material.checker_color);
	return (shape->material.diffuse_ref);
}

t_colorf	get_checker_color(t_intersection_point intp, t_shape *shape)
{
	t_colorf	color;

	SET_COLOR(color, 0.0f, 0.0f, 0.0f)

	if (shape->type == ST_PLANE)
		return (get_checker_color_on_plane(intp, shape));
	else if (shape->type == ST_SPHERE)
		return (get_checker_color_on_sphere(intp, shape));
	else if (shape->type == ST_CYLINDER)
		return (get_checker_color_on_cylinder(intp, shape));
	else if (shape->type == ST_CORN)
		return (get_checker_color_on_corn(intp, shape));
	return (color);
}

/* ring pattern */
//			condition_checker = (int)(floorf(sqrtf(SQR(intp.position.x) + SQR(intp.position.z)))) % 2;
//			if (condition_checker)
//			{
//				SET_COLOR(color, 0.3f, 0.3f, 0.3f);
//				color = colorf_add(&color, &color);
//			}
